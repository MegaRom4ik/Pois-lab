#include "EquipmentInventory.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw EquipmentError(message);
}
} // namespace
EquipmentInventory::EquipmentInventory(const std::string &name, const std::vector<Equipment> &items,
                                       int capacity)
    : name_(name), items_(items), capacity_(capacity) {
    valid(!name_.empty() && capacity_ > 0, "Invalid inventory");
    auto initial = items_;
    items_.clear();
    for (const auto &item : initial)
        add(item);
}
void EquipmentInventory::add(const Equipment &item) {
    valid(items_.size() < static_cast<std::size_t>(capacity_), "Inventory full");
    for (const auto &stored : items_)
        valid(stored.name() != item.name(), "Duplicate equipment");
    items_.push_back(item);
}
void EquipmentInventory::reserve(const std::string &name, double load) {
    for (auto &item : items_)
        if (item.name() == name) {
            item.reserve(load);
            return;
        }
    throw EquipmentError("Equipment not found");
}
void EquipmentInventory::release(const std::string &name) {
    for (auto &item : items_)
        if (item.name() == name) {
            item.release();
            return;
        }
    throw EquipmentError("Equipment not found");
}
} // namespace fitness
