#ifndef VIEWRECIPESTAB_HH
#define VIEWRECIPESTAB_HH

#include <QVBoxLayout>
#include <QWidget>

#include "datahandler.hh"
#include "editablelabel.hh"
#include "recipedisplay.hh"

class ViewRecipesTab : public QWidget
{
    Q_OBJECT
public:
    explicit ViewRecipesTab(DataHandler* dataHandler, QWidget *parent = nullptr);
    void reload();
    void displayRecipes();
private:
    QVBoxLayout* mainLayout_;
    DataHandler* dataHandler_;

signals:

};

#endif // VIEWRECIPESTAB_HH
