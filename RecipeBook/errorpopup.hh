#ifndef ERRORPOPUP_HH
#define ERRORPOPUP_HH

#include <QMessageBox>
#include <QWidget>

/**
 * @brief The ErrorPopup class creates a popup that displays a given error message
 */
class ErrorPopup : public QMessageBox
{
    Q_OBJECT
public:
    ErrorPopup(QString errorMessage, QWidget* parent);
};

#endif // ERRORPOPUP_HH
