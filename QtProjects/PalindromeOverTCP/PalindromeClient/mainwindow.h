#pragma once

#include <QtWidgets>
#include <QtNetwork>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

    void onSend();

private:
    QLineEdit* palindromeLine;

    QPushButton* sendButton;

    QTcpSocket* client;
};

