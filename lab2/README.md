# Лабораторная 2 — Кулинария

Кулинарная мастерская на C++17: рецепты, склад, закупки, приготовление и планирование меню.
Все количества продукта задаются в граммах, цены — за килограмм; даты — целые номера дней.
Срок партии включителен: продукт доступен в день истечения, но не позднее.
Температурные и пищевые правила — параметры учебной модели, не рекомендации по питанию.

## Запуск

```sh
make lab2
./build/cooking_cli
make test-lab2
make coverage-lab2
make docs-lab2
```

Каждый класс объявлен в отдельном заголовке `include`, реализации находятся в `src`.
Тесты каждого предметного класса находятся в отдельном файле `tests`.
Свойства закрыты; getters дают доступ для чтения, изменение выполняется предметными операциями.
`Kitchen` связывает каталог, склад и готовые блюда. Расход рецепта атомарен: при нехватке любой
обязательной позиции состояние склада сохраняется. Склад расходует свежие партии по ближайшему сроку.
Аллергены и вегетарианские ограничения проверяются до приготовления. Масштабирование меняет количества,
но длительность шагов сохраняется. CLI позволяет отдельно завершать шаги и выдавать готовое блюдо.

## Модель

В таблице поля указаны как `тип имя`, методы — без constructors и getters.
Ассоциация считается как пара классов, связанная полем или параметром метода; повторная связь одной пары не дублируется.

