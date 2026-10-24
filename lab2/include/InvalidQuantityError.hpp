#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: InvalidQuantityError. */
class InvalidQuantityError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
