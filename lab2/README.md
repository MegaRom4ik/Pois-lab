# Lab 2 — Cooking

A C++17 cooking workshop: recipes, ingredient storage, purchases, cooking, and menu planning.
Ingredient amounts are measured in grams, prices are per kilogram, and dates are integer day numbers.
A batch remains usable on its expiry day, but not afterwards.
Temperature and nutrition rules are parameters of this educational model, not dietary recommendations.

## Running

```sh
make lab2
./build/cooking_cli
make test-lab2
make coverage-lab2
make docs-lab2
```

Each class has its own header in `include` and implementation in `src`.
Each domain class has a separate test file in `tests`.
Fields are private. Getters provide read access; domain operations change the state.
`Kitchen` connects the recipe book, pantry, and prepared dishes. Recipe consumption is atomic:
if any required ingredient is missing, the pantry remains unchanged. Usable batches are consumed
in order of earliest expiry. Allergens and vegetarian restrictions are checked before cooking.
Scaling changes ingredient amounts and preserves step durations. The CLI lets users complete
individual steps and serve a finished dish. Program menus are in Russian.

## Model

Fields are listed as `type name`; constructors and getters are excluded from the method column.
An association is a distinct directed pair of classes connected through a field or method parameter.
Repeated connections between the same pair are counted once.

