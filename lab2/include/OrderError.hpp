#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: OrderError. */
class OrderError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
