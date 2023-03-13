#include "addrecipetab.hh"
#include "clickablelabel.hh"

#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyle>
#include <QFileDialog>
#include <QResource>

AddRecipeTab::AddRecipeTab(
        DataHandler* dataHandler,
        QWidget *parent
    ) : QWidget(parent), dataHandler_(dataHandler)
{

    // register resources file
    QResource::registerResource("./resources.qrc");

    // create layout on top that contains the recipe icon and the editable recipe name
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    topLayout->setAlignment(Qt::AlignLeft);

    // editable label for the recipe name
    EditableLabel* recipeNameLabel = createRecipeNameLabel();
    topLayout->addWidget(recipeNameLabel);

    // changeable image for the recipe
    ClickableLabel* imageLabel = createImageLabel();
    topLayout->addWidget(imageLabel);

    // layout where all the added ingredients reside
    ingredientsLayout = new QVBoxLayout(this);

    // create ingredient inputs
    QHBoxLayout* inputsLayout = createIngredientInputs();

    // button that finishes editing the recipe
    QPushButton* addButton = new QPushButton("Add recipe");
    connect(addButton, &QPushButton::pressed, this, &AddRecipeTab::onAddButtonPressed);

    // add all the layouts to the main layout
    mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(ingredientsLayout);
    mainLayout->addLayout(ingredientsLayout);
    mainLayout->addWidget(addButton);


    setLayout(mainLayout);

}

std::string AddRecipeTab::getRecipeData() const {

    std::string dataCSV = "";
    QString recipeName = recipeNameLabel->getText();
    assert (!recipeName.isEmpty());

    // add recipe name
    dataCSV += recipeName.toStdString() + ",";

    // add ingredient info in csv format from the ingredient display and separate each triplet with a comma
    for (std::pair<QString, IngredientDisplay*> ingredientInfo : ingredients_) {
        dataCSV += ingredientInfo.second->getIngredientInfo().toStdString() + ",";
    }

    // remove final comma
    dataCSV = dataCSV.substr(0, dataCSV.length()-1);

    return dataCSV;
}

void AddRecipeTab::addIngredientToRecipe()
{
    QString name = nameInput->text();
    QString amount = amountInput->text();
    QString calories = calorieInput->text();

    if (name == "") {
        return;

    } else if (ingredients_.find(name) != ingredients_.end()) {
        new ErrorPopup("Ingredient already added!", this);
        return;

    } else if (!isNumber(calories.toStdString())) {
        new ErrorPopup("The amount of calories needs to be numerical!", this);
        return;

    }

    nameInput->setText("");
    amountInput->setText("");
    calorieInput->setText("");

    IngredientDisplay* ingredientProperties = new IngredientDisplay(
                name,
                dataHandler_,
                this,
                amount,
                calories
                );


    connect(ingredientProperties, &IngredientDisplay::deleted, this, [=](QString ingredientName){
        ingredients_.erase(ingredientName);
    });


    ingredientsLayout->addWidget(ingredientProperties);

    ingredients_.insert({name, ingredientProperties});

}

QHBoxLayout* AddRecipeTab::createIngredientInputs()
{
    QHBoxLayout* inputLayout = new QHBoxLayout(this);

    // create label and input for the name
    QVBoxLayout* nameLayout = new QVBoxLayout(this);
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Garlic");
    nameLayout->addWidget(new QLabel("Ingredient name", this));
    nameLayout->addWidget(nameInput);

    // create label and input for the
    QVBoxLayout* amountLayout = new QVBoxLayout(this);
    amountInput = new QLineEdit(this);
    amountInput->setPlaceholderText("3 cloves");
    amountLayout->addWidget(new QLabel("Amount", this));
    amountLayout->addWidget(amountInput);

    QVBoxLayout* calorieLayout = new QVBoxLayout(this);
    calorieInput = new QLineEdit(this);
    calorieInput->setPlaceholderText("33");
    calorieLayout->addWidget(new QLabel("Calories per unit (optional)", this));
    calorieLayout->addWidget(calorieInput);

    QPushButton* addButton = new QPushButton("Add Ingredient");
    connect(addButton, &QPushButton::pressed, this, &AddRecipeTab::addIngredientToRecipe);

    inputLayout->addLayout(nameLayout);
    inputLayout->addLayout(amountLayout);
    inputLayout->addLayout(calorieLayout);
    inputLayout->addWidget(addButton);

    return inputLayout;

}

ClickableLabel *AddRecipeTab::createImageLabel()
{
    ClickableLabel* imageLabel = new ClickableLabel(this);
    imageLabel->setPixmap(QPixmap(":/images/pizza.png"));

    connect(imageLabel, &ClickableLabel::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Select Icon File"),
                    QDir::homePath(),
                    tr("Icon files (*.png);")
        );
        QResource::registerResource(fileName);

        imageLabel->setPixmap(QPixmap(fileName));

    });

    return imageLabel;
}

EditableLabel* AddRecipeTab::createRecipeNameLabel()
{
    SearchFunctionInfo info = {
        dataHandler_,
        &DataHandler::searchRecipes
    };
    recipeNameLabel = new EditableLabel(
                "Recipe name",
                "Name your recipe",
                this,
                info
    );
    connect(recipeNameLabel, &EditableLabel::textEditingFinished, this, [=](QString oldName, QString newName){
        if (dataHandler_->recipeExists(newName.toStdString())) {
            recipeNameLabel->setText(oldName);

            new ErrorPopup("A recipe by the name" + newName + "already exists!", this);
        }
    });

    return recipeNameLabel;
}

void AddRecipeTab::onAddButtonPressed()
{

    dataHandler_->addRecipe(
        getRecipeData()
    );
    clearTab();
    emit recipeAdded();

}

bool AddRecipeTab::isNumber(std::string string) const
{
    for (char c : string) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

void AddRecipeTab::clearTab()
{
    // Editable label for the recipe name
    recipeNameLabel->returnToDefault();
    // Inputs for ingredient properties
    nameInput->setText("");
    amountInput->setText("");
    calorieInput->setText("");

    for (auto item : ingredients_) {
        delete item.second;
        ingredients_.erase(item.first);
    }

}
