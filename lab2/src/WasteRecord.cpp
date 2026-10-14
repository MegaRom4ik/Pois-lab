#include "WasteRecord.hpp"
namespace cooking {
WasteRecord::WasteRecord(Ingredient ingredient, Quantity amount, std::string reason)
    : ingredient_(std::move(ingredient)), amount_(std::move(amount)), reason_(std::move(reason)) {
    text(reason_);
}
double WasteRecord::loss(const PriceQuote &quote, int day) const {
    if (quote.ingredient() != ingredient_.name())
        throw OrderError("Цена другого продукта");
    return quote.cost(amount_, day);
}
double WasteRecord::fraction_of(const Quantity &purchased) const { return amount_.grams() / purchased.grams(); }
} // namespace cooking
