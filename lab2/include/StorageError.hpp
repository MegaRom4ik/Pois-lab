#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: StorageError. */
class StorageError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
