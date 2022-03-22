#include<string>
#include<vector>
#include "my_algorithms.h"
KMP::KMP(const std::vector<std::string>& patterns):patterns(patterns) { get_borders(); }
void KMP::get_borders(){
    for(const auto& pattern : patterns) borders.emplace_back(get_border(pattern));
    return;
}

std::vector<int> KMP::get_border(const std::string& pattern){
    int pattern_len = (int)pattern.size();
    std::vector<int> border(pattern_len, -1);
    for(int i = 1, j = -1; i < pattern_len; ++i){
        while(j >= 0 && pattern[i] != pattern[j + 1]) j = border[j];
        if(pattern[i] == pattern[j + 1]) ++j;
        border[i] = j;
    }
    return border;
}

void KMP::match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences){
    const auto& pattern = patterns[id];
    const auto& border = borders[id];
    int text_len = (int)text.size();
    int pattern_len = (int)pattern.size();
    for(int i = 0, j = -1; i < text_len; ++i){
        while(j >= 0 && text[i] != pattern[j + 1]) j = border[j];
        if(text[i] == pattern[j + 1]) ++j;
        
        if(j + 1 == pattern_len){
            occurrences.emplace_back(i - j, pattern_len);
            j = border[j];
        }
    }
    return;
}


std::vector<std::pair<int,int>> KMP::match_patterns(const std::string& text){
    std::vector<std::pair<int,int>> occurrences;
    int patterns_len = (int)patterns.size();
    for(int i = 0 ; i < patterns_len; ++i){
        match_pattern(i, text, occurrences);
    }
    return occurrences;
}