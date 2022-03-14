#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
  
bool all_digits (string str){
    for (int i = 0; i < str.length(); i++)
    {
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
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
    int c; 
    int edit_num;
    int alg_index = -1;
    bool count_flag = false;
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

    while ((c = getopt_long (argc, argv, "a::ce:p:h", long_options, &option_index)) != -1) {  
      switch (c){
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
    return 0;
}