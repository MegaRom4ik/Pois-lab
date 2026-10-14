#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: SerializationError. */
class SerializationError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
