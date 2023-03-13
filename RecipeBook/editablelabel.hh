#ifndef EDITABLELABEL_HH
#define EDITABLELABEL_HH

#include "datahandler.hh"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

// used for the search function
using FunctionType = std::vector<Searchable*>(DataHandler::*)(std::string) const;

struct SearchFunctionInfo {
    DataHandler* object;
    FunctionType function;
};

// interval that determines how often look-ups are to be made
const int LOOKUP_INTERVAL = 500;

/**
 * @brief The EditableLabel class is a label that can be edited and that can display search suggestions
 *        with the help of a given search function.
 */
class EditableLabel : public QWidget
{
    Q_OBJECT
public:

    explicit EditableLabel(
            QString defaultName,
            QString placeholder,
            QWidget *parent = nullptr,
            SearchFunctionInfo searchFunctionInfo = {nullptr, nullptr}
            );

    ~EditableLabel();

    // getters and setters
    QString getText() const;
    void setText(QString text);

    // returns the label to a default value
    void returnToDefault();
private:
    QLabel* label;
    QString defaultText_;
    QString placeholder_;

    DataHandler* dataHandler_;
    FunctionType searchFunction_;
    std::vector<QWidget*> searchResults_;
    QElapsedTimer* lookupTimer = new QElapsedTimer();

    void resetLookup();


signals:
    void clicked();
    void textEditingFinished(QString oldText, QString newText);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        QWidget::mousePressEvent(event);
        emit clicked();
    }

    QLineEdit* lineEdit;
    QVBoxLayout* mainLayout;



public slots:
    void startEditing();
    void stopEditing();


};

#endif // EDITABLELABEL_HH
