#include "FitnessClub.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("FitnessClub: domain behavior and validation") {
    FitnessClub value("Gym", EquipmentInventory("Gym", {Equipment()}),
                      {Membership("Other"), Membership("Roman")});
    CHECK_THROWS_AS(value.book("Roman", 0, "Missing", 0), EquipmentError);
    CHECK(value.memberships()[1].credits() == 10);
    value.book("Roman", 0, "Barbell", 20);
    CHECK(value.memberships()[1].credits() == 9);
    CHECK_THROWS_AS(value.book("Missing", 0, "Barbell", 0), MembershipError);
    CHECK_THROWS_AS(value.enroll(Membership("Roman")), MembershipError);
    CHECK_THROWS_AS(FitnessClub(""), MembershipError);
}
