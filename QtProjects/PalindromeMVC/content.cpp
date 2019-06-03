#include "content.h"

Content::Content(QWidget* parent)
    : QWidget(parent)
    , m_textEdit{new QTextEdit}
    , m_palindromeView{new QTableView}
    , m_palindromeModel{new PalindromeModel}
    , m_logEdit{new QTextEdit}
{
    m_palindromeView->setModel(m_palindromeModel);

    QGroupBox* textBox{generateGroupBox("Text:", m_textEdit)};
    QGroupBox* palindromeBox{generateGroupBox("Palindrome List:", m_palindromeView)};
    QGroupBox* logBox{generateGroupBox("Log:", m_logEdit)};

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

void Content::processFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream stream(&file);

    m_textEdit->setPlainText(stream.readAll());

    processText();

    logMessage(QString("File \"%1\" loaded and processed.").arg(fileName));
}

void Content::processText()
{
    m_palindromeModel->clear();

    const QString content{m_textEdit->toPlainText()};

    const QVector<QStringRef> words{content.splitRef(QRegularExpression("\\s+"), QString::SplitBehavior::SkipEmptyParts)};

    for(const QStringRef& word: words)
    {
        QString rword(word.size(), ' ');
        std::copy(word.crbegin(), word.crend(), rword.begin());

        if(word.compare(rword, Qt::CaseInsensitive) == 0)
        {
            m_palindromeModel->append(word.toString());
        }
    }
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

void Content::logMessage(const QString &message)
{
    const QString logMessage{QString("%1 - %2").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")).arg(message)};

    m_logEdit->append(logMessage);

    emit statusMessage(message);
}
