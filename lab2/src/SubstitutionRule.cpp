#include "SubstitutionRule.hpp"
namespace cooking {
SubstitutionRule::SubstitutionRule(std::string original, Ingredient replacement, double ratio)
    : original_(std::move(original)), replacement_(std::move(replacement)), ratio_(std::move(ratio)) {
    text(original_);
    positive(ratio_);
}
IngredientAmount SubstitutionRule::apply(const IngredientAmount &item) const {
    if (item.ingredient().name() != original_)
        throw IngredientError("Замена не подходит");
    return IngredientAmount(replacement_, item.amount().scaled(ratio_), item.optional());
}
bool SubstitutionRule::compatible(const DietProfile &profile) const { return profile.allows(replacement_); }
} // namespace cooking
