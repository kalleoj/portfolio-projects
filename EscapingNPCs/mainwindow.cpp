#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gamedisplay.hh"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      game_(new GameDisplay(this)),
      gameClock_(new QTimer(this)),
      activeCommand_({None, None}),
      paused_(false)
{
    qDebug() << "here";

    ui->setupUi(this);
    qDebug() << "here";

    connect(this, &MainWindow::keyPressed, this, &MainWindow::handleKeyEvent);


    // create display for the game
    QVBoxLayout* gameLayout = new QVBoxLayout(this);
    gameLayout->addWidget(game_);

    // Create a central widget and set the layout on it
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(gameLayout);

    // Set the central widget of the MainWindow
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::advanceGame()
{
    //emit GameDisplay::paintEvent(); // TODO SOMETHING LIKE THIS
}

void MainWindow::toggleGamePaused()
{
    if (paused_) {
        gameClock_->stop();
    } else {
        gameClock_->start();
    }

    paused_ = !paused_;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressed(event);
}

void MainWindow::startGame()
{
    connect(
        gameClock_,
        &QTimer::timeout,
        this,
        [=](){
            advanceGame();
        }

            );

    gameClock_->start(1000);
}



Direction MainWindow::keyToDirection(Qt::Key& pressedKey) const
{
    for (DirectionCommand direction_command : DIRECTION_COMMANDS) {
        for (Qt::Key key : direction_command.keys) {
            if (pressedKey == key) {

                // return key-derived direction, unless the current direction is opposite
                if (activeCommand_.playerDirection != direction_command.oppositeDirection) {
                    return direction_command.direction;
                } else {
                    return None;
                }
            }
        }
    }

    return None;
}

void MainWindow::handleKeyEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter) {
        toggleGamePaused();
        return;
    }
    // hmm why on earth does it require me to do this
    Qt::Key key = static_cast<Qt::Key>(event->key());

    //change player direction
    activeCommand_.playerDirection = keyToDirection(key);
}

