#include "mainwindow.h"

static int ITERATOR{0};

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_label{new QLabel(QString::number(ITERATOR))}
    , m_button{new QPushButton("Click Me!")}
{
    QVBoxLayout* vlayo{new QVBoxLayout(this)};
    vlayo->setMargin(5);
    vlayo->setSpacing(5);
    vlayo->addWidget(m_label, 0, Qt::AlignmentFlag::AlignCenter);
    vlayo->addWidget(m_button);

    connect(m_button, SIGNAL(clicked(bool)), this, SLOT(onClickSlot())); // Using connect method in Qt4 style

    connect(m_button, &QPushButton::clicked, this, &MainWindow::onClick); // Using connect method in Qt5 style
}

MainWindow::~MainWindow()
{
    qDebug() << __FUNCTION__;
}

void MainWindow::onClick()
{
    MainWindow* window{new MainWindow};
    window->setWindowTitle(QString("Slave - %1").arg(ITERATOR));
    window->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);

    QVBoxLayout* vlayo{qobject_cast<QVBoxLayout*>(window->layout())};
    if(vlayo != nullptr)
    {
        QPushButton* button{new QPushButton("Click Me Again!")};
        vlayo->addWidget(button);

        connect(button, &QPushButton::clicked, [window]() // Using connect method in Qt5 style
                {
                    window->m_label->setText("\"Click Me Again!\" button clicked!");
                });
    }

    window->show();
}

void MainWindow::onClickSlot()
{
    m_label->setNum(++ITERATOR);
}
