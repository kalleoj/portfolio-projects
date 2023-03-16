#include "gamedisplay.hh"
#include "grass.hh"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygon>
#include <QTransform>





GameDisplay::GameDisplay(QWidget *parent) :
    QWidget(parent),
    game_(new Game(GAME_WIDTH, GAME_LENGTH, GAME_HEIGHT))
{


}

GameDisplay::~GameDisplay()
{
    delete game_;
}

void GameDisplay::paintEvent(QPaintEvent *event)
{
    QPainter painter = QPainter(this);


    Plane ground = game_->getSpace().at(0);
    displayPlane(ground, painter, 0);

    Plane offGround = game_->getSpace().at(1);
    displayPlane(offGround, painter, 1);




}

void GameDisplay::displayPlane(Plane plane, QPainter& painter, unsigned int zValue) const {

    painter.setPen(Qt::green);
    painter.setBrush(Qt::blue);

    const int canvasWidth = 600;
    const int diamondWidth = canvasWidth / GAME_WIDTH;
    const int diamondHeight = diamondWidth / 2;

    // get the shape of the top of a cube
    QList leftPoints = {
        QPoint(0, diamondHeight / 2),
        QPoint(diamondWidth / 2, diamondHeight),
        QPoint(diamondWidth / 2, 2*diamondHeight),
        QPoint(0, 3 * diamondHeight / 2)
    };
    QPolygon leftFace(leftPoints);

    QList rightPoints = {
        QPoint(diamondWidth/2, diamondHeight),
        QPoint(diamondWidth, diamondHeight/2),
        QPoint(diamondWidth, 3*diamondHeight/2),
        QPoint(diamondWidth/2, 2 * diamondHeight)
    };
    QPolygon rightFace(rightPoints);

    // get the shape of the top of a cube
    QList topPoints = {
        QPoint(diamondWidth / 2, 0),
        QPoint(diamondWidth, diamondHeight / 2),
        QPoint(diamondWidth / 2, diamondHeight),
        QPoint(0, diamondHeight / 2)
    };
    QPolygon topFace(topPoints);

    // center the diamonds
    topFace.translate(canvasWidth/2, canvasWidth/2/2);
    leftFace.translate(canvasWidth/2, canvasWidth/2/2);
    rightFace.translate(canvasWidth/2, canvasWidth/2/2);

    // move according to zValue
    topFace.translate(0, -diamondHeight*zValue);
    leftFace.translate(0, -diamondHeight*zValue);
    rightFace.translate(0, -diamondHeight*zValue);



    for (const Column& column : plane) {
        for (SpaceCube* groundCube : column) {

            painter.setBrush(Qt::NoBrush);
            painter.setPen(Qt::NoPen);

            for (auto occupant : groundCube->getOccupants()) {
                if (dynamic_cast<Avatar*>(occupant) != nullptr) {
                    painter.setBrush(Qt::red);
                    painter.setPen(Qt::darkRed);
                    break;
                } else if (dynamic_cast<Grass*>(occupant) != nullptr) {
                    painter.setBrush(Qt::green);
                    painter.setPen(Qt::darkGreen);
                }
            }

            painter.drawConvexPolygon(topFace);
            painter.drawConvexPolygon(leftFace);
            painter.drawConvexPolygon(rightFace);

            topFace.translate(diamondWidth/2, diamondHeight/2);
            leftFace.translate(diamondWidth/2, diamondHeight/2);
            rightFace.translate(diamondWidth/2, diamondHeight/2);

        }

        topFace.translate((-diamondWidth/2)*GAME_WIDTH-diamondWidth/2, -(diamondHeight/2)*GAME_WIDTH+diamondHeight/2);
        leftFace.translate((-diamondWidth/2)*GAME_WIDTH-diamondWidth/2, -(diamondHeight/2)*GAME_WIDTH+diamondHeight/2);
        rightFace.translate((-diamondWidth/2)*GAME_WIDTH-diamondWidth/2, -(diamondHeight/2)*GAME_WIDTH+diamondHeight/2);

    }
}
