#pragma once

#include <QtWidgets>

#include "palindromemodel.h"

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget* parent = nullptr);

    void processFile(const QString& fileName);
    void processText();

private:
    QGroupBox* generateGroupBox(const QString& boxName, QWidget* widget) const;

    void logMessage(const QString& message);

private:
    QTextEdit* m_textEdit;

    QTableView* m_palindromeView;
    PalindromeModel* m_palindromeModel;

    QTextEdit* m_logEdit;

signals:
    void statusMessage(const QString&, int timeout = 10000);
};
