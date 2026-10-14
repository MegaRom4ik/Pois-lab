#include "CostEstimate.hpp"
namespace cooking {
CostEstimate::CostEstimate(ShoppingList products, double labor_per_minute, double overhead)
    : products_(std::move(products)), labor_per_minute_(std::move(labor_per_minute)), overhead_(std::move(overhead)) {
    nonnegative(labor_per_minute_);
    nonnegative(overhead_);
}
double CostEstimate::total(const Recipe &recipe) const {
    return products_.total() + recipe.duration() * labor_per_minute_ + overhead_;
}
double CostEstimate::per_serving(const Recipe &recipe) const { return total(recipe) / recipe.servings(); }
} // namespace cooking
