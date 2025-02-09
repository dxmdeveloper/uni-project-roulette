#pragma once
#include "Wheel.hpp"

class EuropeanWheel : public Wheel {
public:
    EuropeanWheel();

    constexpr size_t getFieldCount() const override;

    static constexpr size_t FIELD_COUNT = 37;

    static constexpr uint16_t numbers[] {
        0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10,
        5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
    };
protected:
    constexpr void populateFields() override;
};

constexpr size_t EuropeanWheel::getFieldCount() const {
    return FIELD_COUNT;
}

constexpr void EuropeanWheel::populateFields() {
    std::copy(numbers, std::end(numbers), fields);
}
