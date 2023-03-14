#include "ingredient.hh"

#include <assert.h>

Ingredient::Ingredient(std::string name) :
    Searchable(), name_(name), calories_(UNKNOWN_CALORIES) {

}

Ingredient::Ingredient(std::string name, int calories) :
    Searchable(), name_(name), calories_(calories)
{
    assert(calories >= 0 || calories == UNKNOWN_CALORIES);
}

int Ingredient::getCalories() const
{
    return calories_;
}

void Ingredient::setCalories(int calories)
{
    assert(calories >= 0 || calories == UNKNOWN_CALORIES);
    calories_ = calories;
}

std::string Ingredient::getName() const
{
    return name_;
}
