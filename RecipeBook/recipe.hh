#ifndef RECIPE_HH
#define RECIPE_HH

#include "ingredient.hh"

#include <map>
#include <vector>

using RecipeDetails = std::map<std::string, std::pair<Ingredient *, std::string> >;

class Recipe : public Searchable
{
public:
    Recipe(std::string name, RecipeDetails recipeDetails);
    Recipe(const Recipe &recipe);
    virtual ~Recipe() {};
    std::string getName() const override;
    int countCalories() const;

    RecipeDetails getDetails() const;

private:
    std::string name_;
    RecipeDetails recipeDetails_;

};

#endif // RECIPE_HH
