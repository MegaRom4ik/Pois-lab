#include "Marinade.hpp"
namespace cooking {
Marinade::Marinade(SeasoningBlend blend, int minutes_per_kg, double liquid_ratio)
    : blend_(std::move(blend)), minutes_per_kg_(std::move(minutes_per_kg)), liquid_ratio_(std::move(liquid_ratio)) {
    if (minutes_per_kg_ <= 0)
        throw RecipeError("Неверное маринование");
    positive(liquid_ratio_);
}
int Marinade::duration(const Quantity &food) const {
    return static_cast<int>(std::ceil(food.grams() / 1000.0 * minutes_per_kg_));
}
Quantity Marinade::liquid_for(const Quantity &food) const { return food.scaled(liquid_ratio_); }
} // namespace cooking
