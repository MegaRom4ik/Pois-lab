#include "Equipment.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw EquipmentError(message);
}
} // namespace
Equipment::Equipment(const std::string &name, double capacity_kg, bool available)
    : name_(name), capacity_kg_(capacity_kg), available_(available) {
    valid(!name_.empty() && capacity_kg_ > 0 && std::isfinite(capacity_kg_), "Invalid equipment");
}
void Equipment::reserve(double load) {
    valid(available_ && load >= 0 && std::isfinite(load) && load <= capacity_kg_,
          "Equipment unavailable or overloaded");
    available_ = false;
}
void Equipment::release() {
    valid(!available_, "Equipment is not reserved");
    available_ = true;
}
} // namespace fitness
