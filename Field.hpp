#pragma once
#include <cstdint>
#include <string>

struct Field {
    enum class Color {
        RED,
        BLACK,
        GREEN
    };

    Field() = default;

    Field(uint16_t number, uint16_t zeroVariant=0)
        : color(colorFromNumber(number)), number(number), zeroVariant(zeroVariant) {}

    std::string toString() const;

    Color color;
    uint16_t number;
    uint16_t zeroVariant; // 0 for non-zero fields and 0; 1 for 00, 2 for 000

private:
    static constexpr Color colorFromNumber(uint16_t number);
};

inline std::string Field::toString() const {
    std::string str = std::to_string(number) + ' ';
    if (number == 0) {
        if (zeroVariant == 1)
            str = "00 ";
        else if (zeroVariant == 2)
            str = "000 ";
    }

    switch (color) {
        case Color::RED: str += "red"; break;
        case Color::BLACK: str += "black"; break;
        case Color::GREEN: str += "green"; break;
    }
    return str;
}

constexpr  Field::Color Field::colorFromNumber(uint16_t number) {
    if (number == 0)
        return Color::GREEN;

    // "In number ranges from 1 to 10 and 19 to 28, odd numbers are red and even are black.
    // In ranges from 11 to 18 and 29 to 36, odd numbers are black and even are red."
    // Source: https://en.wikipedia.org/wiki/Roulette

    if ((number >= 1 && number <= 10) || (number >= 29 && number <= 36))
        return number % 2 == 0 ? Color::BLACK : Color::RED;

    return number % 2 == 0 ? Color::RED : Color::BLACK;
}

