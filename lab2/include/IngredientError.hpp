#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: IngredientError. */
class IngredientError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
