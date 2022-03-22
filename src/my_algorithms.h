#include<string>
#include<vector>

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