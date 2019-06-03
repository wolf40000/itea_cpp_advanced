#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << QStyleFactory::keys();

    a.setStyle(QStyleFactory::create("plastique"));

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
