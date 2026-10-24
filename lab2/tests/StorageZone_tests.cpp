#include "StorageError.hpp"
#include "StorageZone.hpp"
#include "doctest.h"
using namespace cooking;
TEST_CASE("StorageZone: Температурная зона хранения.") {
    StorageZone value;
    CHECK(value.suitable());
    value.adjust(-1);
    CHECK(value.temperature() == 3);
    CHECK_THROWS_AS(value.adjust(10), StorageError);
    CHECK_FALSE(StorageZone("Зона", 0, 5, 10).suitable());
}
