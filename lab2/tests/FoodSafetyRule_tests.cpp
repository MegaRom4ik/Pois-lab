#include "ExpiredFoodError.hpp"
#include "FoodSafetyRule.hpp"
#include "InventoryBatch.hpp"
#include "StorageZone.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("FoodSafetyRule: Учебное правило проверки продукта, не медицинская рекомендация.") {
    FoodSafetyRule value;
    CHECK(value.permits(StorageZone{}, 1));
    CHECK_FALSE(value.permits(StorageZone{}, 3));
    value.check(InventoryBatch{}, 1);
    CHECK_THROWS_AS(value.check(InventoryBatch{}, 31), ExpiredFoodError);
}
