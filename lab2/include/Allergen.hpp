#pragma once
#include "IngredientError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Аллерген и порог чувствительности. */
class Allergen {
  public:
    Allergen(std::string name = "молоко", int severity = 2, bool trace_sensitive = true);
    const std::string &name() const { return name_; }
    int severity() const { return severity_; }
    bool trace_sensitive() const { return trace_sensitive_; }
    bool matches(const std::string &ingredient_allergen) const;
    bool blocks(int sensitivity, bool trace) const;

  private:
    std::string name_;
    int severity_;
    bool trace_sensitive_;
};
} // namespace cooking
