#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_menuBar{new QMenuBar}
    , m_content{new Content}
    , m_statusBar{new QStatusBar}
{
    createMenus();

    QVBoxLayout* vlayo{new QVBoxLayout(this)};
    vlayo->setMargin(0);
    vlayo->setSpacing(5);
    vlayo->addWidget(m_menuBar);
    vlayo->addWidget(m_content);
    vlayo->addWidget(m_statusBar);
}

void MainWindow::createMenus()
{
    QMenu* menuFile{new QMenu("&File", m_menuBar)};
    menuFile->addSeparator();
    menuFile->addAction("E&xit", qApp, &QApplication::quit, Qt::CTRL+Qt::Key_Q);

    m_menuBar->addMenu(menuFile);

    m_menuBar->addAction("About Qt", qApp, &QApplication::aboutQt);
}
