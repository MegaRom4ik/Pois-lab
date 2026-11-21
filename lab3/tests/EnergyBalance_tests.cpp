#include "EnergyBalance.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("EnergyBalance: domain behavior and validation") {
    EnergyBalance value;
    CHECK(value.net() == 0);
    CHECK(value.activity_share() == .15);
    CHECK(EnergyBalance(0, 0, 0).activity_share() == 0);
    CHECK_THROWS_AS(EnergyBalance(-1), NutritionError);
}
