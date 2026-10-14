#include "Oven.hpp"
namespace cooking {
Oven::Oven(double temperature, double maximum, bool powered)
    : temperature_(std::move(temperature)), maximum_(std::move(maximum)), powered_(std::move(powered)) {
    finite_number(temperature_);
    positive(maximum_);
    if (temperature_ > maximum_)
        throw EquipmentError("Неверная духовка");
}
void Oven::preheat(double target) {
    positive(target);
    if (target > maximum_)
        throw EquipmentError("Перегрев духовки");
    temperature_ = target;
    powered_ = true;
}
bool Oven::ready_for(double required) const { return powered_ && temperature_ >= required; }
void Oven::cool(double room_temperature) {
    finite_number(room_temperature);
    if (room_temperature > temperature_)
        throw EquipmentError("Остывание не нагрев");
    temperature_ = room_temperature;
    powered_ = false;
}
} // namespace cooking
