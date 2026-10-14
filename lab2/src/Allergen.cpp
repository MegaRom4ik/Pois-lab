#include "Allergen.hpp"
namespace cooking {
Allergen::Allergen(std::string name, int severity, bool trace_sensitive)
    : name_(std::move(name)), severity_(std::move(severity)), trace_sensitive_(std::move(trace_sensitive)) {
    text(name_);
    if (severity_ < 1 || severity_ > 3)
        throw IngredientError("Степень аллергена 1..3");
}
bool Allergen::matches(const std::string &ingredient_allergen) const { return name_ == ingredient_allergen; }
bool Allergen::blocks(int sensitivity, bool trace) const {
    return sensitivity >= severity_ && (!trace || trace_sensitive_);
}
} // namespace cooking
