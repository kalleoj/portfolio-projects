
#include "mainwindow.hh"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTabWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), dataHandler(new DataHandler())
{
    // Create the tab widget
    QTabWidget *tabWidget = new QTabWidget(this);

    ViewRecipesTab* viewRecipesTab = new ViewRecipesTab(dataHandler, this);
    tabWidget->addTab(viewRecipesTab, "Recipes");

    AddRecipeTab* addRecipeTab = new AddRecipeTab(dataHandler, this);
    connect(addRecipeTab, &AddRecipeTab::recipeAdded, this, [=](){
        tabWidget->setCurrentWidget(viewRecipesTab);
        viewRecipesTab->reload();
    });
    tabWidget->addTab(addRecipeTab, "Add recipe");

    // Set the layout of the main window
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

void MainWindow::init()
{
    try {
        dataHandler->loadRecipes();
        dataHandler->loadIngredients();
    } catch (std::fstream::failure& e) {
        new ErrorPopup(e.what(), this);
        close();
    } catch (std::runtime_error& e) {
        new ErrorPopup(e.what(), this);
        close();
    }
}

MainWindow::~MainWindow()
{
    delete dataHandler;
}
