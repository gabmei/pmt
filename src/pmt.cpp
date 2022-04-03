#include <iostream>
#include <getopt.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

#include "my_algorithms.h"

#define RED "\033[1;31m"
#define WHITE "\033[0m"
using namespace std;

vector<pair<int,int>> bruteforce(const vector<string>& patterns, const string& text) {
    vector<pair<int, int>> occurences = {};
    //occurrences[i] = {start_position_of_pattern, pattern_length}
    int text_len = (int)text.length();
    for(auto pattern : patterns){
        int pattern_len = (int)pattern.length();
        for (int i = 0; i + pattern_len <= text_len; ++i){
            if(text.substr(i, pattern_len) == pattern){
                occurences.emplace_back(i, pattern_len);
            }
        }
    }
    return occurences;
}

void print_ocurrences(const string& text_line, int line_index, vector<pair<int,int>>& occurences){
    if(occurences.empty()) return;
    sort(begin(occurences), end(occurences), [](const auto& a, const auto& b){
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    int text_len = (int)text_line.length(), occur_len = (int)occurences.size();
    int red_index = -1;
    cout << "Line " << line_index << ": ";
    for (int i = 0, j = 0; i < text_len; ++i){
        //occurrences[i] = {start_position_of_pattern, pattern_length}
        while(j < occur_len && occurences[j].first < i) ++j;
        if(j < occur_len && occurences[j].first == i){
            if(i > red_index) cout << RED; // at the start of a pattern
            red_index = i + occurences[j].second;
            ++j;

        }
        if(i == red_index){ // at the end of a pattern
            cout << WHITE;
        }
        cout << text_line[i];
    }
    cout << WHITE << '\n';
}
  


enum Interruption_Types {
    HELP,
    MISSING_ARGUMENTS,
    NON_EXISTING_FILE,
    UNKNOWN_ARGUMENT,
    NEGATIVE_EDIT
};

string Interruption_Messages[] = {
    "Usage: ./bin/pmt [options] pattern textfile [textfile...]\n"
    "Search for patten in each textfile\n"
    "Example: ./bin/pmt -a KMP \"hello world\" hello.txt\n"
    "Multiple patterns can be passed through a file separated by newline\n"
    "Example: ./bin/pmt -p patterns.txt hello.txt\n\n"
    "Pattern selection and interpretation:\n"
    " -e, --edit e_max                 maximum distance for approximated search\n"
    " -p, --pattern pattern_file       search for patterns in pattern_file\n"
    " -a, --algorithm algorithm_name   choose algorithm for pattern search\n"
    "       exact search       :       kmp, shift_or or bruteforce\n"
    "       approximated search:       sellers or ukkonen",
    " -c, --count                      print the total occurrences of pattern matches"
    "Missing arguments",
    "File not found",
    "Unknown option",
    "Negative edit_max"
};

void usage(Interruption_Types status){
    std::cerr << Interruption_Messages[status] << '\n'; 
    exit (status);
}


vector<pair<int,int>> get_occurrences(const vector<string>& patterns, const string& text, const vector<string>& algorithms, int alg_index, int edit_dist = 0){
    if(algorithms[alg_index] == "shift_or"){
        static auto shift_or = SHIFT_OR(patterns);
        return shift_or.match_patterns(text);
    }
    if(algorithms[alg_index] == "kmp"){
        static auto kmp = KMP(patterns);
        return kmp.match_patterns(text);
    }
    if(algorithms[alg_index] == "sellers"){
        static auto sellers = SELLERS(patterns, edit_dist);
        return sellers.match_patterns(text);
    }
    if(algorithms[alg_index] == "ukkonen"){
        static auto ukkonen = UKKONEN(patterns, edit_dist);
        return ukkonen.match_patterns(text);
    }
    return bruteforce(patterns, text);
}

int main(int argc, char **argv){
    int opt; 
    int edit_num = 0;
    int alg_index = 1;
    bool count_flag = false;
    fstream patterns_file;
    vector<string> algorithms = {"bruteforce", "kmp", "shift_or", "sellers", "ukkonen"};
    
    static struct option long_options[] = {
            {"edit", required_argument, 0, 'e'},
            {"pattern", required_argument, 0, 'p'},
            {"algorithm", optional_argument, 0, 'a'},
            {"count", no_argument, 0, 'c'},
            {"help", no_argument, 0, 'h'},
            {0,0,0,0}
    };

    int option_index = 0;

    //iterate trhoug option arguments with getopt
    while ((opt = getopt_long (argc, argv, "a::ce:p:h", long_options, &option_index)) != -1) {  
      switch (opt) {
        case 'a':
            if (optarg == NULL && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            if (optarg) {
                // convert input string to lowercase
                for(size_t i = 0; i < strlen(optarg); ++i) optarg[i] = tolower(optarg[i]);
                auto it = find(begin(algorithms), end(algorithms), optarg);
                if(it == end(algorithms)) {
                    usage(MISSING_ARGUMENTS);
                }
                alg_index = int(it - begin(algorithms));
            }
            break;
        case 'c':
            count_flag = true;
            break;
        case 'e':
            char * pEnd;
            edit_num = int(strtol (optarg, &pEnd, 10));
            if(*pEnd) {
                usage(MISSING_ARGUMENTS);
            }
            break;
        case 'p':
	        if (optarg == NULL && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            patterns_file.open(optarg);
            if (!patterns_file) {
                usage(NON_EXISTING_FILE);
            }
            break;
        case 'h':
            usage(HELP);
            break;
        case '?':
            exit(UNKNOWN_ARGUMENT);
            break;
        case 0:
          /* LONG OPTIONS */
          break;
        default :
            abort();
        }
    }
    if(edit_num < 0) usage(NEGATIVE_EDIT);
    vector<string> patterns;
    if(patterns_file.is_open()){
        string pattern;
        while(getline(patterns_file, pattern)){
            patterns.emplace_back(pattern);
        }
        patterns_file.close();
    }else{
        patterns.emplace_back(argv[optind]);
        ++optind;
    }
    //make sure all patterns are different
    sort(begin(patterns), end(patterns));
    patterns.erase(unique(begin(patterns),end(patterns)), end(patterns));

    //if edit_num != 0 change to sellers if needed
    if(alg_index < 3 && edit_num > 0){
        alg_index = int(find(begin(algorithms), end(algorithms), "sellers") - begin(algorithms));
    }

    int number_of_matches = 0;
    for (int i = optind; i < argc; ++i){
        ifstream text_file;
        text_file.open(argv[i]);
        if(!text_file){
            usage(NON_EXISTING_FILE);
        }
        if(!count_flag) cout << "Matches on file " << argv[i] << ": \n";
        string text_line;
        int line_index = 1;
        while(getline(text_file, text_line)){
            auto occurences = get_occurrences(patterns, text_line, algorithms, alg_index, edit_num);
            number_of_matches += (int)occurences.size();
            if(!count_flag) print_ocurrences(text_line, line_index++, occurences);
        }
        text_file.close();
        if(!count_flag) cout << '\n';
        else {
            cout << "Total number of matches on file " << argv[i] << ": " << number_of_matches << '\n';
        }
    }
    

    return 0;
}