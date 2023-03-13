#include "recipe.hh"


Recipe::Recipe(std::string name, RecipeDetails recipeDetails) :
    Searchable(), name_(name), recipeDetails_(recipeDetails)
{

}

Recipe::Recipe(Recipe const &recipe) :
    Searchable(),
    name_(recipe.getName()),
    recipeDetails_(recipe.getDetails())
{
}

std::string Recipe::getName() const
{
    return name_;
}


RecipeDetails Recipe::getDetails() const
{
    return recipeDetails_;
}
