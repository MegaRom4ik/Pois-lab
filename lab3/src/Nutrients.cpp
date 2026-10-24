#include "Nutrients.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw NutritionError(message);
}
} // namespace
Nutrients::Nutrients(double protein, double fat, double carbohydrate)
    : protein_(protein), fat_(fat), carbohydrate_(carbohydrate) {
    valid(protein_ >= 0 && fat_ >= 0 && carbohydrate_ >= 0 && std::isfinite(protein_) &&
              std::isfinite(fat_) && std::isfinite(carbohydrate_),
          "Invalid nutrients");
}
double Nutrients::calories() const {
    return protein_ * protein_kcal_per_gram + fat_ * fat_kcal_per_gram +
           carbohydrate_ * carbohydrate_kcal_per_gram;
}
Nutrients Nutrients::scaled(double factor) const {
    valid(factor >= 0 && std::isfinite(factor), "Invalid nutrient scale");
    return Nutrients(protein_ * factor, fat_ * factor, carbohydrate_ * factor);
}
Nutrients Nutrients::combined(const Nutrients &other) const {
    return Nutrients(protein_ + other.protein_, fat_ + other.fat_, carbohydrate_ + other.carbohydrate_);
}
} // namespace fitness
