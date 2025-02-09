#include "Wheel.hpp"

#include <cassert>
#include <random>

Wheel::Wheel() : fields{} {
}

Field Wheel::spin() const {
    assert(fields[4].number != 0 && "populateFields() was not called");
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, getFieldCount() - 1);

    return fields[dist(gen)];
}
