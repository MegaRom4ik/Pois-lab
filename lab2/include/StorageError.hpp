#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: StorageError. */
class StorageError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
