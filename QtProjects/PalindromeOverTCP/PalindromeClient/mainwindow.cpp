#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , palindromeLine{new QLineEdit}
    , sendButton{new QPushButton("Send")}
    , client{new QTcpSocket(this)}
{
    QGridLayout* grid{new QGridLayout(this)};
    grid->setMargin(5);
    grid->setSpacing(5);
    grid->setRowStretch(0, 2);
    grid->addWidget(palindromeLine, 1, 0);
    grid->addWidget(sendButton, 1, 1);

    connect(sendButton, &QPushButton::clicked,
            this, &MainWindow::onSend);
}

void MainWindow::onSend()
{
    if(!client->isOpen())
    {
        client->connectToHost("localhost", 3227);
        if(!client->waitForConnected())
        {
            return;
        }
    }

    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_12);

    stream << palindromeLine->text();

    client->write(array);
}
