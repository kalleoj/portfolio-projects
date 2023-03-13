#include "recipedisplay.hh"



RecipeDisplay::RecipeDisplay(Recipe* recipe, QWidget *parent) : QWidget(parent)
{
    assert(recipe != nullptr);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(
        new QLabel("Recipe name: " + QString::fromStdString(recipe->getName()))
    );

    for (auto item : recipe->getDetails()) {
        layout->addWidget(
            new QLabel(QString::fromStdString("-" + item.first + ": " + item.second.second))
        );
    }
}
