#ifndef DATAHANDLER_HH
#define DATAHANDLER_HH

#include "recipe.hh"
#include "ingredient.hh"

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <cassert>
#include <QDebug>

const std::string RECIPE_FILE_PATH = "./recipes.txt";
const int RECIPE_DATA_MINIMUM_SIZE = 3;

const std::string INGREDIENTS_FILE_PATH = "./ingredients.txt";
const int INGREDIENT_DATA_ENTRY_SIZE = 3;


/**
 * @brief The DataHandler class is a class for loading, saving and controlling access to recipe and ingredient data
 */
class DataHandler
{
public:
    DataHandler();
    ~DataHandler();

    /**
     * @brief getRecipes getter for the recipes
     * @return map with recipe name as key and a pointer to the corresponding recipe as the value
     */
    std::map<std::string, Recipe*> getRecipes() const;

    /**
     * @brief loadRecipes load the recipes from file and updates allRecipes_
     */
    std::map<std::string, Recipe *> loadRecipes();

    /**
     * @brief addRecipe add recipe given a csv of the format:
     *        <recipe name>,<ingredient name>, <ingredient amount>, <ingredient calories>, <ingredient name>, ...
     * @param line is string in csv format
     * @return boolean determining whether adding was successful
     */
    bool addRecipe(std::string line);

    /**
     * @brief addRecipe add recipe from an existing recipe
     * @param recipe
     * @return boolean determining whether adding was successful
     */
    bool addRecipe(Recipe recipe);

    /**
     * @brief recipeExists see if the recipe currently exists in the data handler.
     *        Note: the data handler does not recheck the file
     * @param name
     * @return
     */
    bool recipeExists(std::string name) const;

    /**
     * @brief getRecipesContaining gets a list of recipes containing an ingredient by the given name
     * @param ingredientName
     * @return
     */
    std::vector<Recipe*> getRecipesContaining(std::string ingredientName) const;

    /**
     * @brief searchRecipes search recipes starting with the substring subString
     * @param subString a substring that is used to look up recipe names
     * @return a vector of recipes
     */
    std::vector<Searchable*> searchRecipes(std::string subString) const;


    /**
     * @brief getIngredients returns all ingredients
     * @return a map with the ingredient name as key and pointer to the ingredient as value
     */
    std::map<std::string, Ingredient *> getIngredients() const;

    /**
     * @brief loadIngredients loads the ingredients from file and updates allIngredients_
     * @return a map with the ingredient name as key and pointer to the ingredient as value
     */
    std::map<std::string, Ingredient *> loadIngredients();

    /**
     * @brief ingredientExists checks whether an ingredient by the given name exists.
     *        Note: does not recheck the file for the ingredient.
     * @param name
     * @return
     */
    bool ingredientExists(std::string name) const;

    /**
     * @brief searchIngredients looks up a list of ingredients starting with the substring subString
     * @param subString
     * @return a vector with Searchables (can be cast to vector<Recipe*>)
     */
    std::vector<Searchable*> searchIngredients(std::string subString) const;

    /**
     * @brief addIngredient adds a new ingredient by name, if it does not already exist
     * @param name is the name of the ingredient
     * @return an ingredient by the name name
     */
    Ingredient* addIngredient(std::string name);
private:
    // separates the line on commas
    std::vector<std::string> parseCSVLine(std::string line) const;

    // checks if the string is a number
    bool isNumber(std::string string) const;

    // containers for all recipes and ingredients
    std::map<std::string, Recipe*> allRecipes_ = {};
    std::map<std::string, Ingredient*> allIngredients_ = {};

};

#endif // DATAHANDLER_HH
