#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "addrecipetab.hh"
#include "editablelabel.hh"
#include "datahandler.hh"
#include "viewrecipestab.hh"
#include "errorpopup.hh"

#include <QWidget>

class  MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void init();
    ~MainWindow();

private:
    DataHandler* dataHandler;

signals:

};

#endif // MAINWINDOW_HH
