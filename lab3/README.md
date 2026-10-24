# Lab 3 — Fitness Tracker

A C++17 console application for recording workouts, steps, weight, meals, water and sleep, planning training, and viewing progress. Days are relative nonnegative integers. Menus are in Russian; source documentation is in English.

## Build and run

Clang, Make and curl are required. Run commands from the repository root:

```sh
make lab3
./build/fitness_cli
make test-lab3
make coverage-lab3
make docs-lab3
```

Coverage: `build/fitness-coverage/index.html`. Documentation: `build/fitness-docs/html/index.html`. Generated HTML opens in any browser without Doxygen. Generating it requires Doxygen. Coverage requires LLVM and Python 3. On macOS Make selects the compiler and LLVM tools from Xcode/Command Line Tools. `make all`, `make test`, `make coverage` and `make docs` include all three implemented laboratories.

In a prebuilt release archive, use `./fitness_cli`. No compiler or IDE is needed. The macOS universal archive supports Apple Silicon and Intel on macOS 13 or later; the Linux archive supports x86_64. Release files include `fitness-docs/html/index.html`.

## Using the program

1. Set your profile with menu item 1.
2. Record a cardio workout with item 2, or a strength workout with item 3.
3. Enter daily totals for steps with item 4 and chronological weight measurements with item 5.
4. Record water, food and sleep with items 6–8. Book nonoverlapping workouts with item 9.
5. View a dated report with item 10 and check selected goals with item 11.
6. Explore heart-rate intervals, interval plans, routes, records, club bookings, reminders, measurements, energy balance, recovery days, achievements, leaderboards and lap comparison with items 12–23.
7. Enter 0 to exit.

Records are held in memory for the current run. There is no save/load command or background notification service. Calculation tools such as route and interval previews are displayed immediately. Reminders are delivered only when requested from their menu and are dismissed after delivery. The leaderboard compares the current user's history with a second participant's manually entered step count.

For example, item 2 with day `0`, workout `Morning run`, activity `Run`, distance `2000` metres and time `600` seconds records a run at 12 km/h and 5 min/km. Item 10 for days `0` to `6` then shows one session. Steps, water and weight can be added independently.

## Domain rules

- Invalid input raises a domain exception before it is recorded. All fields are private and public accessors are read-only.
- Completed workouts must contain strength or cardio work; a session can be completed once. The log rejects unfinished sessions and duplicate IDs.
- Strength volume is repetitions multiplied by load, summed over sets. Unilateral work counts both sides. It is expressed as kg-repetitions, not energy.
- Cardio speed uses active time; elapsed time includes rest and pauses. Pace requires a positive distance. Lap comparisons require equal distances.
- Step history stores one total per day. Weight records must have strictly increasing days. Multiple meals and water servings per day are allowed; sleep is one record per awakening day.
- Schedule slots must fit within one day, cannot overlap, and respect the calendar's daily duration limit. Adjacent slots are allowed.
- Sensor timestamps must increase. Time in a heart-rate zone uses the previous reading until the next sample, ignoring gaps over the configured maximum. Zones are inclusive and chosen by the user.
- Sleep times are minutes since midnight. A wake time before bedtime means the next day; equal times are rejected as ambiguous. Duration is under 24 hours.
- Goals count an inclusive range of days. Progress is capped at 100%. Leaderboard ties are resolved alphabetically.
- A club reservation consumes a visit credit only after membership and equipment checks both succeed. A failed reservation preserves credits and equipment availability.
- Food energy uses 4 kcal/g protein, 9 kcal/g fat and 4 kcal/g carbohydrate. Nutrient labels are per 100 g; portion masses scale them. Targets and energy expenditure are user inputs. These calculations do not make health recommendations.
- Finite numeric inputs are required where applicable. Calculations use `double`; their precision and range remain subject to that type's limits. The CLI bounds counts and values to keep interactive input manageable.

## Object model

There are 52 domain classes, 167 fields, 130 implemented domain methods and 65 directed associations between distinct domain classes. Constructors, inline read-only accessors and exception classes are excluded from the behavior count. The checker counts methods mechanically; the inventory below states each method's purpose for review. In particular, forwarding application operations are shown explicitly rather than hidden in the totals.

An association is one directed class pair where the target appears in the source's fields or method parameters; repeated uses of the same pair count once. Exceptions are listed separately: 14 specialized exception classes derive from `FitnessError`, for 15 custom exception classes including the base.

