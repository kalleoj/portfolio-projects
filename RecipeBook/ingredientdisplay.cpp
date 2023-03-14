#include "editablelabel.hh"
#include "errorpopup.hh"
#include "ingredientdisplay.hh"

#include <QHBoxLayout>
#include <QPushButton>

IngredientDisplay::IngredientDisplay(Ingredient *ingredient,
        QString amount,
        DataHandler* dataHandler,
        bool editable,
        QWidget *parent
        ) : QWidget(parent), editable_(editable), dataHandler_(dataHandler)
{

    layout_ = new QHBoxLayout(this);

    createNameLabel(ingredient, editable_);

    createAmountLabel(amount, editable_);

    createCalorieLabel(ingredient->getCalories(), editable_);

    createDeleteButton();
}

/**
 * @brief IngredientPropertyTable::getIngredientInfo gets ingredient properties from the inputs
 * @return returns ingredient properties in  csv format
 *
 */
QString IngredientDisplay::getIngredientInfo() const
{
    return nameLabel_->getText() + "," + amountLabel_->getText() + "," + calorieLabel_->getText();
}

void IngredientDisplay::createNameLabel(Ingredient* ingredient, bool editable)
{
    SearchFunctionInfo info = {
        dataHandler_,
        &DataHandler::searchIngredients
    };
    nameLabel_ = new EditableLabel(
                QString::fromStdString(ingredient->getName()),
                "Rename ingredient",
                this,
                editable,
                info
                );
    connect(
        nameLabel_,
        &EditableLabel::textEditingFinished,
        this,
        [=](QString oldName, QString newName){
            if (dataHandler_->ingredientExists(newName.toStdString())) {
                new ErrorPopup("Such an ingredient already exists!",this);
                nameLabel_->setText(oldName);
            }
        }
    );
    layout_->addWidget(nameLabel_);
}

void IngredientDisplay::createAmountLabel(QString amount, bool editable)
{
    QString placeholder = "Redefine amount";
    if (amount == NO_VALUE) {
        placeholder = "Define amount";
    }
    amountLabel_ = new EditableLabel(
                amount,
                placeholder,
                this,
                editable
    );
    layout_->addWidget(amountLabel_);
}

void IngredientDisplay::createCalorieLabel(int calories, bool editable)
{
    QString placeholder = "Redefine calories";
    if (calories == UNKNOWN_CALORIES) {
        placeholder = "Define calories";
    }
    calorieLabel_ = new EditableLabel(
                QString(calories),
                placeholder,
                this,
                editable
    );
    connect(calorieLabel_, &EditableLabel::textEditingFinished, this, [=](QString oldCalories, QString newCalories){
        if (newCalories != "" and !isNumber(newCalories.toStdString())) {
            new ErrorPopup("The amount of calories needs to be numerical!",this);
            calorieLabel_->setText(oldCalories);
        }
    });
    layout_->addWidget(calorieLabel_);
}

void IngredientDisplay::createDeleteButton()
{
    QPushButton* deleteButton = new QPushButton("Delete");
    connect(deleteButton, &QPushButton::pressed, this, [=](){
        emit deleted(nameLabel_->getText());
        delete this;
    });
    layout_->addWidget(deleteButton);

}

bool IngredientDisplay::isNumber(std::string str) const {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}
