#include "Nutrition.hpp"
namespace cooking {
Nutrition::Nutrition(double calories, double protein, double fat, double carbs)
    : calories_(std::move(calories)), protein_(std::move(protein)), fat_(std::move(fat)), carbs_(std::move(carbs)) {
    nonnegative(calories_);
    nonnegative(protein_);
    nonnegative(fat_);
    nonnegative(carbs_);
}
Nutrition Nutrition::for_mass(double grams) const {
    nonnegative(grams);
    const double factor = grams / 100.0;
    return Nutrition(calories_ * factor, protein_ * factor, fat_ * factor, carbs_ * factor);
}
Nutrition Nutrition::combined(const Nutrition &other) const {
    return Nutrition(calories_ + other.calories_, protein_ + other.protein_, fat_ + other.fat_, carbs_ + other.carbs_);
}
double Nutrition::macro_energy() const { return protein_ * 4.0 + fat_ * 9.0 + carbs_ * 4.0; }
} // namespace cooking
