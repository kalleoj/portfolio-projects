#ifndef RECIPEDISPLAY_HH
#define RECIPEDISPLAY_HH

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

#include "recipe.hh"


class RecipeDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit RecipeDisplay(Recipe* recipe, QWidget *parent = nullptr);

private:
    Recipe* recipe_;

signals:

};

#endif // RECIPEDISPLAY_HH
