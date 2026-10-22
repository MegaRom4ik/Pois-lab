#include "PriceQuote.hpp"
namespace cooking {
PriceQuote::PriceQuote(std::string ingredient, double per_kg, int valid_until)
    : ingredient_(std::move(ingredient)), per_kg_(std::move(per_kg)), valid_until_(std::move(valid_until)) {
    text(ingredient_);
    positive(per_kg_);
    if (valid_until_ < 0)
        throw OrderError("Неверный срок цены");
}
double PriceQuote::cost(const Quantity &amount, int day) const {
    if (day > valid_until_)
        throw OrderError("Цена устарела");
    return amount.grams() / 1000.0 * per_kg_;
}
bool PriceQuote::cheaper_than(const PriceQuote &other) const {
    if (ingredient_ != other.ingredient_)
        throw OrderError("Разные продукты");
    return per_kg_ < other.per_kg_;
}
} // namespace cooking
