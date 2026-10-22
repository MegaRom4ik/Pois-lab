#include "Nutrition.hpp"
namespace cooking {
namespace {
constexpr double reference_mass_grams = 100.0;
constexpr double protein_kcal_per_gram = 4.0;
constexpr double fat_kcal_per_gram = 9.0;
constexpr double carbohydrate_kcal_per_gram = 4.0;
} // namespace
Nutrition::Nutrition(double calories, double protein, double fat, double carbs)
    : calories_(std::move(calories)), protein_(std::move(protein)), fat_(std::move(fat)),
      carbs_(std::move(carbs)) {
    nonnegative(calories_);
    nonnegative(protein_);
    nonnegative(fat_);
    nonnegative(carbs_);
}
Nutrition Nutrition::for_mass(double grams) const {
    nonnegative(grams);
    const double factor = grams / reference_mass_grams;
    return Nutrition(calories_ * factor, protein_ * factor, fat_ * factor, carbs_ * factor);
}
Nutrition Nutrition::combined(const Nutrition &other) const {
    return Nutrition(calories_ + other.calories_, protein_ + other.protein_, fat_ + other.fat_,
                     carbs_ + other.carbs_);
}
double Nutrition::macro_energy() const {
    return protein_ * protein_kcal_per_gram + fat_ * fat_kcal_per_gram + carbs_ * carbohydrate_kcal_per_gram;
}
} // namespace cooking
