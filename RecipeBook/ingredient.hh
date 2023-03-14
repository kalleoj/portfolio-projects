#ifndef INGREDIENT_HH
#define INGREDIENT_HH

#include "searchable.hh"

#include <string>

const int UNKNOWN_CALORIES = -1;

/**
 * @brief The Ingredient class is a
 */
class Ingredient : public Searchable
{
public:
    Ingredient(std::string name);

    Ingredient(std::string name, int calories);

    virtual ~Ingredient() {};

    int getCalories() const;
    void setCalories(int calories);

    std::string getName() const override;



private:
    std::string name_;
    int calories_;

};

#endif // INGREDIENT_HH
