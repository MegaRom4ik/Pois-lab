#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: OrderError. */
class OrderError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
