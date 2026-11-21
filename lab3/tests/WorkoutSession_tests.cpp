#include "WorkoutSession.hpp"
#include "doctest.h"
using namespace fitness;
TEST_CASE("WorkoutSession: domain behavior and validation") {
    CHECK_THROWS_AS(WorkoutSession(1, Workout(), 0, true), WorkoutError);
    WorkoutSession value(1, Workout("Run", {}, {CardioActivity()}), 2);
    CHECK_FALSE(value.in_period(0, 3));
    value.finish();
    CHECK(value.in_period(2, 2));
    CHECK_FALSE(value.in_period(3, 4));
    CHECK_THROWS_AS(value.finish(), WorkoutError);
    CHECK_THROWS_AS(value.in_period(4, 3), WorkoutError);
    CHECK_THROWS_AS(WorkoutSession().finish(), WorkoutError);
    CHECK_THROWS_AS(WorkoutSession(0), WorkoutError);
}

TEST_CASE("WorkoutSession rejects strength entries without any sets") {
    const Workout empty_strength("No sets", {StrengthExercise()});
    WorkoutSession session(1, empty_strength);
    CHECK_THROWS_AS(session.finish(), WorkoutError);
    CHECK_FALSE(session.completed());
    CHECK_THROWS_AS(WorkoutSession(1, empty_strength, 0, true), WorkoutError);
}

TEST_CASE("WorkoutSession accepts bodyweight sets and mixed workouts") {
    const StrengthExercise bodyweight(Exercise(), {ExerciseSet(10, 0)});
    WorkoutSession session(1, Workout("Bodyweight", {StrengthExercise(), bodyweight}));
    session.finish();
    CHECK(session.completed());
    CHECK(WorkoutSession(2, session.workout(), 0, true).completed());
    WorkoutSession cardio(3, Workout("Cardio", {StrengthExercise()}, {CardioActivity()}));
    cardio.finish();
    CHECK(cardio.completed());
    CHECK(WorkoutSession(4, cardio.workout(), 0, true).completed());
}
