#include "errorpopup.hh"

ErrorPopup::ErrorPopup(QString errorMessage, QWidget *parent) : QMessageBox(parent)
{
    QMessageBox popup;
    popup.setIcon(QMessageBox::Information);
    popup.setWindowTitle("Error");
    popup.setText(errorMessage);
    popup.setStandardButtons(QMessageBox::Ok);

    popup.exec();
}
