#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <cctype>
#include <fstream>
#include <set>
#include <string>
#include <vector>

class spell_checker {
public:
    explicit spell_checker(const std::string& word_list_path)
    {
        std::ifstream file(word_list_path);
        std::string word;
        while (std::getline(file, word)) {
            if (!word.empty()) {
                dictionary.insert(word);
            }
        }
    }

    [[nodiscard]] bool is_correct(const std::string& word) const
    {
        return dictionary.count(normalize(word)) > 0;
    }

    [[nodiscard]] std::vector<std::string> suggestions(const std::string& word, int max = 5) const
    {
        const std::string norm = normalize(word);
        std::vector<std::string> result;

        for (const auto& candidate : dictionary) {
            if (edit_distance(norm, candidate) <= 1) {
                result.push_back(candidate);
                if (static_cast<int>(result.size()) >= max) {
                    return result;
                }
            }
        }

        if (!norm.empty()) {
            for (const auto& candidate : dictionary) {
                if (static_cast<int>(result.size()) >= max) {
                    break;
                }
                if (!candidate.empty() && candidate[0] == norm[0]
                    && edit_distance(norm, candidate) == 2) {
                    result.push_back(candidate);
                }
            }
        }

        return result;
    }

    [[nodiscard]] static std::string normalize(const std::string& word)
    {
        std::string result;
        for (char c : word) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return result;
    }

    [[nodiscard]] bool loaded() const { return !dictionary.empty(); }

private:
    std::set<std::string> dictionary;

    [[nodiscard]] static int edit_distance(const std::string& a, const std::string& b)
    {
        const std::size_t m = a.size();
        const std::size_t n = b.size();

        if (m == 0) return static_cast<int>(n);
        if (n == 0) return static_cast<int>(m);
        if (m > n + 2 || n > m + 2) return 3;

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (std::size_t i = 0; i <= m; ++i) dp[i][0] = static_cast<int>(i);
        for (std::size_t j = 0; j <= n; ++j) dp[0][j] = static_cast<int>(j);

        for (std::size_t i = 1; i <= m; ++i) {
            for (std::size_t j = 1; j <= n; ++j) {
                const int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
                dp[i][j] = std::min({ dp[i - 1][j] + 1,
                    dp[i][j - 1] + 1,
                    dp[i - 1][j - 1] + cost });
            }
        }

        return dp[m][n];
    }
};

#endif // SPELL_CHECKER_H