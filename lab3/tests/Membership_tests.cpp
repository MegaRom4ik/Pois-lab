#include "Membership.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Membership: domain behavior and validation") {
    Membership value("Roman", 0, 2, 1);
    CHECK(value.valid_on(1));
    CHECK_FALSE(value.valid_on(3));
    value.consume_visit(1);
    CHECK_FALSE(value.valid_on(1));
    CHECK_THROWS_AS(value.consume_visit(1), MembershipError);
    CHECK_THROWS_AS(Membership(""), MembershipError);
}