| Class | Fields | Domain methods | Associated classes |
|---|---|---|---|
| Distance | 3 | 3 | — |
| Duration | 3 | 3 | — |
| UserProfile | 3 | 2 | — |
| BodyMeasurement | 3 | 2 | — |
| WeightEntry | 3 | 2 | — |
| WeightHistory | 3 | 3 | WeightEntry |
| Exercise | 3 | 2 | — |
| ExerciseSet | 3 | 2 | — |
| StrengthExercise | 3 | 3 | Exercise, ExerciseSet |
| CardioActivity | 3 | 2 | Distance, Duration |
| Workout | 3 | 4 | CardioActivity, StrengthExercise |
| WorkoutSession | 4 | 2 | Workout |
| WorkoutLog | 3 | 3 | WorkoutSession |
| WorkoutPlan | 3 | 3 | Workout |
| ScheduleSlot | 4 | 2 | Workout |
| TrainingCalendar | 3 | 3 | ScheduleSlot |
| StepEntry | 3 | 2 | Distance |
| StepHistory | 3 | 3 | StepEntry |
| StepGoal | 3 | 2 | StepHistory |
| WalkingRoute | 3 | 3 | Distance |
| Lap | 3 | 2 | Distance, Duration |
| Interval | 3 | 2 | Duration |
| IntervalPlan | 3 | 3 | Duration, Interval |
| HeartRateSample | 3 | 2 | — |
| HeartRateZone | 3 | 2 | HeartRateSample |
| HeartRateSeries | 3 | 3 | HeartRateSample, HeartRateZone |
| SleepEntry | 4 | 2 | — |
| SleepDiary | 3 | 3 | SleepEntry |
| WaterEntry | 3 | 2 | — |
| HydrationLog | 3 | 3 | WaterEntry |
| Nutrients | 3 | 3 | — |
| Food | 3 | 2 | Nutrients |
| Meal | 3 | 3 | Food |
| FoodDiary | 3 | 3 | Meal |
| EnergyBalance | 3 | 2 | — |
| ActivitySummary | 3 | 2 | StepHistory, WorkoutLog |
| PersonalRecord | 4 | 2 | Exercise |
| RecordBook | 3 | 2 | PersonalRecord |
| Achievement | 3 | 2 | StepHistory, WorkoutLog |
| Challenge | 3 | 2 | StepGoal, StepHistory |
| Participant | 3 | 2 | StepHistory, WorkoutLog |
| Leaderboard | 3 | 2 | Participant |
| Equipment | 3 | 2 | — |
| EquipmentInventory | 3 | 3 | Equipment |
| Membership | 4 | 2 | — |
| FitnessClub | 3 | 2 | EquipmentInventory, Membership |
| Reminder | 4 | 3 | Workout |
| NotificationQueue | 3 | 2 | Reminder |
| ProgressReport | 3 | 2 | StepHistory, WeightHistory, WorkoutLog |
| FitnessTracker | 8 | 8 | FoodDiary, HydrationLog, Meal, ScheduleSlot, SleepDiary, SleepEntry, StepEntry, StepHistory, TrainingCalendar, UserProfile, WaterEntry, WeightEntry, WeightHistory, WorkoutLog, WorkoutSession |
| TrainingGoal | 3 | 2 | WorkoutLog |
| RecoveryPlan | 3 | 2 | TrainingCalendar |

## Fields and behavior inventory

### Distance

A route segment measured in metres.

Fields: `meters` (`double`), `ascent` (`double`), `surface` (`std::string`).

- `kilometers`: Convert metres to kilometres.
- `grade`: Calculate the ascent to distance ratio.
- `joined`: Join two route segments.

### Duration

Active, resting and paused time in seconds.

Fields: `active` (`double`), `rest` (`double`), `paused` (`double`).

- `elapsed`: Sum all recorded time.
- `active_minutes`: Convert active time to minutes.
- `active_share`: Calculate the fraction spent active.

### UserProfile

Identity and basic user settings.

Fields: `name` (`std::string`), `age` (`int`), `height_cm` (`double`).

- `matches`: Find a user by part of their name.
- `height_meters`: Convert the recorded height to metres.

### BodyMeasurement

Body dimensions recorded on a day.

