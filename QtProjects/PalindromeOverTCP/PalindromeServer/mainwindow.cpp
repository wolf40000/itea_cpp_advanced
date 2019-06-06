#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , startButton{new QPushButton("Start")}
    , stopButton{new QPushButton("Stop")}
    , logEdit{new QTextEdit}
    , server{new QTcpServer(this)}
{
    logEdit->setReadOnly(true);
    logEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);

    QGridLayout* grid{new QGridLayout(this)};
    grid->setMargin(5);
    grid->setSpacing(5);
    grid->addWidget(startButton, 0, 0);
    grid->addWidget(stopButton, 0, 1);
    grid->addWidget(logEdit, 1, 0, 1, 2);

    connect(startButton, &QPushButton::clicked,
            this, &MainWindow::onStart);

    connect(stopButton, &QPushButton::clicked,
            this, &MainWindow::onStop);

    connect(server, &QTcpServer::newConnection,
            this, &MainWindow::onNewConnection);
}

void MainWindow::onStart()
{
    if(server->isListening())
    {
        logMessage("Server is already run");
        return;
    }

    if(server->listen(QHostAddress::AnyIPv4, 3227))
    {
        logMessage("Server is started");
    }
    else
    {
        logMessage(server->errorString());
    }
}

void MainWindow::onStop()
{
    server->close();

    logMessage("Server is stopped.");
}

void MainWindow::logMessage(const QString& message)
{
    const QString log{QString("%1 - %2")
                          .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm::ss"))
                          .arg(message)};

    logEdit->append(log);
}

void MainWindow::onNewConnection()
{
    QTcpSocket* socket{server->nextPendingConnection()};

    connect(socket, &QTcpSocket::disconnected,
            socket, &QTcpSocket::deleteLater);

    connect(socket, &QTcpSocket::readyRead,
            this, &MainWindow::onReadyRead);
}

void MainWindow::onReadyRead()
{
    auto socket{qobject_cast<QTcpSocket*>(sender())};

    if(socket == nullptr)
    {
        return;
    }

    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_5_12);

    stream.startTransaction();

    QString word;
    stream >> word;

    if(!stream.commitTransaction())
    {
        return;
    }

    std::string cword{word.toStdString()};
    std::string rcword{cword.crbegin(), cword.crend()};
    QString rword{QString::fromStdString(rcword)};

    QString message("\"%1\" %2 palindrome");
    message = message.arg(word);

    if(word.compare(rword, Qt::CaseInsensitive))
    {
        logMessage(message.arg("is"));
    }
    else
    {
        logMessage(message.arg("is not"));
    }
}
