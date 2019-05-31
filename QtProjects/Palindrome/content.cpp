#include "content.h"

Content::Content(QWidget* parent)
    : QWidget(parent)
    , textEdit{new QTextEdit}
    , palindromeList{new QListWidget}
    , logEdit{new QTextEdit}
{
    QGroupBox* textBox{generateGroupBox("Text:", textEdit)};
    QGroupBox* palindromeBox{generateGroupBox("Palindrome List:", palindromeList)};
    QGroupBox* logBox{generateGroupBox("Log:", logEdit)};

    QSplitter* hSplitter{new QSplitter(Qt::Horizontal)};
    hSplitter->addWidget(textBox);
    hSplitter->addWidget(palindromeBox);
    hSplitter->setStretchFactor(0, 3);
    hSplitter->setStretchFactor(1, 1);

    QSplitter* vSplitter{new QSplitter(Qt::Vertical)};
    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(logBox);
    vSplitter->setStretchFactor(0, 3);
    vSplitter->setStretchFactor(1, 1);

    QVBoxLayout* vlayo{new QVBoxLayout(this)};
    vlayo->setMargin(5);
    vlayo->setSpacing(5);
    vlayo->addWidget(vSplitter);
}

QGroupBox* Content::generateGroupBox(const QString& boxName, QWidget* widget) const
{
    QGroupBox* box{new QGroupBox(boxName)};
    QVBoxLayout* boxLayout{new QVBoxLayout(box)};
    boxLayout->setMargin(0);
    boxLayout->setSpacing(0);
    boxLayout->addWidget(widget);

    return box;
}