Fields: `day` (`int`), `waist_cm` (`double`), `chest_cm` (`double`).

- `waist_change`: Compare waist measurements chronologically.
- `chest_waist_difference`: Calculate the difference between two dimensions.

### WeightEntry

A dated weight measurement.

Fields: `day` (`int`), `kilograms` (`double`), `note` (`std::string`).

- `change_from`: Calculate chronological weight change.
- `within`: Compare a measurement with a target interval.

### WeightHistory

Chronological weight records and a user selected target.

Fields: `entries` (`std::vector<WeightEntry>`), `target` (`double`), `tolerance` (`double`).

- `add`: Append a measurement with a new later day.
- `total_change`: Calculate change between the first and last measurements.
- `goal_reached`: Check the latest measurement against the goal.

### Exercise

A named exercise and its required equipment.

Fields: `name` (`std::string`), `muscle` (`std::string`), `equipment` (`std::string`).

- `trains`: Match the primary muscle group.
- `possible_with`: Check equipment availability for an exercise.

### ExerciseSet

One strength set with repetitions, load and rest.

Fields: `repetitions` (`int`), `load_kg` (`double`), `rest_seconds` (`int`).

- `volume`: Calculate lifted kilogram repetitions.
- `deloaded`: Create a lighter set while retaining repetitions and rest.

### StrengthExercise

An exercise with an ordered list of sets.

Fields: `exercise` (`Exercise`), `sets` (`std::vector<ExerciseSet>`), `unilateral` (`bool`).

- `add_set`: Append a completed or planned set.
- `volume`: Sum lifted volume, including both sides for unilateral work.
- `total_repetitions`: Sum repetitions across sets and sides.

### CardioActivity

An activity with distance and timing.

Fields: `name` (`std::string`), `distance` (`Distance`), `duration` (`Duration`).

- `speed_kmh`: Calculate moving speed in kilometres per hour.
- `pace_minutes`: Calculate minutes per kilometre.

### Workout

A collection of strength and cardio exercises.

Fields: `name` (`std::string`), `strength` (`std::vector<StrengthExercise>`), `cardio` (`std::vector<CardioActivity>`).

- `add_strength`: Include a strength exercise in the workout.
- `add_cardio`: Include a cardio activity in the workout.
- `lifted_volume`: Sum strength volume across exercises.
- `cardio_minutes`: Sum active cardio minutes.

### WorkoutSession

A dated workout with explicit completion state.

Fields: `id` (`int`), `workout` (`Workout`), `day` (`int`), `completed` (`bool`).

- `finish`: Complete a nonempty session once.
- `in_period`: Select completed sessions within an inclusive date range.

### WorkoutLog

Completed workouts identified by unique session IDs.

Fields: `sessions` (`std::vector<WorkoutSession>`), `owner` (`std::string`), `capacity` (`int`).

- `append`: Store a completed session after checking uniqueness and capacity.
- `volume_between`: Aggregate lifted volume for a period.
- `count_between`: Count completed sessions in a period.

### WorkoutPlan

A weekly workout pattern repeated for a number of weeks.

Fields: `name` (`std::string`), `workouts` (`std::vector<Workout>`), `weeks` (`int`).

- `add`: Add a workout to the weekly pattern.
- `planned_sessions`: Calculate the number of scheduled sessions.
- `planned_volume`: Calculate total planned lifted volume.

### ScheduleSlot

A workout scheduled within a single day.

Fields: `day` (`int`), `minute` (`int`), `duration_minutes` (`int`), `workout` (`Workout`).

- `end_minute`: Calculate the end time of a booking.
- `overlaps`: Detect overlapping bookings, excluding adjacent slots.

### TrainingCalendar

Nonoverlapping workout bookings with a daily limit.

Fields: `name` (`std::string`), `slots` (`std::vector<ScheduleSlot>`), `daily_limit` (`int`).

- `book`: Book a workout after overlap and daily limit checks.
- `minutes_on`: Sum booked workout minutes on a day.
- `cancel_day`: Cancel all workout bookings for a day.

### StepEntry

Daily step count and measured distance.

Fields: `day` (`int`), `steps` (`int`), `distance` (`Distance`).

- `stride_meters`: Calculate average distance per step.
- `remaining`: Calculate steps remaining to a daily target.

### StepHistory

Unique daily step totals.

