#pragma once
#include "DietProfile.hpp"
#include "OrderError.hpp"
#include "Recipe.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Позиция меню и цена порции. */
class MenuItem {
  public:
    MenuItem(Recipe recipe = Recipe{}, double price = 15, bool enabled = true);
    const Recipe &recipe() const { return recipe_; }
    double price() const { return price_; }
    bool enabled() const { return enabled_; }
    double charge(int portions) const;
    bool suitable(const DietProfile &profile) const;

  private:
    Recipe recipe_;
    double price_;
    bool enabled_;
};
} // namespace cooking
