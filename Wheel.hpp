#pragma once
#include "Field.hpp"
#include <vector>

class Wheel {
public:
    Wheel();

    virtual ~Wheel() = default;

    Field spin() const;

    virtual constexpr size_t getFieldCount() const = 0;

protected:
    virtual constexpr void populateFields() = 0;

    Field fields[38]; // 38 is for variant with 3 zeros
};

