#pragma once

#include <QtWidgets>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void onClick();

private:
    QLabel* m_label;

    QPushButton* m_button;

public slots:
    void onClickSlot();
};

