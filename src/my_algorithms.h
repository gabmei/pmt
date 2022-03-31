#include<string>
#include<vector>
#include <unordered_map>

#ifndef KMP_H
#define KMP_H
class KMP{
    public:
        KMP(const std::vector<std::string>& patterns);
        std::vector<std::pair<int,int>> match_patterns(const std::string& text);
    private:
        std::vector<std::string> patterns;
        std::vector<std::vector<int>> borders;

        std::vector<int> get_border(const std::string& pattern);
        void get_borders();
        void match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences);
};

#endif // KMP_H

#ifndef SHIFT_OR_H
#define SHIFT_OR_H

class SHIFT_OR{
    public:
        SHIFT_OR(const std::vector<std::string>& patterns);
        std::vector<std::pair<int,int>> match_patterns(const std::string& text);
    private:
        static int char_id(char c) { return int(c); }
        static unsigned long long set_mask(int pattern_len) { return (1ull << pattern_len) - 1; }
        const static int alpha = 256;

        std::vector<std::string> patterns;
        std::vector<std::vector<unsigned long long>> char_masks;
        std::vector<unsigned long long> get_pattern_masks(const std::string& pattern);
        void get_masks();
        void match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences);
};

#endif // SHIFT_OR_H

#ifndef SELLERS_H
#define SELLERS_H

class SELLERS{
    public:
        SELLERS(const std::vector<std::string>& patterns, int edit_dist);
        std::vector<std::pair<int,int>> match_patterns(const std::string& text);
    private:
        static int phi(const char& a, const char& b) { return a != b ? 1 : 0; }
        void update_col(const int& id, std::vector<std::pair<int,int>>& col, const char& letter);
        void match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences);

        std::vector<std::string> patterns;
        int edit_dist;
        
        
        
};

#endif // SELLERS_H


#ifndef UKKONEN_H
#define UKKONEN_H

class UKKONEN{
    public:
        UKKONEN(const std::vector<std::string>& patterns, int edit_dist);
        std::vector<std::pair<int,int>> match_patterns(const std::string& text);
    private:
        static int char_id(char c) { return int(c); }
        static int phi(const char& a, const char& b) { return a != b ? 1 : 0; }
        void update_col(const int& id, std::vector<std::pair<int,int>>& col, const char& letter);
        void match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences);
        std::pair<std::vector<std::vector<int>>, std::unordered_map<int, int>> build_fsm(const int& id);
        const static int alpha = 256;

        std::vector<std::string> patterns;
        int edit_dist;
};

#endif // UKKONEN_H