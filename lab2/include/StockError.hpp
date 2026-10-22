#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: StockError. */
class StockError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
