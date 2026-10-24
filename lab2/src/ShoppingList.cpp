#include "ShoppingList.hpp"
namespace cooking {
ShoppingList::ShoppingList(std::string title, std::vector<ShoppingItem> items, int limit)
    : title_(std::move(title)), items_(std::move(items)), limit_(std::move(limit)) {
    text(title_);
    if (limit_ <= 0)
        throw OrderError("Неверный лимит");
}
void ShoppingList::add(const ShoppingItem &item) {
    if (static_cast<int>(items_.size()) >= limit_)
        throw OrderError("Лимит списка");
    items_.push_back(item);
}
double ShoppingList::total() const {
    double value = 0;
    for (const auto &item : items_)
        value += item.total();
    return value;
}
void ShoppingList::remove_product(const std::string &name) {
    const auto found = std::find_if(items_.begin(), items_.end(),
                                    [&](const auto &item) { return item.item().ingredient().name() == name; });
    if (found == items_.end())
        throw OrderError("Покупка не найдена");
    items_.erase(found);
}
} // namespace cooking
