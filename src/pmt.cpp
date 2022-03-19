#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> bruteforce(string pattern, string text){
    vector<int> occurences = {};
    bool aux;
    for (int i = 0; i < (text.length() - pattern.length())+1; i++){
        aux = false;
        for (int j = 0; j < pattern.length(); j++){
            if(pattern[j] != text[i+j]){
                aux = true;
                break;
            }
        }
        if(aux){
            continue;
        }
        occurences.push_back(i);
    }
    return occurences;
}

void print_ocurrences(string str, vector<int> occurences){
    for (int i = 0; i < str.length(); i++){
        if(std::find(occurences.begin(), occurences.end(), i) != occurences.end()) {
            printf("\033[0;31m");
            cout << str[i];
            printf("\033[0m");
        } else {
            cout << str[i];
        }
    }
    cout << endl;
}
  
void usage(int status){
  if (status != 0){
      printf("err msg\n");
    }
  else{
      printf("help msg\n");
    }
  exit (status);
}

int main(int argc, char **argv){  
    string pattern;
    int opt; 
    int edit_num;
    int alg_index = -1;
    bool count_flag = false;
    bool pattern_file_flag = false;
    fstream my_file;
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
      switch (opt){
        case 'a':
            if (optarg == NULL && optind < argc && argv[optind][0] != '-') {
                optarg = argv[optind++];
            }
            if (optarg){
                auto it = find(begin(algorithms), end(algorithms), optarg);
                int alg_index = it - begin(algorithms);
                if(alg_index == 4){
                    usage(1);
                }
            }
            break;
        case 'c':
            count_flag = true;
            break;
        case 'e':
            char * pEnd;
            edit_num = strtol (optarg, &pEnd, 10);
            if((*pEnd)){
                usage(1);
            }
            break;
        case 'p':
        pattern_file_flag = true;
	        my_file.open(optarg, ios::in);
            if (!my_file) {
		        cout << "No such file";
                usage(1);
	        }
            break;
        case 'h':
            usage(0);
            break;
        case '?':
            usage(-1);
            break;
        case 0:
          /* LONG OPTIONS */
          break;
        default :
            exit(1);
        }
    }

    //save pattern if not using pattern file
    if(!pattern_file_flag){
        pattern = argv[optind];
        optind++;
    }

    vector<string> texts = {};
    //redundant
    for (int i = optind; i < argc; i++){
        //texts.push_back(argv[i]);
        ifstream file;
        file.open(argv[i]);
        if ( file.is_open() ) {     
            while ( file.good() ) {
                string mystring;
                file >> mystring;
                vector<int> occurences = bruteforce(pattern,mystring);
                print_ocurrences(mystring, occurences);
            }
        }
    }
    return 0;
}