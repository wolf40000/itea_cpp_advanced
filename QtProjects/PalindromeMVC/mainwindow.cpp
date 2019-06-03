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

    connect(m_content, &Content::statusMessage, m_statusBar, &QStatusBar::showMessage);
}

void MainWindow::onOpenFile()
{
    const QString fileName{QFileDialog::getOpenFileName(this, "Open file with palindromes", QString(),
                                                        "Text files (*.txt);;All files (*.*)")};

    if(!fileName.isEmpty())
    {
        m_content->processFile(fileName);
    }
}

void MainWindow::onProcess()
{
    m_content->processText();
}

void MainWindow::createMenus()
{
    QMenu* menuFile{new QMenu("&File", m_menuBar)};
    menuFile->addAction("&Open file", this, &MainWindow::onOpenFile, Qt::CTRL+Qt::Key_O);
    menuFile->addSeparator();
    menuFile->addAction("E&xit", qApp, &QApplication::quit, Qt::CTRL+Qt::Key_Q);

    m_menuBar->addMenu(menuFile);

    QMenu* menuEdit{new QMenu("&Edit", m_menuBar)};
    menuEdit->addAction("&Process", this, &MainWindow::onProcess, Qt::CTRL+Qt::Key_R);

    m_menuBar->addMenu(menuEdit);

    m_menuBar->addAction("About Qt", qApp, &QApplication::aboutQt);
}
