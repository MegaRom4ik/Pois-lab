#pragma once
#include "IngredientError.hpp"
#include "InvalidQuantityError.hpp"
#include <cmath>
#include <string>
namespace cooking {
inline void finite_number(double value) {
    if (!std::isfinite(value))
        throw InvalidQuantityError("Ожидается конечное число");
}
inline void positive(double value) {
    finite_number(value);
    if (value <= 0)
        throw InvalidQuantityError("Ожидается положительное число");
}
inline void nonnegative(double value) {
    finite_number(value);
    if (value < 0)
        throw InvalidQuantityError("Отрицательное количество");
}
inline void fraction(double value) {
    finite_number(value);
    if (value < 0 || value > 1)
        throw InvalidQuantityError("Доля от 0 до 1");
}
inline void text(const std::string &value) {
    if (value.empty() || value.find_first_not_of(" \t\r\n") == std::string::npos)
        throw IngredientError("Пустое название");
}
} // namespace cooking
