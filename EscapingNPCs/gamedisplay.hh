#ifndef GAMEDISPLAY_HH
#define GAMEDISPLAY_HH

#include "game.hh"

#include <QMatrix4x4>
#include <QWidget>
#include <QPainter>
#include <QVector3D>
#include <QTransform>

const unsigned int GAME_WIDTH = 5;
const unsigned int GAME_LENGTH = 5;
const unsigned int GAME_HEIGHT = 5; // TODO: ANALYZE IF THESE HAVE TO BE EQUAL


class GameDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GameDisplay(QWidget* parent = nullptr);
    ~GameDisplay();
    void paintEvent(QPaintEvent* event) override;

signals:

private:
    Game* game_;
    QTransform isometricTransform_ = QTransform();
    std::vector<std::vector<QRect>> isoGrid;

    void displayPlane(Plane plane, QPainter &painter, unsigned int zValue = 0) const;

};

#endif // GAMEDISPLAY_HH
