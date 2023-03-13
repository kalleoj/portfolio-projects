#include "editablelabel.hh"
#include "ingredientdisplay.hh"

#include <QHBoxLayout>
#include <QPushButton>

IngredientDisplay::IngredientDisplay(
        QString name,
        DataHandler* dataHandler,
        QWidget *parent,
        QString amount,
        QString calories
        ) : QWidget(parent), dataHandler_(dataHandler)
{
    assert(isNumber(calories.toStdString()) or calories == NO_VALUE);

    layout_ = new QHBoxLayout(this);

    createNameLabel(name);

    createAmountLabel(amount);

    createCalorieLabel(calories);

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

void IngredientDisplay::createNameLabel(QString name)
{
    SearchFunctionInfo info = {
        dataHandler_,
        &DataHandler::searchIngredients
    };
    nameLabel_ = new EditableLabel(
                name,
                "Rename ingredient",
                this,
                info
                );
    layout_->addWidget(nameLabel_);
}

void IngredientDisplay::createAmountLabel(QString amount)
{
    QString placeholder = "Redefine amount";
    if (amount == NO_VALUE) {
        placeholder = "Define amount";
    }
    amountLabel_ = new EditableLabel(amount, placeholder, this);
    layout_->addWidget(amountLabel_);
}

void IngredientDisplay::createCalorieLabel(QString calories)
{
    QString placeholder = "Redefine calories";
    if (calories == NO_VALUE) {
        placeholder = "Define calories";
    }
    calorieLabel_ = new EditableLabel(calories, placeholder, this);
    connect(calorieLabel_, &EditableLabel::textEditingFinished, this, [=](QString oldCalories, QString newCalories){
        if (newCalories != "" and !isNumber(newCalories.toStdString())) {
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
