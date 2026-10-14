#include "DietProfile.hpp"
namespace cooking {
DietProfile::DietProfile(std::string person, std::vector<Allergen> forbidden, double calorie_limit, bool vegetarian)
    : person_(std::move(person)), forbidden_(std::move(forbidden)), calorie_limit_(std::move(calorie_limit)),
      vegetarian_(std::move(vegetarian)) {
    text(person_);
    positive(calorie_limit_);
}
bool DietProfile::allows(const Ingredient &ingredient) const {
    if (vegetarian_ && !ingredient.vegetarian())
        return false;
    for (const auto &allergen : forbidden_)
        if (ingredient.contains(allergen))
            return false;
    return true;
}
bool DietProfile::accepts(const Recipe &recipe) const {
    for (const auto &item : recipe.ingredients())
        if (!allows(item.ingredient()))
            return false;
    return recipe.calories_per_serving() <= calorie_limit_;
}
} // namespace cooking
