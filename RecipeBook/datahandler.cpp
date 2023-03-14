#include "datahandler.hh"

#include <QString>


DataHandler::DataHandler()
{
    allIngredients_ = {};
    allRecipes_ = {};

}

DataHandler::~DataHandler()
{
    for ( std::pair<std::string, Recipe*> pair : allRecipes_) {
        delete pair.second;
        pair.second = nullptr;
    }

    for ( std::pair<std::string, Ingredient*> pair : allIngredients_) {
        delete pair.second;
        pair.second = nullptr;
    }
}

std::map<std::string, Recipe*> DataHandler::getRecipes() const
{
    return allRecipes_;
}

std::map<std::string, Recipe*> DataHandler::loadRecipes()
{
    // create file if a previous one does not exist
    std::ofstream outputfile(RECIPE_FILE_PATH);
    if (!outputfile) {
        throw std::ofstream::failure("Could not open or create recipe file: " + RECIPE_FILE_PATH);
    }
    outputfile.close();

    std::ifstream file(RECIPE_FILE_PATH);
    std::string line;
    while (std::getline(file, line)) {
        assert(addRecipe(line));
    }

    file.close();

    return allRecipes_;

}

bool DataHandler::recipeExists(std::string name) const
{
    return allRecipes_.find(name) != allRecipes_.end();
}

std::vector<Searchable*> DataHandler::searchRecipes(std::string subString) const
{


    auto it = allRecipes_.lower_bound(subString);
    if (it == allRecipes_.end()) {
        return {};
    }


    // add recipes to vector and return them
    std::vector<Searchable*> recipes;
    while (it != allRecipes_.end() && it->first.substr(0, subString.length()) == subString) {

        recipes.push_back(it->second);
        it++;

    }


    return recipes;
}

std::map<std::string, Ingredient*> DataHandler::getIngredients() const
{
    return allIngredients_;
}

std::map<std::string, Ingredient*> DataHandler::loadIngredients()
{
    // create file if a previous one does not exist
    std::ofstream outputfile(INGREDIENTS_FILE_PATH);
    if (!outputfile) {
        throw std::ofstream::failure("Could not open or create ingredient file: " + INGREDIENTS_FILE_PATH);
    }
    outputfile.close();

    std::ifstream file(INGREDIENTS_FILE_PATH);
    std::string line;
    while (std::getline(file, line)) {
        //assert(addRecipe(line));
    }

    file.close();

    return allIngredients_;
}

std::vector<Searchable*> DataHandler::searchIngredients(std::string subString) const
{

    auto it = allIngredients_.lower_bound(subString);
    if (it == allIngredients_.end()) {
        return {};
    }

    // add recipes to vector and return them
    std::vector<Searchable*> ingredients;
    while (it != allIngredients_.end() && it->first.substr(0, subString.length()) == subString) {

        ingredients.push_back(it->second);
        it++;

    }

    return ingredients;
}

bool DataHandler::ingredientExists(std::string name) const
{
    return allIngredients_.find(name) != allIngredients_.end();
}

Ingredient* DataHandler::addIngredient(std::string name) {
    if (ingredientExists(name)) {
        return allIngredients_.at(name);
    }

    Ingredient* ingredient = new Ingredient(name);
    allIngredients_.insert({name, ingredient});
    return ingredient;
}


std::vector<std::string> DataHandler::parseCSVLine(std::string line) const
{
    std::vector<std::string> parts;

    std::string part = "";
    for (char character : line) {
        if (character != ',') {
            part += character;
        } else if (part != "") {
            parts.push_back(part);
            part = "";
        }
    }

    if (part != "") {
        parts.push_back(part);
    }

    return parts;
}

bool DataHandler::isNumber(std::string str) const {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}
/**
 * @brief DataHandler::addRecipe - extract data in a string in the following format:
 *        name,ingredient name, amount, ingredient name, amount, ingredient name, amount, ...
 *        Also saves any new ingredients whether or not adding the recipe is possbile
 * @param line is the string from which the data is extracted
 * @return boolean signaling whether adding the ingredient was successful
 */
bool DataHandler::addRecipe(std::string line)
{

    std::vector<std::string> recipeData = parseCSVLine(line);


    // must have one entry for recipe name and one for each ingredient property
    assert(recipeData.size() % INGREDIENT_DATA_ENTRY_SIZE == 1);
    std::string name = recipeData.at(0);

    // search and if neceassry create ingredients
    std::map<std::string, std::pair<Ingredient*, std::string>> ingredients;
    for (int i = 1; i < (int) recipeData.size(); i += INGREDIENT_DATA_ENTRY_SIZE) {

        std::string ingredientName = recipeData.at(i);
        std::string ingredientAmount = recipeData.at(i+1);
        std::string ingredientCaloriesStr = recipeData.at(i+2);
        assert(isNumber(ingredientCaloriesStr) || ingredientCaloriesStr == "");

        int ingredientCalories = UNKNOWN_CALORIES;
        if (ingredientCaloriesStr != "") {
            ingredientCalories = stoi(ingredientCaloriesStr);
        }


        // Add ingredient data to the ingredient list of the recipe
        // and make sure ingredient is in the list of all known ingredients
        if (ingredientExists(ingredientName)) {

            Ingredient* ingredient = allIngredients_.at(ingredientName);
            ingredient->setCalories(ingredientCalories);
            ingredients.insert({ingredientName, {ingredient, ingredientAmount}});

        } else {

            Ingredient* ingredient = new Ingredient(ingredientName, ingredientCalories);
            allIngredients_.insert({ingredientName, ingredient});
            ingredients.insert({ingredientName, {ingredient, ingredientAmount}});

        }
    }

    // add recipe if one by the same name exists
    if (!recipeExists(name)) {
        allRecipes_.insert({name, new Recipe(name, ingredients)});
        return true;
    }

    return false;

}

bool DataHandler::addRecipe(Recipe recipe)
{
    if (!recipeExists(recipe.getName())) {
        allRecipes_.insert({recipe.getName(), new Recipe(recipe)});
        return true;
    }

    return false;
}
