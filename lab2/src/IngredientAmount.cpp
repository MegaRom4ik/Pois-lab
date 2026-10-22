#include "IngredientAmount.hpp"
namespace cooking {
IngredientAmount::IngredientAmount(Ingredient ingredient, Quantity amount, bool optional)
    : ingredient_(std::move(ingredient)), amount_(std::move(amount)), optional_(std::move(optional)) {}
IngredientAmount IngredientAmount::scaled(double factor) const {
    return IngredientAmount(ingredient_, amount_.scaled(factor), optional_);
}
double IngredientAmount::calories() const { return ingredient_.nutrition_for(amount_).calories(); }
} // namespace cooking
