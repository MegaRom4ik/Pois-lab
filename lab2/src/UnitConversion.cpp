#include "UnitConversion.hpp"
namespace cooking {
UnitConversion::UnitConversion(Ingredient ingredient, double grams_per_ml, std::string volume_unit)
    : ingredient_(std::move(ingredient)), grams_per_ml_(std::move(grams_per_ml)), volume_unit_(std::move(volume_unit)) {
    positive(grams_per_ml_);
    text(volume_unit_);
}
double UnitConversion::volume_for(const Quantity &amount) const { return amount.grams() / grams_per_ml_; }
Quantity UnitConversion::mass_for(double volume) const {
    positive(volume);
    return Quantity(volume * grams_per_ml_);
}
} // namespace cooking
