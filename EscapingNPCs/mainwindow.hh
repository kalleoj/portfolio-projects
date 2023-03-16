#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gamedisplay.hh"

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct ActiveCommand {
    Direction playerDirection;
    Direction enemyDirection;
};

struct DirectionCommand {
    Direction direction;
    Direction oppositeDirection;
    vector<Qt::Key> keys;
};

const vector<DirectionCommand> DIRECTION_COMMANDS = {
    // Direction, opposite, {key1, ...}
    {Left, Right, {Qt::Key_Left, Qt::Key_A}},
    {Right, Left, {Qt::Key_Right, Qt::Key_D}},
    {Up, Down, {Qt::Key_Q, Qt::Key_Space}},
    {Down, Up, {Qt::Key_E}},
    {Front, Back, {Qt::Key_W, Qt::Key_Up}},
    {Back, Front, {Qt::Key_Left, Qt::Key_A}},
    {None, Right, {}}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void advanceGame();

    void toggleGamePaused();


protected:
  void keyPressEvent(QKeyEvent *event);

public slots:
    void startGame();

signals:
    void keyPressed(QKeyEvent* key);

private:
    Ui::MainWindow *ui;
    GameDisplay* game_;
    QTimer* gameClock_;
    bool paused_;
    ActiveCommand activeCommand_;

    Direction keyToDirection(Qt::Key &key) const;
    void handleKeyEvent(QKeyEvent* event);
};
#endif // MAINWINDOW_HH
