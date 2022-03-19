#include <iostream>
#include <getopt.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>

#define PATHMAXLEN 1024
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
    sort(begin(occurences), end(occurences));
    occurences.erase(unique(begin(occurences),end(occurences)), end(occurences));
    return occurences;
}

void print_ocurrences(const string& text_line, int line_index, const vector<pair<int,int>>& occurences){
    if(occurences.empty()) return;
    int text_len = (int)text_line.length(), occur_len = (int)occurences.size();
    int red_index = 0;
    cout << "Line " << line_index << ": ";
    for (int i = 0, j = 0; i < text_len; ++i){
        //occurrences[i] = {start_position_of_pattern, pattern_length}
        if(j < occur_len && occurences[j].first == i){
            red_index = i + occurences[j].second;
            ++j;
            cout << RED; // at the start of a pattern
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
    UNKNOWN_ARGUMENT
};

string Interruption_Messages[] = {
    "Help message",
    "Missing arguments",
    "File not found",
    "Unknown option"
};

void usage(Interruption_Types status){
    std::cerr << Interruption_Messages[status] << '\n'; 
    exit (status);
}

int main(int argc, char **argv){
    int opt; 
    int edit_num;
    int alg_index = -1;
    bool count_flag = false;
    char patterns_directory[PATHMAXLEN] = "../";
    fstream patterns_file;
    vector<string> algorithms = {"alg1", "alg2", "alg3", "alg4"};
    
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
            strcat(patterns_directory, optarg);
            patterns_file.open(patterns_directory);
            if (!patterns_file) {
                usage(NON_EXISTING_FILE);
            }
            break;
        case 'h':
            usage(HELP);
            break;
        case '?':
            usage(UNKNOWN_ARGUMENT);
            break;
        case 0:
          /* LONG OPTIONS */
          break;
        default :
            abort();
        }
    }
    
    vector<string> patterns;
    if(patterns_file.is_open()){
        string pattern;
        while(patterns_file >> pattern){
            patterns.emplace_back(pattern);
        }
        patterns_file.close();
    }else{
        patterns.emplace_back(argv[optind]);
        ++optind;
    }

    int number_of_matches = 0;
    for (int i = optind; i < argc; ++i){
        char text_directory[PATHMAXLEN] = "../";
        strcat(text_directory, argv[i]);
        ifstream text_file;
        text_file.open(text_directory);
        if(!text_file){
            usage(NON_EXISTING_FILE);
        }

        cout << "Matches on file " << argv[i] << ": \n";
        string text_line;
        int line_index = 0;
        while(getline(text_file, text_line)){
            auto occurences = bruteforce(patterns, text_line);
            number_of_matches += (int)occurences.size();
            print_ocurrences(text_line, line_index++, occurences);
        }
        text_file.close();
        cout << '\n';
    }
    if(count_flag){
        cout << "Total number of matches: " << number_of_matches << '\n';
    }

    return 0;
}