Fields: `entries` (`std::vector<StepEntry>`), `owner` (`std::string`), `daily_goal` (`int`).

- `record`: Record the total for a new day.
- `total_steps`: Sum steps over an inclusive day range.
- `goal_days`: Count days meeting the configured step goal.

### StepGoal

A step challenge over an inclusive date range.

Fields: `target` (`long long`), `first_day` (`int`), `last_day` (`int`).

- `progress`: Calculate capped progress over the challenge period.
- `achieved`: Check if the step target has been met before its deadline.

### WalkingRoute

A named route assembled from distance segments.

Fields: `name` (`std::string`), `segments` (`std::vector<Distance>`), `loop` (`bool`).

- `extend`: Append a route segment.
- `total_distance`: Sum distance and ascent over the route.
- `round_trip_meters`: Calculate the distance needed to return to the starting point.

### Lap

A numbered cardio split.

Fields: `number` (`int`), `distance` (`Distance`), `duration` (`Duration`).

- `seconds_per_100m`: Normalize split timing to 100 metres.
- `time_difference`: Compare active time for equal distance splits.

### Interval

A repeated work and recovery block.

Fields: `work` (`Duration`), `recovery` (`Duration`), `repetitions` (`int`).

- `total_seconds`: Calculate block duration including every recovery.
- `work_seconds`: Calculate active work time across repetitions.

### IntervalPlan

A warmup followed by interval blocks.

Fields: `name` (`std::string`), `warmup` (`Duration`), `blocks` (`std::vector<Interval>`).

- `append`: Append an interval block.
- `elapsed_minutes`: Calculate the complete interval session duration.
- `work_fraction`: Calculate the active work fraction including warmup.

### HeartRateSample

A sensor reading at a relative timestamp.

Fields: `second` (`int`), `bpm` (`int`), `sensor` (`std::string`).

- `time_since`: Calculate time since an earlier sample.
- `change_from`: Calculate the change in beats per minute.

### HeartRateZone

A user configured heart rate interval, without medical recommendations.

Fields: `name` (`std::string`), `minimum` (`int`), `maximum` (`int`).

- `contains`: Classify a reading into the configured inclusive zone.
- `overlap_width`: Count integer heart rates shared by two zones.

### HeartRateSeries

Ordered readings with a maximum interval for time integration.

Fields: `samples` (`std::vector<HeartRateSample>`), `label` (`std::string`), `max_gap` (`int`).

- `append`: Append a reading at a strictly later time.
- `average`: Calculate the arithmetic mean of recorded readings.
- `seconds_in`: Integrate left endpoint readings while excluding long sensor gaps.

### SleepEntry

A sleep interval expressed as minute of day.

Fields: `day` (`int`), `bedtime` (`int`), `wake_time` (`int`), `interruptions` (`int`).

- `minutes`: Calculate duration, supporting an interval crossing midnight.
- `hours_per_interruption`: Calculate average hours per uninterrupted segment.

### SleepDiary

Daily sleep records and a user selected duration target.

Fields: `entries` (`std::vector<SleepEntry>`), `target_minutes` (`int`), `owner` (`std::string`).

- `record`: Record a new daily sleep interval.
- `average_hours`: Calculate mean sleep duration in hours.
- `total_deficit`: Sum shortfalls relative to the selected sleep duration.

### WaterEntry

A dated serving of water.

Fields: `day` (`int`), `milliliters` (`double`), `label` (`std::string`).

- `liters`: Convert the water serving to litres.
- `cups`: Count complete cups of a selected capacity.

### HydrationLog

Water servings and a user configured daily target.

Fields: `entries` (`std::vector<WaterEntry>`), `target_ml` (`double`), `owner` (`std::string`).

- `drink`: Record an additional water serving.
- `total_on`: Sum water consumed on a day.
- `remaining_on`: Calculate the remaining amount for the selected daily target.

### Nutrients

Macronutrient masses in grams.

Fields: `protein` (`double`), `fat` (`double`), `carbohydrate` (`double`).

- `calories`: Calculate energy using 4, 9 and 4 kcal per gram.
- `scaled`: Scale all nutrient masses together.
- `combined`: Combine nutrients from multiple portions.

### Food

A consumed portion with nutrition stated per 100 grams.

Fields: `name` (`std::string`), `per_100g` (`Nutrients`), `grams` (`double`).

