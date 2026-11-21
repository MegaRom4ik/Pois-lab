#include "Exercise.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ExerciseError(message);
}
} // namespace
Exercise::Exercise(const std::string &name, const std::string &muscle, const std::string &equipment)
    : name_(name), muscle_(muscle), equipment_(equipment) {
    valid(!name_.empty() && !muscle_.empty() && !equipment_.empty(), "Empty exercise description");
}
bool Exercise::trains(const std::string &group) const { return muscle_ == group; }
bool Exercise::possible_with(const std::vector<std::string> &available) const {
    return equipment_ == "bodyweight" ||
           std::find(available.begin(), available.end(), equipment_) != available.end();
}
} // namespace fitness