| Class | Fields | Domain methods | Related classes |
|---|---|---|---|
| Quantity — Ingredient mass in grams, including the edible yield. | `double grams; double yield; std::string label` | `Quantity scaled(double factor) const; double edible() const; Quantity combined(const Quantity& other) const` |  |
| Nutrition — Nutritional values for a given amount of food. | `double calories; double protein; double fat; double carbs` | `Nutrition for_mass(double grams) const; Nutrition combined(const Nutrition& other) const; double macro_energy() const` |  |
| Allergen — An allergen and its sensitivity threshold. | `std::string name; int severity; bool trace_sensitive` | `bool matches(const std::string& ingredient_allergen) const; bool blocks(int sensitivity, bool trace) const` |  |
| Ingredient — A food ingredient with nutritional values and allergens. | `std::string name; Nutrition nutrition; std::vector<std::string> allergens; bool vegetarian` | `Nutrition nutrition_for(const Quantity& amount) const; bool contains(const Allergen& allergen) const` | Quantity, Nutrition, Allergen |
| IngredientAmount — A recipe ingredient, its amount, and whether it is optional. | `Ingredient ingredient; Quantity amount; bool optional` | `IngredientAmount scaled(double factor) const; double calories() const` | Quantity, Ingredient |
| RecipeStep — A cooking step with a duration and prerequisite. | `std::string instruction; int minutes; int prerequisite` | `bool ready(int completed_steps) const; int finish_at(int start_minute) const` |  |
| Recipe — A recipe with ingredients and ordered cooking steps. | `std::string name; int servings; std::vector<IngredientAmount> ingredients; std::vector<RecipeStep> steps` | `void add_ingredient(const IngredientAmount& item); void add_step(const RecipeStep& step); Recipe scaled_to(int portions) const; double calories_per_serving() const; int duration() const` | IngredientAmount, RecipeStep |
| RecipeBook — A searchable recipe collection with removal support. | `std::string title; std::vector<Recipe> recipes; int revision` | `void add(const Recipe& recipe); Recipe find(const std::string& name) const; void remove(const std::string& name)` | Recipe |
| DietProfile — A user's dietary restrictions. | `std::string person; std::vector<Allergen> forbidden; double calorie_limit; bool vegetarian` | `bool allows(const Ingredient& ingredient) const; bool accepts(const Recipe& recipe) const` | Allergen, Ingredient, Recipe |
| SubstitutionRule — An ingredient substitution with a mass conversion ratio. | `std::string original; Ingredient replacement; double ratio` | `IngredientAmount apply(const IngredientAmount& item) const; bool compatible(const DietProfile& profile) const` | Ingredient, IngredientAmount, DietProfile |
| PortionPlan — A portion estimate including reserve servings and yield. | `int guests; int reserve; double yield` | `int required() const; Recipe prepare(const Recipe& recipe) const` | Recipe |
| PriceQuote — A price offer per kilogram of an ingredient. | `std::string ingredient; double per_kg; int valid_until` | `double cost(const Quantity& amount, int day) const; bool cheaper_than(const PriceQuote& other) const` | Quantity |
| ShoppingItem — A purchase item with an amount and price quote. | `IngredientAmount item; PriceQuote quote; int day` | `double total() const; ShoppingItem increased(double factor) const` | IngredientAmount, PriceQuote |
| ShoppingList — A shopping list with an item limit. | `std::string title; std::vector<ShoppingItem> items; int limit` | `void add(const ShoppingItem& item); double total() const; void remove_product(const std::string& name)` | ShoppingItem |
| Budget — A purchasing budget with payment and refund tracking. | `double limit; double spent; std::string currency` | `void pay(double amount); void refund(double amount); bool covers(const ShoppingList& list) const` | ShoppingList |
| Supplier — A supplier with product offers and a minimum order value. | `std::string name; std::vector<PriceQuote> offers; double minimum_order` | `PriceQuote quote_for(const std::string& product) const; bool accepts(const ShoppingList& list) const` | PriceQuote, ShoppingList |
| PurchaseOrder — A supplier order with payment and cancellation support. | `Supplier supplier; ShoppingList list; bool paid; bool cancelled` | `void submit(Budget& budget); void cancel(Budget& budget)` | ShoppingList, Budget, Supplier |
| Delivery — Delivery acceptance based on arrival date and temperature. | `PurchaseOrder order; int arrival_day; double temperature; bool accepted` | `bool on_time(int promised_day) const; void accept(double maximum_temperature)` | PurchaseOrder |
| InventoryBatch — An ingredient batch with an expiry date. | `Ingredient ingredient; double grams; int expires_day; std::string lot` | `bool usable(int day) const; void consume(double grams, int day)` | Ingredient |
| Pantry — Ingredient storage that consumes usable batches by earliest expiry. | `std::string name; std::vector<InventoryBatch> batches; double capacity` | `double stored() const; void receive(const InventoryBatch& batch); double available(const std::string& product, int day) const; void consume(const std::string& product, double grams, int day); void consume_recipe(const Recipe& recipe, int day)` | Recipe, InventoryBatch |
| StorageZone — A storage area with a temperature range. | `std::string name; double minimum; double maximum; double temperature` | `bool suitable() const; void adjust(double delta)` |  |
| FoodSafetyRule — An educational food safety rule, not medical advice. | `double min_temperature; double max_temperature; int max_open_days` | `bool permits(const StorageZone& zone, int open_days) const; void check(const InventoryBatch& batch, int day) const` | InventoryBatch, StorageZone |
| WasteRecord — Discarded ingredients and the cost of waste. | `Ingredient ingredient; Quantity amount; std::string reason` | `double loss(const PriceQuote& quote, int day) const; double fraction_of(const Quantity& purchased) const` | Quantity, Ingredient, PriceQuote |
| KitchenTool — A kitchen tool with a capacity limit and cleaning requirements. | `std::string name; double capacity; bool clean` | `void use(const Quantity& amount); void wash()` | Quantity |
| Oven — An oven with heating, readiness checks, and cooling. | `double temperature; double maximum; bool powered` | `void preheat(double target); bool ready_for(double required) const; void cool(double room_temperature)` |  |
| Timer — A timer for a cooking step. | `int remaining; bool running; int elapsed` | `void start(); void tick(int minutes)` |  |
| SkillProfile — A chef's proficiency in cooking techniques. | `std::string speciality; int level; int practice_hours` | `void practice(int hours); bool qualifies(const std::string& technique, int required_level) const` |  |
| Chef — A chef with skills and available working time. | `std::string name; SkillProfile skills; int available_minutes` | `void assign(const Recipe& recipe); bool can_cook(const std::string& technique, int level) const` | Recipe, SkillProfile |
| Workstation — A workstation and its availability. | `std::string name; KitchenTool tool; bool occupied` | `void reserve(const Quantity& quantity); void release()` | Quantity, KitchenTool |
| Task — A cooking task with a deadline. | `Recipe recipe; int deadline; bool completed` | `bool fits(int start) const; void complete(int finish)` | Recipe |
| Assignment — A task assigned to a chef and workstation. | `Chef chef; Task task; Workstation station; bool started` | `void start(int minute); void finish(int minute)` | Chef, Workstation, Task |
| Schedule — A task schedule checked against available working time. | `std::string day; std::vector<Task> tasks; int shift_minutes` | `int workload() const; void add(const Task& task)` | Task |
| Dish — A cooked dish with a remaining portion count. | `Recipe recipe; int remaining; int cooked_day` | `void serve(int portions); double calories_for(int portions) const` | Recipe |
| CookingSession — Step-by-step cooking with atomic ingredient consumption. | `Recipe recipe; int next_step; bool started; int day` | `void begin(Pantry& pantry); void complete_step(); Dish finish() const` | Recipe, Pantry |
| PlatingRule — Serving quantities for food and garnish. | `std::string style; double portion_grams; double garnish_grams` | `Quantity for_guests(int count) const; int plates_from(const Quantity& cooked) const` | Quantity |
| MenuItem — A menu entry and its price per serving. | `Recipe recipe; double price; bool enabled` | `double charge(int portions) const; bool suitable(const DietProfile& profile) const` | Recipe, DietProfile |
| Menu — A menu filtered by dietary restrictions. | `std::string title; std::vector<MenuItem> items; int max_items` | `void add(const MenuItem& item); std::vector<MenuItem> select(const DietProfile& profile) const` | DietProfile, MenuItem |
| MealPlan — A meal plan with a total calorie limit. | `DietProfile profile; std::vector<Recipe> meals; double daily_limit` | `double calories() const; void add(const Recipe& recipe)` | Recipe, DietProfile |
| Serving — Serving a dish to a guest after checking dietary restrictions. | `Dish dish; DietProfile guest; int delivered` | `void deliver(int portions); double delivered_calories() const` | DietProfile, Dish |
| Feedback — Feedback on a dish. | `std::string dish; int score; std::string comment` | `bool needs_attention() const; bool refers_to(const Recipe& recipe) const` | Recipe |
| RatingSummary — The average rating of a specific recipe. | `Recipe recipe; std::vector<Feedback> feedback; int minimum_reviews` | `void add(const Feedback& item); double average() const` | Recipe, Feedback |
| CostEstimate — Dish costs including ingredients, labor, and overhead. | `ShoppingList products; double labor_per_minute; double overhead` | `double total(const Recipe& recipe) const; double per_serving(const Recipe& recipe) const` | Recipe, ShoppingList |
| UnitConversion — Conversion between mass and volume using density. | `Ingredient ingredient; double grams_per_ml; std::string volume_unit` | `double volume_for(const Quantity& amount) const; Quantity mass_for(double volume) const` | Quantity, Ingredient |
| SeasoningBlend — A seasoning mixture with a recommended dose in the model. | `std::string name; std::vector<IngredientAmount> components; double grams_per_kg` | `Quantity dose(const Quantity& food) const; double component_share(const std::string& name) const` | Quantity, IngredientAmount |
| Marinade — A marinating plan based on food mass and time. | `SeasoningBlend blend; int minutes_per_kg; double liquid_ratio` | `int duration(const Quantity& food) const; Quantity liquid_for(const Quantity& food) const` | Quantity, SeasoningBlend |
| Dough — Dough hydration and total mass. | `Quantity flour; Quantity water; Quantity salt` | `double hydration() const; Quantity total_mass() const; Dough scaled(double factor) const` | Quantity |
| Fermentation — An educational estimate of dough readiness based on time. | `Dough dough; int required_minutes; int elapsed_minutes` | `void advance(int minutes); bool ready() const; double progress() const` | Dough |
| BakingProfile — A baking schedule with oven readiness checks. | `std::string name; double temperature; int minutes` | `void prepare(Oven& oven) const; int finish_at(int start) const` | Oven |
| TemperatureLog — A log of equipment temperature readings. | `std::string equipment; std::vector<double> readings; double maximum` | `void record(double value); double average() const` |  |
| CleaningTask — A tool cleaning task with time tracking. | `KitchenTool tool; int required_minutes; int spent_minutes` | `void work(int minutes); KitchenTool finish() const` | KitchenTool |
| Kitchen — A cooking workshop containing recipes, stock, and prepared dishes. | `RecipeBook book; Pantry pantry; std::vector<Dish> dishes; int day` | `void register_recipe(const Recipe& recipe); void stock(const InventoryBatch& batch); Recipe plan(const std::string& name, int portions, const DietProfile& profile) const; void cook(const std::string& name, int portions, const DietProfile& profile); void next_day()` | Recipe, RecipeBook, DietProfile, InventoryBatch, Pantry, Dish |
| KitchenArchive | `int version; int max_recipes; int max_entries` | `save(Kitchen, ostream); load(istream)` | Kitchen |