- `portion_nutrients`: Convert reference nutrient values to the consumed portion.
- `resized`: Create a portion of a different mass.

### Meal

A dated meal containing food portions.

Fields: `name` (`std::string`), `day` (`int`), `foods` (`std::vector<Food>`).

- `add`: Add a food portion to the meal.
- `total_nutrients`: Aggregate nutrients across food portions.
- `total_grams`: Calculate total consumed food mass.

### FoodDiary

A food diary with a user selected energy budget.

Fields: `meals` (`std::vector<Meal>`), `target_kcal` (`double`), `owner` (`std::string`).

- `record`: Record a consumed meal.
- `calories_on`: Sum recorded food energy for a day.
- `budget_balance`: Calculate remaining energy relative to the user chosen budget.

### EnergyBalance

User supplied daily intake and expenditure estimates.

Fields: `intake` (`double`), `activity` (`double`), `baseline` (`double`).

- `net`: Subtract estimated expenditure from intake.
- `activity_share`: Calculate the activity fraction of estimated expenditure.

### ActivitySummary

A joint summary of workouts and step records.

Fields: `workouts` (`WorkoutLog`), `steps` (`StepHistory`), `day` (`int`).

- `weekly_sessions`: Count workouts in the trailing seven day window.
- `weekly_step_average`: Calculate average daily steps over the trailing available week.

### PersonalRecord

Best recorded load for a given exercise and repetition count.

Fields: `exercise` (`Exercise`), `load_kg` (`double`), `repetitions` (`int`), `day` (`int`).

- `beats`: Compare loads for the same exercise and repetition count.
- `improvement`: Calculate load improvement for comparable records.

### RecordBook

Personal records grouped by exercise and repetition count.

Fields: `records` (`std::vector<PersonalRecord>`), `owner` (`std::string`), `capacity` (`int`).

- `submit`: Insert a new record category or replace a strictly lower load.
- `best_load`: Find the best load for one exercise and repetition count.

### Achievement

An achievement combining workout and step milestones.

Fields: `name` (`std::string`), `required_sessions` (`int`), `required_steps` (`long long`).

- `unlocked`: Check both lifetime milestone requirements.
- `sessions_remaining`: Calculate workouts still needed for the achievement.

### Challenge

A named, dated step challenge.

Fields: `name` (`std::string`), `goal` (`StepGoal`), `reward` (`std::string`).

- `result`: Award the configured label only after reaching the challenge goal.
- `steps_missing`: Calculate the step shortfall for the challenge period.

### Participant

A leaderboard participant with independent activity history.

Fields: `name` (`std::string`), `steps` (`StepHistory`), `workouts` (`WorkoutLog`).

- `step_score`: Calculate a participant score using step totals only.
- `active_days`: Count distinct days with steps or a completed workout.

### Leaderboard

A deterministic ranking by step totals.

Fields: `name` (`std::string`), `participants` (`std::vector<Participant>`), `first_day` (`int`).

- `join`: Register a participant with a unique display name.
- `ranking`: Rank descending step totals, resolving ties alphabetically.

### Equipment

A reservable piece of exercise equipment.

Fields: `name` (`std::string`), `capacity_kg` (`double`), `available` (`bool`).

- `reserve`: Reserve available equipment within its load capacity.
- `release`: Release a currently reserved item.

### EquipmentInventory

An inventory of uniquely named equipment.

Fields: `name` (`std::string`), `items` (`std::vector<Equipment>`), `capacity` (`int`).

- `add`: Add equipment after capacity and identity checks.
- `reserve`: Find and reserve equipment by its name.
- `release`: Find and release equipment by its name.

### Membership

A dated club membership with remaining visit credits.

Fields: `member` (`std::string`), `first_day` (`int`), `last_day` (`int`), `credits` (`int`).

- `valid_on`: Check validity dates and remaining visit credits.
- `consume_visit`: Consume one visit credit during the validity period.

### FitnessClub

Membership and equipment booking coordinated atomically.

Fields: `name` (`std::string`), `inventory` (`EquipmentInventory`), `memberships` (`std::vector<Membership>`).

- `enroll`: Register a unique membership.
- `book`: Reserve equipment and spend a visit credit only if both operations succeed.

### Reminder

A scheduled reminder that can be dismissed.

