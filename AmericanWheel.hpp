#pragma once
#include "Wheel.hpp"

class AmericanWheel : public Wheel {
public:
    AmericanWheel();

    constexpr size_t getFieldCount() const override;

    static constexpr size_t FIELD_COUNT = 38;

    static constexpr uint16_t numbers[] = {
        0, 28, 9, 26, 30, 11, 7, 20, 32, 17, 5, 22, 34, 15, 3, 24, 36, 13, 1,
        00, 27, 10, 25, 29, 12, 8, 19, 31, 18, 6, 21, 33, 16, 4, 23, 35, 14, 2
    };
protected:
    constexpr void populateFields() override;
};


constexpr size_t AmericanWheel::getFieldCount() const {
    return FIELD_COUNT;
}

constexpr void AmericanWheel::populateFields() {
    std::copy(numbers, std::end(numbers), fields);
    fields[19].zeroVariant = 1;
}
