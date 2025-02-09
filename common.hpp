#pragma once
#include <functional>
#include <optional>
#include <cstdint>

template<class T, class TFunc>
void processFirstAndLastN(
    size_t n,
    T *first,
    size_t size,
    TFunc func,
    std::optional<std::function<void()>> doBetween = std::nullopt
) {
    static_assert(std::is_invocable_v<TFunc, size_t, T&>);

    size_t i = 0;
    for (; i < std::min(n, size); ++i)
        func(i, first[i]);

    if (n * 2 >= size) {
        for (size_t ii = 0; ii < n && i < size; ++ii, ++i) {
            func(i, first[i]);
        }
        return;
    }

    if (doBetween)
        doBetween.value()();

    for (i = size - n; i < size; ++i)
        func(i, first[i]);
}
