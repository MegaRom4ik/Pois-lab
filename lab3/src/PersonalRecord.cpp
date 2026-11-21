#include "PersonalRecord.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw GoalError(message);
}
} // namespace
PersonalRecord::PersonalRecord(const Exercise &exercise, double load_kg, int repetitions, int day)
    : exercise_(exercise), load_kg_(load_kg), repetitions_(repetitions), day_(day) {
    valid(load_kg_ >= 0 && std::isfinite(load_kg_) && repetitions_ > 0 && day_ >= 0,
          "Invalid personal record");
}
bool PersonalRecord::beats(const PersonalRecord &previous) const {
    valid(exercise_.name() == previous.exercise_.name() && repetitions_ == previous.repetitions_,
          "Incomparable records");
    return load_kg_ > previous.load_kg_;
}
double PersonalRecord::improvement(const PersonalRecord &previous) const {
    valid(exercise_.name() == previous.exercise_.name() && repetitions_ == previous.repetitions_,
          "Incomparable records");
    return load_kg_ - previous.load_kg_;
}
} // namespace fitness
