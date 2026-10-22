#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: RecipeError. */
class RecipeError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
