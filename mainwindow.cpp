#include "mainwindow.h"
#include <QtWidgets>
#include "business.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    auto layoutall = new QGridLayout(this);
    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,0,0);
    layoutall->addWidget(right,0,2);
    layoutall->addWidget(central,0,1);

    connect(left, &QPushButton::clicked, [=]()
    {
        int id = central->currentIndex();
        if (id >0)
            central->setCurrentIndex(id-1);
    });

    connect(right, &QPushButton::clicked, [=]()
    {
        int id = central->currentIndex();
        if (id < central->count()-1)
            central->setCurrentIndex(id+1);
    });

    for (int stackid = 0; stackid < 3; ++stackid)
    {
        auto widget = new QWidget;
        central->addWidget(widget);
        auto *layout = new QGridLayout(widget);
        for (int i=0; i< 3; ++i)
            for (int j =0; j<3; ++j)
            {
                auto btn = new QPushButton(QString::number(stackid*9 + i*3 +j));
                layout->addWidget(btn, i, j);

                int index = m_btnOrders.size();
                if (index >= Business::instance().size)
                {
                    QSizePolicy sp_retain = btn->sizePolicy();
                    sp_retain.setRetainSizeWhenHidden(true);
                    btn->setSizePolicy(sp_retain);
                    btn->hide();
                }
                else
                {
                    m_btnOrders.push_back(btn);

                    connect(btn, &QPushButton::clicked, [=]()
                    {
                        emit updateOrder(index);
                    });
                }
            }
    }

}

MainWindow::~MainWindow()
{

}
