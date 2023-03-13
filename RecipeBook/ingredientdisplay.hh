#ifndef INGREDIENTDISPLAY_HH
#define INGREDIENTDISPLAY_HH

#include "editablelabel.hh"
#include "ingredient.hh"

#include <QWidget>


const QString NO_VALUE = "";

class IngredientDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit IngredientDisplay(
            QString name,
            DataHandler* dataHandler,
            QWidget *parent = nullptr,
            QString amount = NO_VALUE,
            QString calories = NO_VALUE
    );

    QString getIngredientInfo() const;


private:

    QHBoxLayout* layout_;

    void createNameLabel(QString name);
    void createAmountLabel(QString amount);
    void createCalorieLabel(QString amount);
    void createDeleteButton();

    EditableLabel* nameLabel_;
    EditableLabel* amountLabel_;
    EditableLabel* calorieLabel_;

    DataHandler* dataHandler_;

    bool isNumber(std::string str) const;
signals:
    void deleted(QString name);

};

#endif // INGREDIENTDISPLAY_HH
