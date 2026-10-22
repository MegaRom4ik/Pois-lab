#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: SerializationError. */
class SerializationError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
