#include "clickablelabel.hh"

ClickableLabel::ClickableLabel(QWidget *parent) : QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
