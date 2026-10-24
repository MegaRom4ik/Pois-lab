#include "Delivery.hpp"
namespace cooking {
Delivery::Delivery(PurchaseOrder order, int arrival_day, double temperature, bool accepted)
    : order_(std::move(order)), arrival_day_(std::move(arrival_day)), temperature_(std::move(temperature)),
      accepted_(std::move(accepted)) {
    if (arrival_day_ < 0)
        throw OrderError("Неверная дата поставки");
    finite_number(temperature_);
}
bool Delivery::on_time(int promised_day) const { return arrival_day_ <= promised_day; }
void Delivery::accept(double maximum_temperature) {
    if (accepted_ || !order_.paid() || order_.cancelled() || temperature_ > maximum_temperature)
        throw OrderError("Поставка не прошла приёмку");
    accepted_ = true;
}
} // namespace cooking
