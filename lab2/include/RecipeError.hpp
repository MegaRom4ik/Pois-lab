#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: RecipeError. */
class RecipeError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
