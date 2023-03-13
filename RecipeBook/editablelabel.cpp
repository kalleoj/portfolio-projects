#include "clickablelabel.hh"
#include "editablelabel.hh"

#include <QTimer>
#include <QVBoxLayout>

EditableLabel::EditableLabel(
        QString defaultName,
        QString placeholder,
        QWidget *parent,
        SearchFunctionInfo searchFunctionInfo
    ) :
    QWidget(parent),
    defaultText_(defaultName),
    placeholder_(placeholder),
    dataHandler_(searchFunctionInfo.object),
    searchFunction_(searchFunctionInfo.function)
{
    lookupTimer->start();

    // create label with bold text and a pointing hand cursor
    label = new QLabel(this);
    label->setText(defaultName);
    QFont boldFont;
    boldFont.setBold(true);
    label->setFont(boldFont);
    label->setCursor(Qt::PointingHandCursor);

    connect(this, &EditableLabel::clicked, this, &EditableLabel::startEditing);

    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(placeholder);
    connect(lineEdit, &QLineEdit::editingFinished, this, &EditableLabel::stopEditing);
    connect(lineEdit, &QLineEdit::textEdited, this, &EditableLabel::resetLookup);


    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->addWidget(lineEdit);
    lineEdit->hide();

    setLayout(mainLayout);
}

EditableLabel::~EditableLabel()
{
    delete lookupTimer;
}

QString EditableLabel::getText() const
{
    return label->text();
}

void EditableLabel::setText(QString text)
{
    label->setText(text);
}

void EditableLabel::returnToDefault() {
    label->setText(defaultText_);
    lineEdit->setText("");
}



void EditableLabel::startEditing()
{
    label->hide();
    lineEdit->show();

    lineEdit->setFocus();
    lineEdit->setText("");

}

void EditableLabel::stopEditing()
{
    emit textEditingFinished(label->text(), lineEdit->text());

    lineEdit->hide();

    if (lineEdit->text() != "") {
        label->setText(lineEdit->text());
    }

    label->show();

}

void EditableLabel::resetLookup()
{
    QString text = lineEdit->text();
    if (text.isEmpty()) {
        return;
    }

    if (lookupTimer->elapsed() < LOOKUP_INTERVAL) {
        return;
    } else {
        lookupTimer->restart();
    }

    for (QWidget* w : searchResults_) {
        mainLayout->removeWidget(w);
        delete w;
    }
    searchResults_.clear();


    std::vector<Searchable*> searchables = (dataHandler_->*searchFunction_)(text.toStdString());

    for (Searchable* searchable : searchables) {
        assert(searchable != nullptr);

        ClickableLabel* searchResult = new ClickableLabel(this);
        searchResult->setText(QString::fromStdString(searchable->getName()));
        connect(searchResult, &ClickableLabel::clicked, this, [=](){
            lineEdit->setText(searchResult->text());
            stopEditing();
        });
        mainLayout->addWidget(searchResult);
        searchResults_.push_back(searchResult);

    }

}
