#include "Distance.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("Distance: domain behavior and validation") {
    Distance value(2000, 100, "trail");
    CHECK(value.kilometers() == 2);
    CHECK(value.grade() == doctest::Approx(.05));
    CHECK(value.joined(Distance(500)).meters() == 2500);
    CHECK_THROWS_AS(Distance(-1), DistanceError);
    CHECK_THROWS_AS(Distance(0).grade(), DistanceError);
}
