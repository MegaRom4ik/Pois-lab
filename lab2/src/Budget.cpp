#include "Budget.hpp"
namespace cooking {
Budget::Budget(double limit, double spent, std::string currency)
    : limit_(std::move(limit)), spent_(std::move(spent)), currency_(std::move(currency)) {
    positive(limit_);
    nonnegative(spent_);
    text(currency_);
    if (spent_ > limit_)
        throw BudgetError("Перерасход");
}
void Budget::pay(double amount) {
    positive(amount);
    if (amount > limit_ - spent_)
        throw BudgetError("Недостаточно бюджета");
    spent_ += amount;
}
void Budget::refund(double amount) {
    positive(amount);
    if (amount > spent_)
        throw BudgetError("Возврат больше расходов");
    spent_ -= amount;
}
bool Budget::covers(const ShoppingList &list) const { return list.total() <= limit_ - spent_; }
} // namespace cooking
