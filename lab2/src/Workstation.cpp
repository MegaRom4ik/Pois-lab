#include "Workstation.hpp"
namespace cooking {
Workstation::Workstation(std::string name, KitchenTool tool, bool occupied)
    : name_(std::move(name)), tool_(std::move(tool)), occupied_(std::move(occupied)) {
    text(name_);
}
void Workstation::reserve(const Quantity &quantity) {
    if (occupied_)
        throw EquipmentError("Место занято");
    tool_.use(quantity);
    occupied_ = true;
}
void Workstation::release() {
    if (!occupied_)
        throw EquipmentError("Место свободно");
    tool_.wash();
    occupied_ = false;
}
} // namespace cooking
