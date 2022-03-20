#include<string>
#include<vector>
// KMP declarations
std::vector<int> get_border(const std::string& pattern);
std::vector<std::vector<int>> get_borders(const std::vector<std::string>& patterns);
void match_pattern(const std::string& pattern, const std::string& text, const std::vector<int>& border, std::vector<std::pair<int,int>>& occurrences);
std::vector<std::pair<int,int>> match_patterns(const std::vector<std::string>& patterns, const std::string& text, const std::vector<std::vector<int>>& borders);