#include "viewrecipestab.hh"

ViewRecipesTab::ViewRecipesTab(DataHandler* dataHandler, QWidget *parent) : QWidget(parent) {
    mainLayout_ = new QVBoxLayout();

    dataHandler_ = dataHandler;

    displayRecipes();

    setLayout(mainLayout_);

}

void ViewRecipesTab::reload()
{
    // delete everything from the layout
    QLayoutItem *item;
    while ((item = mainLayout_->takeAt(0)) != nullptr)
    {
        QWidget *widget = item->widget();
        if (widget)
        {
            delete widget;
        }
        delete item;
    }

    displayRecipes();

}

void ViewRecipesTab::displayRecipes()
{
    if (dataHandler_->getRecipes().size() == 0) {
        mainLayout_->addWidget(new QLabel("Looks like you do not have any recipes yet."));
        return;
    }

    // add everything agian
    for ( auto recipePair : dataHandler_->getRecipes()) {
        mainLayout_->addWidget(
                    new RecipeDisplay(recipePair.second, this)
        );
    }
}
