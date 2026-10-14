#pragma once
#include "AllergyError.hpp"
#include "CookingSession.hpp"
#include "DietProfile.hpp"
#include "Dish.hpp"
#include "ExpiredFoodError.hpp"
#include "InventoryBatch.hpp"
#include "Pantry.hpp"
#include "Recipe.hpp"
#include "RecipeBook.hpp"
#include "Support.hpp"
#include "WorkflowError.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Кулинарная мастерская: каталог, склад и готовые блюда. */
class Kitchen {
  public:
    Kitchen(RecipeBook book = RecipeBook{}, Pantry pantry = Pantry{}, std::vector<Dish> dishes = {}, int day = 1);
    const RecipeBook &book() const { return book_; }
    const Pantry &pantry() const { return pantry_; }
    const std::vector<Dish> &dishes() const { return dishes_; }
    int day() const { return day_; }
    void register_recipe(const Recipe &recipe);
    void stock(const InventoryBatch &batch);
    Recipe plan(const std::string &name, int portions, const DietProfile &profile) const;
    void cook(const std::string &name, int portions, const DietProfile &profile);
    void next_day();

  private:
    RecipeBook book_;
    Pantry pantry_;
    std::vector<Dish> dishes_;
    int day_;
};
} // namespace cooking
