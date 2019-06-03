#pragma once

#include "content.h"

#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

    void onOpenFile();

    void onProcess();

private:
    void createMenus();

private:
    QMenuBar* m_menuBar;

    Content* m_content;

    QStatusBar* m_statusBar;
};
