#include "sort.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
void print_vector(const std::vector<T>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0)
            std::cout << " "; // space BEFORE item, skip for first
        std::cout << v[i];
    }
    std::cout << "\n";
}

void print_pairs(const std::vector<std::pair<std::string, int>>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i > 0)
            std::cout << " "; // space BEFORE item, skip for first
        std::cout << "{ \"" << v[i].first << "\": " << v[i].second << " }";
    }
    std::cout << "\n";
}

int main()
{
    std::cout << "Sorting integers with my::sort (default operator<):\n";
    std::cout << "Before: ";
    std::vector<int> ints = { 8, 2, 6, 5, 1, 9, 3 };
    print_vector(ints);
    my::sort(ints.begin(), ints.end());
    std::cout << "After:  ";
    print_vector(ints);

    std::cout << "\n";

    std::cout << "Sorting strings with my::sort (default operator<):\n";
    std::vector<std::string> words = { "Java", "C++", "Kotlin", "C#", "Scala", "C" };
    std::cout << "Before: ";
    print_vector(words);
    my::sort(words.begin(), words.end());
    std::cout << "After:  ";
    print_vector(words);

    std::cout << "\n";

    std::cout << "Sorting word frequencies with my::sort (lambda: by count descending):\n";
    std::vector<std::pair<std::string, int>> freqs = {
        { "apple", 2 }, { "banana", 5 }, { "cherry", 1 }, { "date", 3 }
    };
    std::cout << "Before: ";
    print_pairs(freqs);
    my::sort(freqs.begin(), freqs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // ← my::sort, not std::sort
    });
    std::cout << "After:  ";
    print_pairs(freqs);

    return 0;
}