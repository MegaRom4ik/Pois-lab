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
/** Отзыв о блюде. */
class Feedback {
  public:
    Feedback(std::string dish = "Каша", int score = 5, std::string comment = "Вкусно");
    const std::string &dish() const { return dish_; }
    int score() const { return score_; }
    const std::string &comment() const { return comment_; }
    bool needs_attention() const;
    bool refers_to(const Recipe &recipe) const;

  private:
    std::string dish_;
    int score_;
    std::string comment_;
};
} // namespace cooking
