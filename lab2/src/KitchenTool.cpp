#include "KitchenTool.hpp"
namespace cooking {
KitchenTool::KitchenTool(std::string name, double capacity, bool clean)
    : name_(std::move(name)), capacity_(std::move(capacity)), clean_(std::move(clean)) {
    text(name_);
    positive(capacity_);
}
void KitchenTool::use(const Quantity &amount) {
    if (!clean_ || amount.grams() > capacity_)
        throw EquipmentError("Инструмент не готов");
    clean_ = false;
}
void KitchenTool::wash() {
    if (clean_)
        throw EquipmentError("Уже вымыт");
    clean_ = true;
}
} // namespace cooking
