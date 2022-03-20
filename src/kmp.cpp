#include<string>
#include<vector>

std::vector<int> get_border(const std::string& pattern){
    int pattern_len = (int)pattern.size();
    std::vector<int> border(pattern_len, -1);
    for(int i = 1, j = -1; i < pattern_len; ++i){
        while(j >= 0 && pattern[i] != pattern[j + 1]) j = border[j];
        if(pattern[i] == pattern[j + 1]) ++j;
        border[i] = j;
    }
    return border;
}

std::vector<std::vector<int>> get_borders(const std::vector<std::string>& patterns){
    std::vector<std::vector<int>> borders;
    for(const auto& pattern : patterns) borders.emplace_back(get_border(pattern));
    return borders;
}

void match_pattern(const std::string& pattern, const std::string& text, const std::vector<int>& border, std::vector<std::pair<int,int>>& occurrences){
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


std::vector<std::pair<int,int>> match_patterns(const std::vector<std::string>& patterns, const std::string& text, const std::vector<std::vector<int>>& borders){
    std::vector<std::pair<int,int>> occurrences;
    int patterns_len = (int)patterns.size();
    for(int i = 0 ; i < patterns_len; ++i){
        auto& pattern = patterns[i];
        auto& border = borders[i];
        match_pattern(pattern, text, border, occurrences);
    }
    return occurrences;
}