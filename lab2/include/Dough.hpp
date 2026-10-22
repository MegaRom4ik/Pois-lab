#pragma once
#include "Quantity.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Dough hydration and total mass. */
class Dough {
  public:
    Dough(Quantity flour = Quantity(1000), Quantity water = Quantity(600), Quantity salt = Quantity(20));
    const Quantity &flour() const { return flour_; }
    const Quantity &water() const { return water_; }
    const Quantity &salt() const { return salt_; }
    double hydration() const;
    Quantity total_mass() const;
    Dough scaled(double factor) const;

  private:
    Quantity flour_;
    Quantity water_;
    Quantity salt_;
};
} // namespace cooking
