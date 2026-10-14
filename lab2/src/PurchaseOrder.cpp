#include "PurchaseOrder.hpp"
namespace cooking {
PurchaseOrder::PurchaseOrder(Supplier supplier, ShoppingList list, bool paid, bool cancelled)
    : supplier_(std::move(supplier)), list_(std::move(list)), paid_(std::move(paid)), cancelled_(std::move(cancelled)) {
}
void PurchaseOrder::submit(Budget &budget) {
    if (paid_ || cancelled_ || !supplier_.accepts(list_))
        throw OrderError("Заказ нельзя оплатить");
    budget.pay(list_.total());
    paid_ = true;
}
void PurchaseOrder::cancel(Budget &budget) {
    if (cancelled_)
        throw OrderError("Уже отменён");
    if (paid_)
        budget.refund(list_.total());
    paid_ = false;
    cancelled_ = true;
}
} // namespace cooking
