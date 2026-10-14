#include "InventoryBatch.hpp"
namespace cooking {
InventoryBatch::InventoryBatch(Ingredient ingredient, double grams, int expires_day, std::string lot)
    : ingredient_(std::move(ingredient)), grams_(std::move(grams)), expires_day_(std::move(expires_day)),
      lot_(std::move(lot)) {
    nonnegative(grams_);
    text(lot_);
    if (expires_day_ < 0)
        throw StorageError("Неверный срок годности");
}
bool InventoryBatch::usable(int day) const { return day <= expires_day_ && grams_ > 0; }
void InventoryBatch::consume(double grams, int day) {
    positive(grams);
    if (day > expires_day_)
        throw ExpiredFoodError("Партия просрочена");
    if (grams > grams_)
        throw StockError("Недостаточно продукта");
    grams_ -= grams;
}
} // namespace cooking
