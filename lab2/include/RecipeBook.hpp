#pragma once
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** Каталог рецептов с поиском и удалением. */
class RecipeBook {
  public:
    RecipeBook(std::string title = "Моя книга", std::vector<Recipe> recipes = {}, int revision = 0);
    const std::string &title() const { return title_; }
    const std::vector<Recipe> &recipes() const { return recipes_; }
    int revision() const { return revision_; }
    void add(const Recipe &recipe);
    Recipe find(const std::string &name) const;
    void remove(const std::string &name);

  private:
    std::string title_;
    std::vector<Recipe> recipes_;
    int revision_;
};
} // namespace cooking
