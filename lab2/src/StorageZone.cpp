#include "StorageZone.hpp"
namespace cooking {
StorageZone::StorageZone(std::string name, double minimum, double maximum, double temperature)
    : name_(std::move(name)), minimum_(std::move(minimum)), maximum_(std::move(maximum)),
      temperature_(std::move(temperature)) {
    text(name_);
    finite_number(minimum_);
    finite_number(maximum_);
    finite_number(temperature_);
    if (minimum_ > maximum_)
        throw StorageError("Неверный диапазон");
}
bool StorageZone::suitable() const { return temperature_ >= minimum_ && temperature_ <= maximum_; }
void StorageZone::adjust(double delta) {
    finite_number(delta);
    const double next = temperature_ + delta;
    if (next < minimum_ || next > maximum_)
        throw StorageError("Температура вне диапазона");
    temperature_ = next;
}
} // namespace cooking
