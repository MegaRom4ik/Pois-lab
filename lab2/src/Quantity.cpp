#include "Quantity.hpp"
namespace cooking {
Quantity::Quantity(double grams, double yield, std::string label)
    : grams_(std::move(grams)), yield_(std::move(yield)), label_(std::move(label)) {
    positive(grams_);
    fraction(yield_);
    text(label_);
}
Quantity Quantity::scaled(double factor) const {
    positive(factor);
    return Quantity(grams_ * factor, yield_, label_);
}
double Quantity::edible() const { return grams_ * yield_; }
Quantity Quantity::combined(const Quantity &other) const {
    if (label_ != other.label_ || yield_ != other.yield_)
        throw InvalidQuantityError("Несовместимые количества");
    return Quantity(grams_ + other.grams_, yield_, label_);
}
} // namespace cooking
