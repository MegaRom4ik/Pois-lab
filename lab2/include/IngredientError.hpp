#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: IngredientError. */
class IngredientError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
