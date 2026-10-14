#include "TemperatureLog.hpp"
namespace cooking {
TemperatureLog::TemperatureLog(std::string equipment, std::vector<double> readings, double maximum)
    : equipment_(std::move(equipment)), readings_(std::move(readings)), maximum_(std::move(maximum)) {
    text(equipment_);
    finite_number(maximum_);
}
void TemperatureLog::record(double value) {
    finite_number(value);
    if (value > maximum_)
        throw EquipmentError("Температура выше предела");
    readings_.push_back(value);
}
double TemperatureLog::average() const {
    if (readings_.empty())
        throw EquipmentError("Нет замеров");
    double total = 0;
    for (double value : readings_)
        total += value;
    return total / readings_.size();
}
} // namespace cooking