| Класс | Поля | Предметные методы | Связанные классы |
|---|---|---|---|
| Quantity — Масса продукта в граммах с учётом съедобной части. | `double grams; double yield; std::string label` | `Quantity scaled(double factor) const; double edible() const; Quantity combined(const Quantity& other) const` |  |
| Nutrition — Пищевая ценность заданного количества продукта. | `double calories; double protein; double fat; double carbs` | `Nutrition for_mass(double grams) const; Nutrition combined(const Nutrition& other) const; double macro_energy() const` |  |
| Allergen — Аллерген и порог чувствительности. | `std::string name; int severity; bool trace_sensitive` | `bool matches(const std::string& ingredient_allergen) const; bool blocks(int sensitivity, bool trace) const` |  |
| Ingredient — Продукт, пищевая ценность и аллергены. | `std::string name; Nutrition nutrition; std::vector<std::string> allergens; bool vegetarian` | `Nutrition nutrition_for(const Quantity& amount) const; bool contains(const Allergen& allergen) const` | Quantity, Nutrition, Allergen |
| IngredientAmount — Строка рецепта: продукт, количество и обязательность. | `Ingredient ingredient; Quantity amount; bool optional` | `IngredientAmount scaled(double factor) const; double calories() const` | Quantity, Ingredient |
| RecipeStep — Шаг приготовления с длительностью и зависимостью. | `std::string instruction; int minutes; int prerequisite` | `bool ready(int completed_steps) const; int finish_at(int start_minute) const` |  |
| Recipe — Рецепт с составом и последовательностью шагов. | `std::string name; int servings; std::vector<IngredientAmount> ingredients; std::vector<RecipeStep> steps` | `void add_ingredient(const IngredientAmount& item); void add_step(const RecipeStep& step); Recipe scaled_to(int portions) const; double calories_per_serving() const; int duration() const` | IngredientAmount, RecipeStep |
| RecipeBook — Каталог рецептов с поиском и удалением. | `std::string title; std::vector<Recipe> recipes; int revision` | `void add(const Recipe& recipe); Recipe find(const std::string& name) const; void remove(const std::string& name)` | Recipe — Рецепт с составом и последовательностью шагов. |
| DietProfile — Ограничения питания пользователя. | `std::string person; std::vector<Allergen> forbidden; double calorie_limit; bool vegetarian` | `bool allows(const Ingredient& ingredient) const; bool accepts(const Recipe& recipe) const` | Allergen, Ingredient, Recipe |
| SubstitutionRule — Замена продукта с коэффициентом массы. | `std::string original; Ingredient replacement; double ratio` | `IngredientAmount apply(const IngredientAmount& item) const; bool compatible(const DietProfile& profile) const` | Ingredient, IngredientAmount, DietProfile |
| PortionPlan — Расчёт порций с резервом и запасом выхода. | `int guests; int reserve; double yield` | `int required() const; Recipe prepare(const Recipe& recipe) const` | Recipe — Рецепт с составом и последовательностью шагов. |
| PriceQuote — Предложение цены за килограмм продукта. | `std::string ingredient; double per_kg; int valid_until` | `double cost(const Quantity& amount, int day) const; bool cheaper_than(const PriceQuote& other) const` | Quantity — Масса продукта в граммах с учётом съедобной части. |
| ShoppingItem — Позиция закупки с количеством и ценой. | `IngredientAmount item; PriceQuote quote; int day` | `double total() const; ShoppingItem increased(double factor) const` | IngredientAmount, PriceQuote |
| ShoppingList — Список покупок с ограничением числа позиций. | `std::string title; std::vector<ShoppingItem> items; int limit` | `void add(const ShoppingItem& item); double total() const; void remove_product(const std::string& name)` | ShoppingItem — Позиция закупки с количеством и ценой. |
| Budget — Бюджет закупок и учёт возвратов. | `double limit; double spent; std::string currency` | `void pay(double amount); void refund(double amount); bool covers(const ShoppingList& list) const` | ShoppingList — Список покупок с ограничением числа позиций. |
| Supplier — Поставщик с ассортиментом и минимальной суммой заказа. | `std::string name; std::vector<PriceQuote> offers; double minimum_order` | `PriceQuote quote_for(const std::string& product) const; bool accepts(const ShoppingList& list) const` | PriceQuote, ShoppingList |
| PurchaseOrder — Заказ поставщику с оплатой и отменой. | `Supplier supplier; ShoppingList list; bool paid; bool cancelled` | `void submit(Budget& budget); void cancel(Budget& budget)` | ShoppingList, Budget, Supplier |
| Delivery — Приёмка поставки по дате и температуре. | `PurchaseOrder order; int arrival_day; double temperature; bool accepted` | `bool on_time(int promised_day) const; void accept(double maximum_temperature)` | PurchaseOrder — Заказ поставщику с оплатой и отменой. |
| InventoryBatch — Партия продукта со сроком годности. | `Ingredient ingredient; double grams; int expires_day; std::string lot` | `bool usable(int day) const; void consume(double grams, int day)` | Ingredient — Продукт, пищевая ценность и аллергены. |
| Pantry — Склад: расходует сначала партии с ближайшим сроком. | `std::string name; std::vector<InventoryBatch> batches; double capacity` | `double stored() const; void receive(const InventoryBatch& batch); double available(const std::string& product, int day) const; void consume(const std::string& product, double grams, int day); void consume_recipe(const Recipe& recipe, int day)` | Recipe, InventoryBatch |
| StorageZone — Температурная зона хранения. | `std::string name; double minimum; double maximum; double temperature` | `bool suitable() const; void adjust(double delta)` |  |
| FoodSafetyRule — Учебное правило проверки продукта, не медицинская рекомендация. | `double min_temperature; double max_temperature; int max_open_days` | `bool permits(const StorageZone& zone, int open_days) const; void check(const InventoryBatch& batch, int day) const` | InventoryBatch, StorageZone |
| WasteRecord — Учёт списания продукта и стоимости потерь. | `Ingredient ingredient; Quantity amount; std::string reason` | `double loss(const PriceQuote& quote, int day) const; double fraction_of(const Quantity& purchased) const` | Quantity, Ingredient, PriceQuote |
| KitchenTool — Инструмент с вместимостью и обязательной мойкой. | `std::string name; double capacity; bool clean` | `void use(const Quantity& amount); void wash()` | Quantity — Масса продукта в граммах с учётом съедобной части. |
| Oven — Духовка: нагрев, проверка режима и остывание. | `double temperature; double maximum; bool powered` | `void preheat(double target); bool ready_for(double required) const; void cool(double room_temperature)` |  |
| Timer — Таймер шага приготовления. | `int remaining; bool running; int elapsed` | `void start(); void tick(int minutes)` |  |
| SkillProfile — Квалификация повара по техникам. | `std::string speciality; int level; int practice_hours` | `void practice(int hours); bool qualifies(const std::string& technique, int required_level) const` |  |
| Chef — Повар с навыками и доступным рабочим временем. | `std::string name; SkillProfile skills; int available_minutes` | `void assign(const Recipe& recipe); bool can_cook(const std::string& technique, int level) const` | Recipe, SkillProfile |
| Workstation — Рабочее место и занятость. | `std::string name; KitchenTool tool; bool occupied` | `void reserve(const Quantity& quantity); void release()` | Quantity, KitchenTool |
| Task — Задание повару с крайним сроком. | `Recipe recipe; int deadline; bool completed` | `bool fits(int start) const; void complete(int finish)` | Recipe — Рецепт с составом и последовательностью шагов. |
| Assignment — Назначение задания повару и месту. | `Chef chef; Task task; Workstation station; bool started` | `void start(int minute); void finish(int minute)` | Chef, Workstation, Task |
| Schedule — План заданий с проверкой общего времени. | `std::string day; std::vector<Task> tasks; int shift_minutes` | `int workload() const; void add(const Task& task)` | Task — Задание повару с крайним сроком. |
| Dish — Готовое блюдо с количеством оставшихся порций. | `Recipe recipe; int remaining; int cooked_day` | `void serve(int portions); double calories_for(int portions) const` | Recipe — Рецепт с составом и последовательностью шагов. |
| CookingSession — Приготовление по шагам с безопасным расходом склада. | `Recipe recipe; int next_step; bool started; int day` | `void begin(Pantry& pantry); void complete_step(); Dish finish() const` | Recipe, Pantry |
| PlatingRule — Норма подачи по массе и украшению. | `std::string style; double portion_grams; double garnish_grams` | `Quantity for_guests(int count) const; int plates_from(const Quantity& cooked) const` | Quantity — Масса продукта в граммах с учётом съедобной части. |
| MenuItem — Позиция меню и цена порции. | `Recipe recipe; double price; bool enabled` | `double charge(int portions) const; bool suitable(const DietProfile& profile) const` | Recipe, DietProfile |
| Menu — Меню с подбором по рациону. | `std::string title; std::vector<MenuItem> items; int max_items` | `void add(const MenuItem& item); std::vector<MenuItem> select(const DietProfile& profile) const` | DietProfile, MenuItem |
| MealPlan — План питания с суммированием калорий. | `DietProfile profile; std::vector<Recipe> meals; double daily_limit` | `double calories() const; void add(const Recipe& recipe)` | Recipe, DietProfile |
| Serving — Выдача блюда гостю с проверкой диеты. | `Dish dish; DietProfile guest; int delivered` | `void deliver(int portions); double delivered_calories() const` | DietProfile, Dish |
| Feedback — Отзыв о блюде. | `std::string dish; int score; std::string comment` | `bool needs_attention() const; bool refers_to(const Recipe& recipe) const` | Recipe — Рецепт с составом и последовательностью шагов. |
| RatingSummary — Средняя оценка конкретного рецепта. | `Recipe recipe; std::vector<Feedback> feedback; int minimum_reviews` | `void add(const Feedback& item); double average() const` | Recipe, Feedback |
| CostEstimate — Себестоимость блюда: продукты, труд и накладные расходы. | `ShoppingList products; double labor_per_minute; double overhead` | `double total(const Recipe& recipe) const; double per_serving(const Recipe& recipe) const` | Recipe, ShoppingList |
| UnitConversion — Перевод массы в объём по плотности. | `Ingredient ingredient; double grams_per_ml; std::string volume_unit` | `double volume_for(const Quantity& amount) const; Quantity mass_for(double volume) const` | Quantity, Ingredient |
| SeasoningBlend — Смесь приправ с нормой дозировки. | `std::string name; std::vector<IngredientAmount> components; double grams_per_kg` | `Quantity dose(const Quantity& food) const; double component_share(const std::string& name) const` | Quantity, IngredientAmount |
| Marinade — План маринования по массе и времени. | `SeasoningBlend blend; int minutes_per_kg; double liquid_ratio` | `int duration(const Quantity& food) const; Quantity liquid_for(const Quantity& food) const` | Quantity, SeasoningBlend |
| Dough — Тесто: гидратация и масса. | `Quantity flour; Quantity water; Quantity salt` | `double hydration() const; Quantity total_mass() const; Dough scaled(double factor) const` | Quantity — Масса продукта в граммах с учётом съедобной части. |
| Fermentation — Учебная оценка готовности теста по времени. | `Dough dough; int required_minutes; int elapsed_minutes` | `void advance(int minutes); bool ready() const; double progress() const` | Dough — Тесто: гидратация и масса. |
| BakingProfile — Режим выпечки и проверка духовки. | `std::string name; double temperature; int minutes` | `void prepare(Oven& oven) const; int finish_at(int start) const` | Oven — Духовка: нагрев, проверка режима и остывание. |
| TemperatureLog — Журнал замеров температуры оборудования. | `std::string equipment; std::vector<double> readings; double maximum` | `void record(double value); double average() const` |  |
| CleaningTask — Мойка инструмента с учётом времени. | `KitchenTool tool; int required_minutes; int spent_minutes` | `void work(int minutes); KitchenTool finish() const` | KitchenTool — Инструмент с вместимостью и обязательной мойкой. |
| Kitchen — Кулинарная мастерская: каталог, склад и готовые блюда. | `RecipeBook book; Pantry pantry; std::vector<Dish> dishes; int day` | `void register_recipe(const Recipe& recipe); void stock(const InventoryBatch& batch); Recipe plan(const std::string& name, int portions, const DietProfile& profile) const; void cook(const std::string& name, int portions, const DietProfile& profile); void next_day()` | Recipe, RecipeBook, DietProfile, InventoryBatch, Pantry, Dish |

