#include "Ingredient.hpp"
namespace cooking {
Ingredient::Ingredient(std::string name, Nutrition nutrition, std::vector<std::string> allergens, bool vegetarian)
    : name_(std::move(name)), nutrition_(std::move(nutrition)), allergens_(std::move(allergens)),
      vegetarian_(std::move(vegetarian)) {
    text(name_);
}
Nutrition Ingredient::nutrition_for(const Quantity &amount) const { return nutrition_.for_mass(amount.edible()); }
bool Ingredient::contains(const Allergen &allergen) const {
    return std::any_of(allergens_.begin(), allergens_.end(), [&](const auto &item) { return allergen.matches(item); });
}
} // namespace cooking
