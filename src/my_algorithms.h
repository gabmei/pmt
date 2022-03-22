#include<string>
#include<vector>

#ifndef KMP_H
#define KMP_H
class KMP{
    public:
        KMP(const std::vector<std::string>& _patterns);
        std::vector<int> get_border(const std::string& pattern);
        std::vector<std::vector<int>> get_borders();
        void match_pattern(const int id, const std::string& text, std::vector<std::pair<int,int>>& occurrences);
        std::vector<std::pair<int,int>> match_patterns(const std::string& text);
    private:
        std::vector<std::string> patterns;
        std::vector<std::vector<int>> borders;
};

#endif // KMP_H