Fields: `message` (`std::string`), `day` (`int`), `minute` (`int`), `enabled` (`bool`).

- `due`: Check whether an enabled reminder is due.
- `postpone`: Postpone a reminder by a positive number of days.
- `dismiss`: Disable further delivery of this reminder.

### NotificationQueue

Bounded reminders for a single user.

Fields: `owner` (`std::string`), `reminders` (`std::vector<Reminder>`), `capacity` (`int`).

- `enqueue`: Queue a reminder without exceeding capacity.
- `deliver`: Return and dismiss due reminders so they are delivered once.

### ProgressReport

A report combining workouts, steps and weight history.

Fields: `workouts` (`WorkoutLog`), `steps` (`StepHistory`), `weights` (`WeightHistory`).

- `render`: Render a dated activity summary and lifetime weight change.
- `sessions_per_week`: Normalize the session count to a seven day rate.

### FitnessTracker

Application state coordinating activity and daily records.

Fields: `profile` (`UserProfile`), `workouts` (`WorkoutLog`), `steps` (`StepHistory`), `weights` (`WeightHistory`), `water` (`HydrationLog`), `food` (`FoodDiary`), `sleep` (`SleepDiary`), `calendar` (`TrainingCalendar`).

- `record_workout`: Store a finished workout in the application log.
- `record_steps`: Store a new daily step total.
- `record_weight`: Store a chronological weight measurement.
- `record_water`: Record water consumption.
- `record_meal`: Record a consumed meal.
- `record_sleep`: Store one sleep interval.
- `schedule`: Book a planned workout.
- `report`: Build a progress report from the current application state.

### TrainingGoal

A workout attendance target in a date interval.

Fields: `required_sessions` (`int`), `first_day` (`int`), `last_day` (`int`).

- `sessions_missing`: Calculate the attendance shortfall for the chosen period.
- `completion_percent`: Calculate capped attendance completion as a percentage.

### RecoveryPlan

A rest-day policy based on the recorded calendar.

Fields: `name` (`std::string`), `minimum_rest_days` (`int`), `first_day` (`int`).

- `rest_days`: Count unbooked days in a seven day schedule.
- `respected`: Check the user configured minimum number of rest days.

## Exceptions

| Exception | Purpose |
|---|---|
| DistanceError | Reports invalid distance data or operations. |
| DurationError | Reports invalid duration data or operations. |
| EquipmentError | Reports invalid equipment data or operations. |
| ExerciseError | Reports invalid exercise data or operations. |
| FitnessError | Common base for fitness application failures. |
| GoalError | Reports invalid goal data or operations. |
| MeasurementError | Reports invalid measurement data or operations. |
| MembershipError | Reports invalid membership data or operations. |
| NutritionError | Reports invalid nutrition data or operations. |
| PlanError | Reports invalid plan data or operations. |
| ProfileError | Reports invalid profile data or operations. |
| RecoveryError | Reports invalid recovery data or operations. |
| ScheduleError | Reports invalid schedule data or operations. |
| SensorError | Reports invalid sensor data or operations. |
| WorkoutError | Reports invalid workout data or operations. |

## Tests and automation

Each domain class has its own test source in `tests`. Tests cover successful calculations, rejected inputs, invalid transitions, boundaries and preservation of state after failed bookings. Run `make build/fitness_tests` followed by `./build/fitness_tests --success` to display assertions, or `./build/fitness_tests --list-test-cases` to list scenarios.

`scripts/check_lab3.py model lab3` checks the model counts from declarations and definitions. `make coverage-lab3` measures each `lab3/src/*.cpp` file using LLVM and rejects any result less than or equal to 90%. CLI, third-party doctest and inline header accessors are outside this implementation line metric. Coverage indicates execution of lines, not proof that all possible inputs are correct.

The GitHub workflow runs builds, unit tests, coverage checks, cppcheck and Doxygen. It uploads programs and reports only after these steps succeed. A version tag starts release packaging only after the checks pass. The macOS package additionally verifies both CPU architectures and launches each console program with an exit command.

## Assignment

- [Lab 3](https://github.com/alix-zzh/ppois-course/blob/master/ru/lab3.md)
- [Common requirements](https://github.com/alix-zzh/ppois-course/blob/master/ru/common_requirements.md)
- [Checklist](https://github.com/alix-zzh/ppois-course/blob/master/ru/checklist.md)
