#include "Menu.hpp"
namespace cooking {
Menu::Menu(std::string title, std::vector<MenuItem> items, int max_items)
    : title_(std::move(title)), items_(std::move(items)), max_items_(std::move(max_items)) {
    text(title_);
    if (max_items_ <= 0)
        throw OrderError("Неверный размер меню");
}
void Menu::add(const MenuItem &item) {
    if (static_cast<int>(items_.size()) >= max_items_)
        throw OrderError("Меню заполнено");
    items_.push_back(item);
}
std::vector<MenuItem> Menu::select(const DietProfile &profile) const {
    std::vector<MenuItem> result;
    for (const auto &item : items_)
        if (item.suitable(profile))
            result.push_back(item);
    return result;
}
} // namespace cooking
