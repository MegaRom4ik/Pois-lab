#include "UserProfile.hpp"
namespace fitness {
namespace {
void valid(bool condition, const std::string &message) {
    if (!condition) throw ProfileError(message);
}
} // namespace
UserProfile::UserProfile(const std::string &name, int age, double height_cm)
    : name_(name), age_(age), height_cm_(height_cm) {
    valid(!name_.empty() && age_ > 0 && height_cm_ > 0 && std::isfinite(height_cm_), "Invalid profile");
}
bool UserProfile::matches(const std::string &query) const { return name_.find(query) != std::string::npos; }
double UserProfile::height_meters() const { return height_cm_ / 100.0; }
} // namespace fitness
