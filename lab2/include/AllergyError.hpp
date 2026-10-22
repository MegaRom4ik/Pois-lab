#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: AllergyError. */
class AllergyError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
