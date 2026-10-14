#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: ExpiredFoodError. */
class ExpiredFoodError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
