#include "SeasoningBlend.hpp"
namespace cooking {
SeasoningBlend::SeasoningBlend(std::string name, std::vector<IngredientAmount> components, double grams_per_kg)
    : name_(std::move(name)), components_(std::move(components)), grams_per_kg_(std::move(grams_per_kg)) {
    text(name_);
    positive(grams_per_kg_);
}
Quantity SeasoningBlend::dose(const Quantity &food) const { return Quantity(food.grams() / 1000.0 * grams_per_kg_); }
double SeasoningBlend::component_share(const std::string &name) const {
    double total = 0, selected = 0;
    for (const auto &item : components_) {
        total += item.amount().grams();
        if (item.ingredient().name() == name)
            selected += item.amount().grams();
    }
    return total == 0 ? 0 : selected / total;
}
} // namespace cooking
