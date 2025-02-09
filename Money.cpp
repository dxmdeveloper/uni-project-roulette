#include "Money.hpp"
#include <type_traits>

Money::Money(uint32_t integral, uint16_t decimal) {
    value = static_cast<uint64_t>(integral) * 100 + decimal;
}

Money::Money(std::string_view str) {
    auto sepPos = str.find('.');
    value = std::stoull(std::string(str)) * 100;

    if (sepPos == std::string_view::npos || sepPos == str.length() - 1)
        return;

    str = str.substr(sepPos + 1);
    if (str.length() > 2)
        str = str.substr(0, 2);

    value += std::stoul(std::string(str));
}

std::pair<uint64_t, uint16_t> Money::getValue() const {
    return {value / 100, static_cast<uint16_t>(value % 100)};
}

template<char decSep>
std::string Money::toString() const {
    auto [i, d] = getValue();
    return std::to_string(i) + decSep + std::to_string(d);
}
template std::string Money::toString<'.'>() const;
template std::string Money::toString<','>() const;

Money Money::operator/(uint64_t divisor) const {
    Money money{};
    money.value = value / divisor;
    return money;
}

template<typename T>
Money &Money::operator*=(T multiplier) {
    if constexpr(std::is_signed_v<T>)
        multiplier = std::abs(multiplier);

    value *= multiplier;
    return *this;
}

template Money &Money::operator*=<uint32_t>(uint32_t);
template Money &Money::operator*=<unsigned long>(unsigned long);
template Money &Money::operator*=<int>(int);
template Money &Money::operator*=<float>(float);

template<typename T>
Money Money::operator*(T multiplier) const {
    if constexpr(std::is_signed_v<T>)
        multiplier = std::abs(multiplier);

    Money money{};
    money.value = value * multiplier;
    return money;
}

template Money Money::operator*<uint32_t>(uint32_t) const;
template Money Money::operator*<unsigned long>(unsigned long) const;
template Money Money::operator*<int>(int) const;
template Money Money::operator*<float>(float) const;

Money &Money::operator-=(const Money &rhs) {
    value -= rhs.value;
    return *this;
}

Money Money::operator-(const Money &rhs) const {
    Money money{};
    money.value = value - rhs.value;
    return money;
}

Money &Money::operator+=(const Money &rhs) {
    value += rhs.value;
    return *this;
}

Money Money::operator+(const Money &rhs) const {
    Money newMoney{};
    newMoney.value = value + rhs.value;
    return newMoney;
}

bool Money::operator==(const Money &rhs) const {
    return value == rhs.value;
}

bool Money::operator!=(const Money &rhs) const {
    return value != rhs.value;
}

bool Money::operator<(const Money &rhs) const {
    return value < rhs.value;
}

bool Money::operator>(const Money &rhs) const {
    return value > rhs.value;
}

bool Money::operator<=(const Money &rhs) const {
    return value <= rhs.value;
}

bool Money::operator>=(const Money &rhs) const {
    return value >= rhs.value;
}

Money::operator bool() const {
    return !!value;
}

std::ostream &operator<<(std::ostream &os, const Money &money) {
    os << money.toString();
    return os;
}

std::istream &operator>>(std::istream &is, Money &money) {
    is >> money.value;
    return is;
}