#pragma once
#include "AllergyError.hpp"
#include "DietProfile.hpp"
#include "Dish.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Выдача блюда гостю с проверкой диеты. */
class Serving {
  public:
    Serving(Dish dish = Dish{}, DietProfile guest = DietProfile{}, int delivered = 0);
    const Dish &dish() const { return dish_; }
    const DietProfile &guest() const { return guest_; }
    int delivered() const { return delivered_; }
    void deliver(int portions);
    double delivered_calories() const;

  private:
    Dish dish_;
    DietProfile guest_;
    int delivered_;
};
} // namespace cooking
