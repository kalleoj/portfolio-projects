#ifndef CLICKABLELABEL_HH
#define CLICKABLELABEL_HH

#include <QLabel>

/**
 * @brief The ClickableLabel class is a QLabel that can send a clicked signal
 */
class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;


private:

};

#endif // CLICKABLELABEL_HH
