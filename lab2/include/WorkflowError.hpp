#pragma once
#include "CookingError.hpp"
namespace cooking {
/** Exception raised by the cooking model: WorkflowError. */
class WorkflowError : public CookingError {
  public:
    using CookingError::CookingError;
};
} // namespace cooking
