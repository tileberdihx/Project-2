#ifndef SORT_H
#define SORT_H
#include <algorithm>
namespace my {

    template <typename Iterator, typename Comparator>

    void sort(Iterator begin, Iterator end, Comparator comp)
    {
        for (Iterator i = begin; i != end; ++i) {
            Iterator min_it = i;

            for (Iterator j = std::next(i); j != end; ++j) { // ← fixed here
                if (comp(*j, *min_it)) {
                    min_it = j;
                }
            }

            std::iter_swap(i, min_it);
        }
    }

    template <typename Iterator>
    void sort(Iterator begin, Iterator end)
    {
        my::sort(begin, end, [](const auto& a, const auto& b) {
            return a < b;
        });
    }

}

#endif // SORT_H
