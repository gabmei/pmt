#include<string>
#include<vector>
#include "my_algorithms.h"

SELLERS::SELLERS(const std::vector<std::string>& patterns, int edit_dist) : patterns(patterns), edit_dist(edit_dist) {}
void SELLERS::update_col(const int& id, std::vector<std::pair<int,int>>& col, const char& letter){
    const auto& pattern = patterns[id];
    int pattern_len = (int)pattern.size();
    std::pair<int,int> previous_value = {0, 0};
    for(int i = 1; i < pattern_len + 1; ++i){
        int prev_edit = previous_value.first, prev_len = previous_value.second;
        auto x = prev_edit + phi(letter, pattern[i - 1]);
        auto y = col[i - 1].first + 1;
        auto z = col[i].first + 1;
        previous_value = col[i];
        if(x <= y && x <= z){
            col[i].first = x;
            col[i].second = prev_len + 1;
        }else if(y <= z){
            col[i].first = y;
            col[i].second = col[i - 1].second + 1;
        }else{
            col[i].first = z;
        }
    }
}

void SELLERS::match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences){
    const auto& pattern = patterns[id];
    int pattern_len = (int)pattern.size();
    int text_len = (int)text.size();
    std::vector<std::pair<int,int>> col(pattern_len + 1, {0, 0});
    for(int i = 0; i < pattern_len + 1; ++i) col[i].first = i;

    for(int i = 0; i < text_len; ++i){
        update_col(id, col, text[i]);
        if(col[pattern_len].first <= edit_dist){
            occurrences.emplace_back(i - col[pattern_len].second + 1, col[pattern_len].second);
        }
    }
}

std::vector<std::pair<int,int>> SELLERS::match_patterns(const std::string& text){
    std::vector<std::pair<int,int>> occurrences;
    int patterns_len = (int)patterns.size();
    for(int i = 0; i < patterns_len; ++i){
        match_pattern(i, text, occurrences);
    }
    return occurrences;
}

