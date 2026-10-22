#pragma once
#include "Feedback.hpp"
#include "Recipe.hpp"
#include "RecipeError.hpp"
#include "Support.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <utility>
#include <vector>
namespace cooking {
/** The average rating of a specific recipe. */
class RatingSummary {
  public:
    RatingSummary(Recipe recipe = Recipe{}, std::vector<Feedback> feedback = {}, int minimum_reviews = 1);
    const Recipe &recipe() const { return recipe_; }
    const std::vector<Feedback> &feedback() const { return feedback_; }
    int minimum_reviews() const { return minimum_reviews_; }
    void add(const Feedback &item);
    double average() const;

  private:
    Recipe recipe_;
    std::vector<Feedback> feedback_;
    int minimum_reviews_;
};
} // namespace cooking
