#include "ShoppingItem.hpp"
namespace cooking {
ShoppingItem::ShoppingItem(IngredientAmount item, PriceQuote quote, int day)
    : item_(std::move(item)), quote_(std::move(quote)), day_(std::move(day)) {
    if (item_.ingredient().name() != quote_.ingredient())
        throw OrderError("Цена другого продукта");
}
double ShoppingItem::total() const { return quote_.cost(item_.amount(), day_); }
ShoppingItem ShoppingItem::increased(double factor) const { return ShoppingItem(item_.scaled(factor), quote_, day_); }
} // namespace cooking
