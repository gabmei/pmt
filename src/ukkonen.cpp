#include<string>
#include<vector>
#include <map>
#include <unordered_map>
#include <queue>
#include "my_algorithms.h"

UKKONEN::UKKONEN(const std::vector<std::string>& patterns, int edit_dist) : patterns(patterns), edit_dist(edit_dist){}

void UKKONEN::update_col(const int& id, std::vector<std::pair<int,int>>& col, const char& letter){
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
            col[i].first = x > edit_dist ? edit_dist + 1 : x;
            col[i].second = prev_len + 1;
        }else if(y <= z){
            col[i].first = y > edit_dist ? edit_dist + 1 : y;
            col[i].second = col[i - 1].second + 1;
        }else{
            col[i].first = z > edit_dist ? edit_dist + 1 : z;
        }
    }
}

std::pair<std::vector<std::vector<int>>, std::unordered_map<int, int>> UKKONEN::build_fsm(const int& id){
    const auto& pattern = patterns[id]; 
    int pattern_len = (int)pattern.size();
    std::vector<std::pair<int,int>> init_col(pattern_len + 1, {0, 0});
    for(int i = 0; i < pattern_len + 1; ++i) init_col[i].first = i;
    std::queue<std::pair<std::vector<std::pair<int,int>>, int>> col_queue;
    col_queue.push({init_col, 0});
    /*
    ;auto hash = [](const std::vector<std::pair<int,int>>& v){
        int hash = (int)v.size();
        for(auto& i : v){
            hash ^= (i.first^i.second) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    };
    std::unordered_map<std::vector<std::pair<int,int>>, int, decltype(hash)> all_states(10, hash);
    */
    std::map<std::vector<std::pair<int,int>>, int> all_states;
    int index_seq = 1;
    std::vector<std::vector<int>> delta;
    std::unordered_map<int, int> final_states;
    /*
    if(init_col[pattern_len].first <= edit_dist){
        final_states[0] = 0;
    }
    while(!col_queue.empty()){
        auto cur_col = col_queue.front().first;
        auto cur_col_index = col_queue.front().second;
        col_queue.pop();
        delta.push_back({});
        for(int i = 0; i < alpha; ++i){
            char letter = char(i);
            auto next_col = cur_col;
            auto next_index = -1;
            update_col(id, next_col, letter);
            if(all_states.count(next_col)){
                next_index = all_states[next_col];
            }else{
                next_index = index_seq++;
                col_queue.push({next_col, next_index});
                all_states[next_col] = next_index;
                if(next_col[pattern_len].first <= edit_dist){
                    final_states[next_index] = next_col[pattern_len].second;
                }
            }
            delta[cur_col_index].push_back(next_index);
        }
    }
    */
    return {delta, final_states};
}


void UKKONEN::match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences){
    int text_len = (int)text.size();

    auto fsm = build_fsm(id);
    const auto& delta = fsm.first;  
    std::unordered_map<int, int> final_states = fsm.second;
    
    int cur_index = 0;
    // error here
    if(final_states[cur_index]){
        occurrences.emplace_back(0);
    }
    /*
    for(int i = 0; i < text_len; ++i){
        cur_index = fsm.first[cur_index][char_id(text[i])];
        if(fsm.second.count(cur_index)){
            auto len = fsm.second[cur_index];
            occurrences.emplace_back(i - len + 1, len);
        }
    }
    */
}

std::vector<std::pair<int,int>> UKKONEN::match_patterns(const std::string& text){
    std::vector<std::pair<int,int>> occurrences;
    int patterns_len = (int)patterns.size();
    for(int i = 0; i < patterns_len; ++i){
        match_pattern(i, text, occurrences);
    }
    return occurrences;
}