| KitchenArchive | `int version; int max_recipes; int max_entries` | `save(Kitchen, ostream); load(istream)` | Kitchen — Кулинарная мастерская: каталог, склад и готовые блюда. |

## Ошибки

- `CookingError` — базовый тип ошибок кулинарной модели.
- `InvalidQuantityError` — неконечное, отрицательное или недопустимое количество.
- `IngredientError` — неверные данные продукта или несовместимая замена.
- `RecipeError` — неверные порции, шаги, состав или отсутствующий рецепт.
- `AllergyError` — рецепт не соответствует ограничениям питания.
- `StockError` — нехватка свежего продукта или повторный номер партии.
- `ExpiredFoodError` — попытка использовать просроченный продукт.
- `StorageError` — переполнение склада или неверные условия хранения.
- `BudgetError` — недостаток средств или некорректный возврат.
- `OrderError` — недоступное предложение, заказ или позиция меню.
- `EquipmentError` — инструмент не готов, превышена вместимость или температура.
- `WorkflowError` — нарушение порядка шагов, выдачи или расписания.
- `SerializationError` — ошибка записи, повреждённый архив или неподдерживаемый формат.

Предметных классов: **52**. Полей: **167**. Предметных методов: **122**. Ассоциаций: **78**. Собственных исключений: **13**.

[Задание](https://github.com/alix-zzh/ppois-course/blob/master/ru/lab2.md)

Сохранение через меню записывает каталог рецептов и партии склада. Готовые блюда, бюджет, диета и текущая сессия в архив не входят. Загрузка полностью проверяет временное состояние; повреждённый файл не меняет кухню. Формат: COOKING 1, строки в кавычках, даты и количества.

## Быстрая проверка меню

Сразу после запуска есть рецепт «Каша» и запас овса и молока.
1. Пункт 1 показывает рецепты.
2. Пункт 3, название `Каша`, 4 порции — показывает 200 г овса, 400 г молока и 230 ккал на порцию.
3. Пункт 7, `Каша`, 2 порции — начинает приготовление и списывает продукты.
4. Пункт 8 два раза — завершает два шага и создаёт блюдо.
5. Пункт 11, блюдо 1, одна порция — выдаёт порцию.
6. Пункты 13 и 14 сохраняют и загружают рецепты и склад.
Для выхода — 0. На Mac скачанная сборка может потребовать разрешения через «Конфиденциальность и безопасность».
