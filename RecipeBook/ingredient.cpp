#include "ingredient.hh"

Ingredient::Ingredient(std::string name) :
    Searchable(), name_(name), calories_(UNKNOWN_CALORIES) {

}

Ingredient::Ingredient(std::string name, std::string amount) :
    name_(name), calories_(UNKNOWN_CALORIES), amount_(amount) {

}

Ingredient::Ingredient(std::string name, int calories) :
    name_(name), calories_(calories)
{

}

std::string Ingredient::getName() const
{
    return name_;
}
