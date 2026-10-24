#include "Supplier.hpp"
namespace cooking {
Supplier::Supplier(std::string name, std::vector<PriceQuote> offers, double minimum_order)
    : name_(std::move(name)), offers_(std::move(offers)), minimum_order_(std::move(minimum_order)) {
    text(name_);
    nonnegative(minimum_order_);
}
PriceQuote Supplier::quote_for(const std::string &product) const {
    for (const auto &offer : offers_)
        if (offer.ingredient() == product)
            return offer;
    throw OrderError("Нет предложения");
}
bool Supplier::accepts(const ShoppingList &list) const {
    for (const auto &item : list.items()) {
        bool found = false;
        for (const auto &offer : offers_)
            if (offer.ingredient() == item.item().ingredient().name())
                found = true;
        if (!found)
            return false;
    }
    return list.total() >= minimum_order_;
}
} // namespace cooking
