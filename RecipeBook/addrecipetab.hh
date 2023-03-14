#ifndef ADDRECIPETAB_HH
#define ADDRECIPETAB_HH

#include "datahandler.hh"
#include "editablelabel.hh"
#include "ingredient.hh"
#include "ingredientdisplay.hh"
#include "errorpopup.hh"
#include "clickablelabel.hh"


#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <typeinfo>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyle>
#include <QFileDialog>
#include <QResource>
#include <string>

const QString DEFAULT_RECIPE_ICON_PATH= ":/images/pizza.png";

/**
 * @brief The AddRecipeTab class represents a tab that the user uses to fill in recipe details
 */
class AddRecipeTab : public QWidget
{
    Q_OBJECT
public:
    explicit AddRecipeTab(DataHandler* dataHandler, QWidget *parent = nullptr);

    /**
     * @brief getRecipeData collects all the data from the inputs into a csv format
     * @return a string in csv format
     */
    std::string getRecipeData() const;

signals:
    /**
     * @brief recipeAdded signals that a recipe has been added
     */
    void recipeAdded();

public slots:
    /**
     * @brief addIngredientToRecipe adds an ingredient to the recipe in the form of an IngredientDisplay
     */
    void addIngredientToRecipe();

private:
    // Editable label for the recipe name
    EditableLabel* recipeNameLabel;

    // changeable icon for the image
    ClickableLabel* imageLabel_;

    // handler for adding, retrieving, loading and saving data
    DataHandler* dataHandler_;

    // Inputs for ingredient properties
    QLineEdit* nameInput;
    QLineEdit* amountInput;
    QLineEdit* calorieInput;

    // main layout
    QVBoxLayout* mainLayout_;

    // layout where all the ingredients are
    QVBoxLayout* ingredientsLayout;

    // create inputs for ingredient properties
    QHBoxLayout *createIngredientInputs();

    // create label for an icon that can have its image switched
    ClickableLabel* createImageLabel();

    // create editable label for recipe name
    EditableLabel* createRecipeNameLabel();

    // Private member function called when the user clicks the "Add" button to add a new ingredient to the recipe
    void onAddButtonPressed();

    // checks if a string is a number
    bool isNumber(std::string string) const;

    // clears all inputs and resets the recipe
    void clearTab();

    // contains all the ingredient displays
    std::map<QString, IngredientDisplay*> ingredients_;


};

#endif // ADDRECIPETAB_HH

