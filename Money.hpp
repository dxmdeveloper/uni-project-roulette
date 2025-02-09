#pragma once
#include <cstdint>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>

struct Money {
    Money() = default;

    Money(uint32_t integral, uint16_t decimal = 0); // NOLINT(google-explicit-constructor)

    explicit Money(std::string_view str);

    std::pair<uint64_t, uint16_t> getValue() const;

    template<char decSep = '.'>
    std::string toString() const;

    Money operator/(uint64_t divisor) const;

    template<typename T>
    Money operator*(T multiplier) const;

    template<typename T>
    Money &operator*=(T multiplier);

    Money &operator-=(const Money &rhs);

    Money operator-(const Money &rhs) const;

    Money &operator+=(const Money &rhs);

    Money operator+(const Money &rhs) const;

    bool operator==(const Money &rhs) const;

    bool operator!=(const Money &rhs) const;

    bool operator<(const Money &rhs) const;

    bool operator>(const Money &rhs) const;

    bool operator<=(const Money &rhs) const;

    bool operator>=(const Money &rhs) const;

    explicit operator bool() const;

    friend std::ostream &operator<<(std::ostream &os, const Money &money);

    friend std::istream &operator>>(std::istream &is, Money &money);

private:

    uint64_t value = 0;
};

