#include "Pantry.hpp"
namespace cooking {
Pantry::Pantry(std::string name, std::vector<InventoryBatch> batches, double capacity)
    : name_(std::move(name)), batches_(), capacity_(std::move(capacity)) {
    text(name_);
    positive(capacity_);
    for (const auto &batch : batches)
        receive(batch);
}
double Pantry::stored() const {
    double total = 0;
    for (const auto &batch : batches_)
        total += batch.grams();
    return total;
}
void Pantry::receive(const InventoryBatch &batch) {
    for (const auto &existing : batches_)
        if (existing.lot() == batch.lot())
            throw StockError("Номер партии уже существует");
    if (stored() + batch.grams() > capacity_)
        throw StorageError("Склад заполнен");
    batches_.push_back(batch);
}
double Pantry::available(const std::string &product, int day) const {
    double total = 0;
    for (const auto &batch : batches_)
        if (batch.ingredient().name() == product && batch.usable(day))
            total += batch.grams();
    return total;
}
void Pantry::consume(const std::string &product, double grams, int day) {
    positive(grams);
    if (available(product, day) < grams)
        throw StockError("Недостаточно свежего продукта");
    auto next = batches_;
    std::stable_sort(next.begin(), next.end(), [](const auto &left, const auto &right) {
        return left.expires_day() < right.expires_day();
    });
    double remaining = grams;
    for (auto &batch : next) {
        if (batch.ingredient().name() != product || !batch.usable(day) || remaining <= 0)
            continue;
        const double amount = std::min(remaining, batch.grams());
        batch.consume(amount, day);
        remaining -= amount;
    }
    batches_ = std::move(next);
}
void Pantry::consume_recipe(const Recipe &recipe, int day) {
    Pantry next = *this;
    for (const auto &item : recipe.ingredients()) {
        if (item.optional())
            continue;
        next.consume(item.ingredient().name(), item.amount().grams(), day);
    }
    *this = std::move(next);
}
} // namespace cooking
