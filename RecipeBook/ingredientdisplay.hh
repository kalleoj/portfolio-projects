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
            Ingredient* ingredient,
            QString amount,
            DataHandler* dataHandler,
            bool editable = true,
            QWidget *parent = nullptr
    );

    QString getIngredientInfo() const;


private:

    bool editable_;

    QHBoxLayout* layout_;

    void createNameLabel(Ingredient *name, bool editable);
    void createAmountLabel(QString amount, bool editable);
    void createCalorieLabel(int amount, bool editable);
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
