#pragma once

#include <QtWidgets>
#include <QtNetwork>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

    void onStart();
    void onStop();

    void logMessage(const QString& message);

    void onNewConnection();

    void onReadyRead();

private:
    QPushButton* startButton;
    QPushButton* stopButton;

    QTextEdit* logEdit;

    QTcpServer* server;
};

