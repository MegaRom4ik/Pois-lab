#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: ExpiredFoodError. */
class ExpiredFoodError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
