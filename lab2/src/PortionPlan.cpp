#include "PortionPlan.hpp"
namespace cooking {
PortionPlan::PortionPlan(int guests, int reserve, double yield)
    : guests_(std::move(guests)), reserve_(std::move(reserve)), yield_(std::move(yield)) {
    if (guests_ <= 0 || reserve_ < 0)
        throw RecipeError("Неверный план порций");
    positive(yield_);
    fraction(yield_);
}
int PortionPlan::required() const { return static_cast<int>(std::ceil((guests_ + reserve_) / yield_)); }
Recipe PortionPlan::prepare(const Recipe &recipe) const { return recipe.scaled_to(required()); }
} // namespace cooking
