#include "Dough.hpp"
namespace cooking {
Dough::Dough(Quantity flour, Quantity water, Quantity salt)
    : flour_(std::move(flour)), water_(std::move(water)), salt_(std::move(salt)) {}
double Dough::hydration() const { return water_.grams() / flour_.grams() * 100.0; }
Quantity Dough::total_mass() const { return Quantity(flour_.grams() + water_.grams() + salt_.grams()); }
Dough Dough::scaled(double factor) const {
    return Dough(flour_.scaled(factor), water_.scaled(factor), salt_.scaled(factor));
}
} // namespace cooking