## Exceptions

- `CookingError` — base exception for the cooking model.
- `InvalidQuantityError` — a non-finite, negative, or otherwise invalid quantity.
- `IngredientError` — invalid ingredient data or an incompatible substitution.
- `RecipeError` — invalid portions, steps, ingredients, or a missing recipe.
- `AllergyError` — a recipe violates dietary restrictions.
- `StockError` — insufficient usable stock or a duplicate batch identifier.
- `ExpiredFoodError` — an attempt to use expired food.
- `StorageError` — storage capacity exceeded or unsuitable storage conditions.
- `BudgetError` — insufficient funds or an invalid refund.
- `OrderError` — an unavailable offer, order, or menu entry.
- `EquipmentError` — equipment is not ready, or a capacity or temperature limit is exceeded.
- `WorkflowError` — an invalid cooking, serving, or scheduling sequence.
- `SerializationError` — a write failure, damaged archive, or unsupported format.

Domain classes: **52**. Fields: **167**. Domain methods: **122**. Associations: **78**. Custom exception types: **13**.

[Assignment](https://github.com/alix-zzh/ppois-course/blob/master/ru/lab2.md)

Saving through the menu stores recipes and pantry batches. Prepared dishes, the budget, dietary
profile, and current session are not saved. Loading validates a temporary state before replacing
the kitchen, so a damaged file leaves it unchanged. The format starts with `COOKING 1` and uses
quoted strings, dates, and quantities.

## Quick menu example

The program starts with a recipe named `Каша` and a supply of oats and milk.

1. Option 1 lists recipes.
2. Option 3, recipe `Каша`, 4 portions: displays 200 g of oats, 400 g of milk, and 230 kcal per serving.
3. Option 7, `Каша`, 2 portions: starts cooking and consumes the ingredients.
4. Select option 8 twice to complete both steps and create the dish.
5. Option 11, dish 1, one portion: serves one portion.
6. Options 13 and 14 save and load recipes and stock.

Select 0 to exit. On macOS, the downloaded build may require permission in Privacy & Security.
