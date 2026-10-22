#include "Serving.hpp"
namespace cooking {
Serving::Serving(Dish dish, DietProfile guest, int delivered)
    : dish_(std::move(dish)), guest_(std::move(guest)), delivered_(std::move(delivered)) {
    if (delivered_ < 0)
        throw WorkflowError("Неверная выдача");
}
void Serving::deliver(int portions) {
    if (!guest_.accepts(dish_.recipe()))
        throw AllergyError("Блюдо не подходит гостю");
    dish_.serve(portions);
    delivered_ += portions;
}
double Serving::delivered_calories() const { return delivered_ * dish_.recipe().calories_per_serving(); }
} // namespace cooking
