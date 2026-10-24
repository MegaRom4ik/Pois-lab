#include "PlatingRule.hpp"
namespace cooking {
PlatingRule::PlatingRule(std::string style, double portion_grams, double garnish_grams)
    : style_(std::move(style)), portion_grams_(std::move(portion_grams)), garnish_grams_(std::move(garnish_grams)) {
    text(style_);
    positive(portion_grams_);
    nonnegative(garnish_grams_);
}
Quantity PlatingRule::for_guests(int count) const {
    if (count <= 0)
        throw RecipeError("Нет гостей");
    return Quantity((portion_grams_ + garnish_grams_) * count);
}
int PlatingRule::plates_from(const Quantity &cooked) const {
    return static_cast<int>(cooked.grams() / (portion_grams_ + garnish_grams_));
}
} // namespace cooking
