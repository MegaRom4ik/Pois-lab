#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: BudgetError. */
class BudgetError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
