#pragma once
#include "IngredientAmount.hpp"
#include "RecipeError.hpp"
#include "RecipeStep.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Рецепт с составом и последовательностью шагов. */
class Recipe {
  public:
    Recipe(std::string name = "Каша", int servings = 2, std::vector<IngredientAmount> ingredients = {},
           std::vector<RecipeStep> steps = {});
    const std::string &name() const { return name_; }
    int servings() const { return servings_; }
    const std::vector<IngredientAmount> &ingredients() const { return ingredients_; }
    const std::vector<RecipeStep> &steps() const { return steps_; }
    void add_ingredient(const IngredientAmount &item);
    void add_step(const RecipeStep &step);
    Recipe scaled_to(int portions) const;
    double calories_per_serving() const;
    int duration() const;

  private:
    std::string name_;
    int servings_;
    std::vector<IngredientAmount> ingredients_;
    std::vector<RecipeStep> steps_;
};
} // namespace cooking
