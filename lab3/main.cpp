#include "../lab1/cli/Input.hpp"
#include "Achievement.hpp"
#include "ActivitySummary.hpp"
#include "BodyMeasurement.hpp"
#include "Challenge.hpp"
#include "EnergyBalance.hpp"
#include "FitnessClub.hpp"
#include "FitnessTracker.hpp"
#include "HeartRateSeries.hpp"
#include "IntervalPlan.hpp"
#include "Lap.hpp"
#include "Leaderboard.hpp"
#include "NotificationQueue.hpp"
#include "RecordBook.hpp"
#include "RecoveryPlan.hpp"
#include "TrainingGoal.hpp"
#include "WalkingRoute.hpp"
#include "WorkoutPlan.hpp"
#include <fstream>
#include <iomanip>
using namespace fitness;
namespace {
constexpr int max_entries = 1000;
constexpr int max_day = 1000000;
constexpr double max_quantity = 1000000;
int integer(const std::string &prompt, int minimum = 0, int maximum = max_day) {
    const int value = cli::read<int>(prompt);
    if (value < minimum || value > maximum) throw FitnessError("Число вне допустимого диапазона");
    return value;
}
double number(const std::string &prompt, double minimum = 0) {
    const double value = cli::read<double>(prompt);
    if (!std::isfinite(value) || value < minimum || value > max_quantity)
        throw FitnessError("Число вне допустимого диапазона");
    return value;
}
Exercise read_exercise() {
    const auto name = cli::read_line("Название упражнения: ");
    const auto muscle = cli::read_line("Группа мышц: ");
    const auto equipment = cli::read_line("Оборудование (bodyweight — без оборудования): ");
    return Exercise(name, muscle, equipment);
}
StrengthExercise read_strength() {
    StrengthExercise exercise(read_exercise());
    const int count = integer("Число подходов: ", 1, max_entries);
    for (int index = 0; index < count; ++index) {
        const int repetitions = integer("Повторения: ", 1, max_entries);
        const double load = number("Вес, кг: ");
        const int rest = integer("Отдых после подхода, секунд: ");
        exercise.add_set(ExerciseSet(repetitions, load, rest));
    }
    std::cout << "Объём: " << exercise.volume() << " кг·повт., повторений: " << exercise.total_repetitions()
              << '\n';
    return exercise;
}
CardioActivity read_cardio() {
    const auto name = cli::read_line("Название активности: ");
    const double meters = number("Дистанция, м: ", 1);
    const double seconds = number("Активное время, секунд: ", 1);
    CardioActivity activity(name, Distance(meters), Duration(seconds));
    std::cout << "Скорость: " << activity.speed_kmh() << " км/ч, темп: " << activity.pace_minutes()
              << " мин/км\n";
    return activity;
}
void record_workout(FitnessTracker &tracker, bool cardio) {
    const int day = integer("День (0, 1, 2...): ");
    const auto name = cli::read_line("Название тренировки: ");
    Workout workout(name);
    if (cardio) workout.add_cardio(read_cardio());
    else workout.add_strength(read_strength());
    const int next_id = static_cast<int>(tracker.workouts().sessions().size()) + 1;
    WorkoutSession session(next_id, workout, day);
    session.finish();
    tracker.record_workout(session);
    std::cout << "Тренировка сохранена в журнале\n";
}
void steps(FitnessTracker &tracker) {
    const int day = integer("День: ");
    const int count = integer("Шаги за день: ");
    const double meters = number("Пройденная дистанция, м: ");
    tracker.record_steps(StepEntry(day, count, Distance(meters)));
}
void weight(FitnessTracker &tracker) {
    const int day = integer("День: ");
    const double kg = number("Вес, кг: ", 1);
    tracker.record_weight(WeightEntry(day, kg));
}
void water(FitnessTracker &tracker) {
    const int day = integer("День: ");
    const double ml = number("Объём воды, мл: ", 1);
    tracker.record_water(WaterEntry(day, ml));
    std::cout << "Всего: " << tracker.water().total_on(day)
              << " мл; осталось до вашей цели: " << tracker.water().remaining_on(day) << " мл\n";
}
void meal(FitnessTracker &tracker) {
    const int day = integer("День: ");
    const auto name = cli::read_line("Название приёма пищи: ");
    Meal meal(name, day);
    const int count = integer("Число продуктов: ", 1, max_entries);
    for (int index = 0; index < count; ++index) {
        const auto food_name = cli::read_line("Продукт: ");
        const double grams = number("Масса, г: ", 1);
        const double protein = number("Белки на 100 г: ");
        const double fat = number("Жиры на 100 г: ");
        const double carbs = number("Углеводы на 100 г: ");
        meal.add(Food(food_name, Nutrients(protein, fat, carbs), grams));
    }
    tracker.record_meal(meal);
    std::cout << "Энергия приёма пищи: " << meal.total_nutrients().calories() << " ккал\n";
}
void sleep(FitnessTracker &tracker) {
    const int day = integer("День пробуждения: ");
    const int bedtime = integer("Время засыпания, минут от 00:00 (23:00 = 1380): ", 0, minutes_per_day - 1);
    const int wake = integer("Время пробуждения, минут от 00:00: ", 0, minutes_per_day - 1);
    const int breaks = integer("Число пробуждений: ", 0, max_entries);
    tracker.record_sleep(SleepEntry(day, bedtime, wake, breaks));
    std::cout << "Средний сон: " << tracker.sleep().average_hours() << " ч\n";
}
void schedule(FitnessTracker &tracker) {
    const int day = integer("День: ");
    const int minute = integer("Начало, минут от 00:00: ", 0, minutes_per_day - 1);
    const int duration = integer("Длительность, минут: ", 1, minutes_per_day);
    const auto name = cli::read_line("Название тренировки: ");
    tracker.schedule(ScheduleSlot(day, minute, duration, Workout(name)));
    std::cout << "Запланировано на этот день: " << tracker.calendar().minutes_on(day) << " мин.\n";
}
void report(const FitnessTracker &tracker) {
    const int first = integer("С какого дня: ");
    const int last = integer("По какой день: ", first);
    std::cout << tracker.report(first, last);
    const ActivitySummary summary(tracker.workouts(), tracker.steps(), last);
    std::cout << "Тренировок за последние 7 дней: " << summary.weekly_sessions()
              << "; средние шаги: " << summary.weekly_step_average() << '\n';
}
void goals(const FitnessTracker &tracker) {
    const int first = integer("Начальный день: ");
    const int last = integer("Конечный день: ", first);
    const int target = integer("Цель по шагам за период: ", 1);
    const int sessions = integer("Цель по тренировкам за период: ", 1, max_entries);
    const StepGoal step_goal(target, first, last);
    const TrainingGoal training_goal(sessions, first, last);
    const Challenge challenge("Личная цель", step_goal, "Цель достигнута");
    std::cout << "Шаги: " << step_goal.progress(tracker.steps()) * 100
              << "%; осталось: " << challenge.steps_missing(tracker.steps()) << "; "
              << challenge.result(tracker.steps(), last)
              << "\nТренировки: " << training_goal.completion_percent(tracker.workouts()) << "%\n";
}
void pulse() {
    const int minimum = integer("Нижняя граница вашей зоны, уд/мин: ", 1, max_entries);
    const int maximum = integer("Верхняя граница: ", minimum, max_entries);
    const HeartRateZone zone("Пользовательская", minimum, maximum);
    HeartRateSeries series;
    const int count = integer("Число измерений: ", 1, max_entries);
    for (int index = 0; index < count; ++index) {
        const int second = integer("Время от начала, секунд (строго возрастает): ");
        const int bpm = integer("Пульс, уд/мин: ", 1, max_entries);
        series.append(HeartRateSample(second, bpm));
    }
    std::cout << "Среднее: " << series.average() << "; секунд в выбранной зоне: " << series.seconds_in(zone)
              << " (промежутки свыше 60 секунд исключены)\n";
}
void intervals() {
    const double warmup = number("Разминка, секунд: ");
    const double work = number("Рабочий интервал, секунд: ", 1);
    const double recovery = number("Восстановление, секунд: ");
    const int repetitions = integer("Повторения: ", 1, max_entries);
    IntervalPlan plan("Интервалы", Duration(warmup));
    plan.append(Interval(Duration(work), Duration(recovery), repetitions));
    std::cout << "Всего: " << plan.elapsed_minutes()
              << " мин.; доля активной работы: " << plan.work_fraction() * 100 << "%\n";
}
void route() {
    const auto name = cli::read_line("Название маршрута: ");
    const bool loop = integer("Кольцевой? 1 — да, 0 — нет: ", 0, 1) == 1;
    WalkingRoute route(name, {}, loop);
    const int count = integer("Число участков: ", 1, max_entries);
    for (int index = 0; index < count; ++index) {
        const double meters = number("Длина участка, м: ", 1);
        const double ascent = number("Набор высоты, м: ");
        route.extend(Distance(meters, ascent));
    }
    const auto distance = route.total_distance();
    std::cout << "Длина: " << distance.kilometers() << " км; набор высоты: " << distance.ascent()
              << " м; путь с возвращением: " << route.round_trip_meters() << " м\n";
}
void record(RecordBook &book) {
    const auto exercise = read_exercise();
    const double load = number("Вес, кг: ");
    const int repetitions = integer("Повторения: ", 1, max_entries);
    const int day = integer("День: ");
    const bool improved = book.submit(PersonalRecord(exercise, load, repetitions, day));
    std::cout << (improved ? "Рекорд обновлён" : "Предыдущий рекорд выше или равен") << '\n';
}
void club(FitnessClub &club) {
    const int action = integer("1 — оформить абонемент, 2 — забронировать штангу, 3 — освободить: ", 1, 3);
    if (action == 3) {
        auto inventory = club.inventory();
        inventory.release("Barbell");
        club = FitnessClub(club.name(), inventory, club.memberships());
        return;
    }
    const auto member = cli::read_line("Имя участника: ");
    const int day = integer("День: ");
    if (action == 1) {
        const int last = integer("Последний день действия: ", day);
        const int visits = integer("Число посещений: ", 1, max_entries);
        club.enroll(Membership(member, day, last, visits));
    } else {
        const double load = number("Вес на штанге, кг: ");
        club.book(member, day, "Barbell", load);
    }
    std::cout << "Операция клуба выполнена\n";
}
void reminders(NotificationQueue &queue) {
    const int action = integer("1 — добавить напоминание, 2 — показать наступившие: ", 1, 2);
    const int day = integer("День: ");
    const int minute = integer("Минут от 00:00: ", 0, minutes_per_day - 1);
    if (action == 1) {
        const auto message = cli::read_line("Текст: ");
        queue.enqueue(Reminder(message, day, minute));
    } else
        for (const auto &message : queue.deliver(day, minute))
            std::cout << message << '\n';
}
void measurements() {
    const int day = integer("День нового замера: ", 1);
    const double previous = number("Предыдущая талия, см: ", 1);
    const double waist = number("Новая талия, см: ", 1);
    const double chest = number("Обхват груди, см: ", 1);
    const BodyMeasurement current(day, waist, chest);
    std::cout << "Изменение талии: " << current.waist_change(BodyMeasurement(day - 1, previous))
              << " см; разница грудь/талия: " << current.chest_waist_difference() << " см\n";
}
void energy() {
    const double intake = number("Получено из пищи, ккал: ");
    const double active = number("Ваш расход на активность, ккал: ");
    const double baseline = number("Ваш прочий расход, ккал: ");
    const EnergyBalance balance(intake, active, baseline);
    std::cout << "Баланс: " << balance.net() << " ккал; доля активности: " << balance.activity_share() * 100
              << "%\n";
}
void plan(const FitnessTracker &tracker) {
    const auto name = cli::read_line("Название плана: ");
    const int weeks = integer("Число недель: ", 1, max_entries);
    WorkoutPlan plan(name, {}, weeks);
    for (const auto &session : tracker.workouts().sessions())
        plan.add(session.workout());
    const int rest_days = integer("Минимум дней отдыха в неделю: ", 0, days_per_week);
    const int first = integer("Начальный день недели: ");
    const RecoveryPlan recovery("Отдых", rest_days, first);
    std::cout << "Повторить записанные тренировки каждую неделю: " << plan.planned_sessions()
              << " занятий, объём " << plan.planned_volume()
              << " кг·повт.\nДней отдыха в расписании: " << recovery.rest_days(tracker.calendar())
              << "; условие выполнено: " << recovery.respected(tracker.calendar()) << '\n';
}
void achievement(const FitnessTracker &tracker) {
    const int day = integer("По какой день: ");
    const int sessions = integer("Требуется тренировок: ", 0, max_entries);
    const int steps = integer("Требуется шагов: ");
    const Achievement badge("Личная награда", sessions, steps);
    std::cout << "Награда получена: " << badge.unlocked(tracker.workouts(), tracker.steps(), day)
              << "; тренировок осталось: " << badge.sessions_remaining(tracker.workouts(), day) << '\n';
}
void leaderboard(const FitnessTracker &tracker) {
    const int day = integer("По какой день сравнить шаги: ");
    const auto name = cli::read_line("Имя второго участника: ");
    const int steps = integer("Его шаги за выбранный день: ");
    Leaderboard board;
    board.join(Participant(tracker.profile().name(), tracker.steps(), tracker.workouts()));
    board.join(Participant(name, StepHistory({StepEntry(day, steps)})));
    for (const auto &participant : board.ranking(day))
        std::cout << participant << '\n';
}
void laps() {
    const double meters = number("Длина круга, м: ", 1);
    const double first = number("Первый круг, секунд: ", 1);
    const double second = number("Второй круг, секунд: ", 1);
    const Lap previous(1, Distance(meters), Duration(first));
    const Lap current(2, Distance(meters), Duration(second));
    std::cout << "Разница второго круга: " << current.time_difference(previous)
              << " сек.; время на 100 м: " << current.seconds_per_100m() << " сек.\n";
}
void profile(FitnessTracker &tracker) {
    const auto name = cli::read_line("Имя: ");
    const int age = integer("Возраст: ", 1, max_entries);
    const double height = number("Рост, см: ", 1);
    tracker =
        FitnessTracker(UserProfile(name, age, height), tracker.workouts(), tracker.steps(), tracker.weights(),
                       tracker.water(), tracker.food(), tracker.sleep(), tracker.calendar());
}
void action(int choice, FitnessTracker &tracker, RecordBook &records, FitnessClub &fitness_club,
            NotificationQueue &notifications) {
    switch (choice) {
    case 1:
        return profile(tracker);
    case 2:
        return record_workout(tracker, true);
    case 3:
        return record_workout(tracker, false);
    case 4:
        return steps(tracker);
    case 5:
        return weight(tracker);
    case 6:
        return water(tracker);
    case 7:
        return meal(tracker);
    case 8:
        return sleep(tracker);
    case 9:
        return schedule(tracker);
    case 10:
        return report(tracker);
    case 11:
        return goals(tracker);
    case 12:
        return pulse();
    case 13:
        return intervals();
    case 14:
        return route();
    case 15:
        return record(records);
    case 16:
        return club(fitness_club);
    case 17:
        return reminders(notifications);
    case 18:
        return measurements();
    case 19:
        return energy();
    case 20:
        return plan(tracker);
    case 21:
        return achievement(tracker);
    case 22:
        return leaderboard(tracker);
    case 23:
        return laps();
    default:
        throw FitnessError("Нет такого пункта меню");
    }
}
void menu() {
    std::cout << "\nФитнес-трекер\n1 — профиль, 2 — кардиотренировка, 3 — силовая тренировка,\n"
                 "4 — шаги, 5 — вес, 6 — вода, 7 — питание, 8 — сон, 9 — расписание,\n"
                 "10 — отчёт, 11 — цели, 12 — пульс, 13 — интервалы, 14 — маршрут,\n"
                 "15 — рекорды, 16 — клуб, 17 — напоминания, 18 — замеры,\n"
                 "19 — баланс энергии, 20 — план и отдых, 21 — награды, 22 — рейтинг,\n"
                 "23 — сравнить круги, 0 — выход\n";
}
} // namespace
int main() {
    FitnessTracker tracker;
    RecordBook records;
    FitnessClub fitness_club("Клуб", EquipmentInventory("Зал", {Equipment()}));
    NotificationQueue notifications;
    std::cout << "Записи хранятся в памяти до выхода. Дни задаются целыми числами от 0.\n";
    while (std::cin) {
        menu();
        try {
            const int choice = integer("> ", 0, 23);
            if (choice == 0) break;
            action(choice, tracker, records, fitness_club, notifications);
        } catch (const std::exception &error) { std::cerr << "Ошибка: " << error.what() << '\n'; }
    }
}
