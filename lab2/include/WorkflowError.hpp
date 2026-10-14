#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Ошибка кулинарной модели: WorkflowError. */
class WorkflowError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
