#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: InvalidQuantityError. */
class InvalidQuantityError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
