#include<string>
#include<vector>
#include "my_algorithms.h"

SHIFT_OR::SHIFT_OR(const std::vector<std::string>& patterns):patterns(patterns) { get_masks(); }

std::vector<unsigned long long> SHIFT_OR::get_pattern_masks(const std::string& pattern){
    int pattern_len = (int)pattern.size();
    std::vector<unsigned long long> masks(alpha, set_mask(pattern_len));
    for(int i = 0; i < pattern_len; ++i){
        masks[char_id(pattern[i])] &= ~(1ull << i);
    }
    return masks;
}

void SHIFT_OR::get_masks(){
    for(const auto& pattern : patterns) char_masks.emplace_back(get_pattern_masks(pattern));
    return;
}

void SHIFT_OR::match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences){
    const auto& pattern = patterns[id];
    const auto& char_mask = char_masks[id];
    int pattern_len = (int)pattern.size();
    int text_len = (int)text.size();
    auto s_mask = set_mask(pattern_len);
    for(int i = 0; i < text_len; ++i){
        s_mask = (s_mask << 1) | char_mask[char_id(text[i])];
        if((s_mask & (1ull << (pattern_len - 1))) == 0){
            occurrences.emplace_back(i + 1 - pattern_len, pattern_len);
        }
    }
    return;
}

std::vector<std::pair<int,int>> SHIFT_OR::match_patterns(const std::string& text){
    std::vector<std::pair<int,int>> occurrences;
    int patterns_len = (int)patterns.size();
    for(int i = 0; i < patterns_len; ++i){
        match_pattern(i, text, occurrences);
    }
    return occurrences;
}

