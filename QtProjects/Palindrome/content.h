#pragma once

#include <QtWidgets>

class Content : public QWidget
{
    Q_OBJECT

public:
    explicit Content(QWidget* parent = nullptr);

private:
    QGroupBox* generateGroupBox(const QString& boxName, QWidget* widget) const;

private:
    QTextEdit* textEdit;

    QListWidget* palindromeList;

    QTextEdit* logEdit;
};

