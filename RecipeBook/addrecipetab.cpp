#include "addrecipetab.hh"
#include "clickablelabel.hh"



AddRecipeTab::AddRecipeTab(
        DataHandler* dataHandler,
        QWidget *parent
    ) : QWidget(parent), dataHandler_(dataHandler)
{

    // register resources file
    QResource::registerResource("./resources.qrc");

    mainLayout_ = new QVBoxLayout(this);

    // create layout on top that contains the recipe icon and the editable recipe name
    QHBoxLayout* topLayout = new QHBoxLayout(this);
    //topLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // changeable image for the recipe
    ClickableLabel* imageLabel = createImageLabel();
    topLayout->addWidget(imageLabel);

    // editable label for the recipe name
    EditableLabel* recipeNameLabel = createRecipeNameLabel();
    topLayout->addWidget(recipeNameLabel);

    // layout where all the added ingredients reside
    ingredientsLayout = new QVBoxLayout(this);

    // create ingredient inputs
    QHBoxLayout* inputsLayout = createIngredientInputs();

    // button that finishes editing the recipe
    QPushButton* addButton = new QPushButton("Add recipe");
    connect(addButton, &QPushButton::pressed, this, &AddRecipeTab::onAddButtonPressed);

    // add all the layouts to the main layout
    mainLayout_->addLayout(topLayout);
    mainLayout_->addLayout(ingredientsLayout);
    mainLayout_->addLayout(inputsLayout);
    mainLayout_->addWidget(addButton);



    setLayout(mainLayout_);

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

    } else if (!isNumber(calories.toStdString()) && calories != NO_VALUE) {
        new ErrorPopup("The amount of calories needs to be numerical!", this);
        return;

    }

    nameInput->setText("");
    amountInput->setText("");
    calorieInput->setText("");

    Ingredient* ingredient = dataHandler_->addIngredient(name.toStdString());
    if (calories != NO_VALUE) {
        ingredient->setCalories(calories.toInt());
    }

    IngredientDisplay* ingredientProperties = new IngredientDisplay(
                ingredient,
                amount,
                dataHandler_,
                this
                );


    connect(ingredientProperties, &IngredientDisplay::deleted, this, [=](QString ingredientName){
        ingredients_.erase(ingredientName);
    });


    ingredientsLayout->addWidget(ingredientProperties);

    ingredients_.insert({name, ingredientProperties});



}

QHBoxLayout* AddRecipeTab::createIngredientInputs()
{
    QVBoxLayout* labelsLayout = new QVBoxLayout();
    QVBoxLayout* inputsLayout = new QVBoxLayout();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QHBoxLayout* amountLayout = new QHBoxLayout();
    QHBoxLayout* calorieLayout = new QHBoxLayout();

    // create labels for the inputs
    QLabel* nameLabel = new QLabel("Ingredient name", this);
    QLabel* amountLabel = new QLabel("Amount", this);
    QLabel* calorieLabel = new QLabel("Calories per unit (optional)", this);

    // create inputs for the labels
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Garlic");
    amountInput = new QLineEdit(this);
    amountInput->setPlaceholderText("3 cloves");
    calorieInput = new QLineEdit(this);
    calorieInput->setPlaceholderText("33");

    // add each label and input to the appropriate layout
    nameLayout->addWidget(nameInput);
    amountLayout->addWidget(amountInput);
    calorieLayout->addWidget(calorieInput);

    labelsLayout->addWidget(nameLabel);
    labelsLayout->addWidget(amountLabel);
    labelsLayout->addWidget(calorieLabel);

    inputsLayout->addLayout(nameLayout);
    inputsLayout->addLayout(amountLayout);
    inputsLayout->addLayout(calorieLayout);

    QPushButton* addButton = new QPushButton("Add Ingredient");
    connect(addButton, &QPushButton::pressed, this, &AddRecipeTab::addIngredientToRecipe);

    // create a layout for the inputs and button
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(labelsLayout);
    mainLayout->addLayout(inputsLayout);

    // add the button to the main layout
    mainLayout->addWidget(addButton);

    return mainLayout;

}

ClickableLabel *AddRecipeTab::createImageLabel()
{
    imageLabel_ = new ClickableLabel(this);
    imageLabel_->setScaledContents(true);
    imageLabel_->setMaximumSize(50,50);

    imageLabel_->setPixmap(QPixmap(DEFAULT_RECIPE_ICON_PATH));

    connect(imageLabel_, &ClickableLabel::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Select Icon File"),
                    QDir::homePath(),
                    tr("Icon files (*.png);")
        );

        if (fileName == "") {
            return;
        }

        QResource::registerResource(fileName);

        imageLabel_->setPixmap(QPixmap(fileName));

    });

    return imageLabel_;
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
                true,
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

    imageLabel_->setPixmap(QPixmap(DEFAULT_RECIPE_ICON_PATH));
    // Inputs for ingredient properties
    nameInput->setText("");
    amountInput->setText("");
    calorieInput->setText("");

    for (auto item : ingredients_) {
        delete item.second;
        ingredients_.erase(item.first);
    }

}
