#include "mainwindow.h"
#include <QtWidgets>
#include "business.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<3; ++j)
        {
            auto btn = new QPushButton(QString::number(i));
            layout->addWidget(btn, j, i);
            m_btnOrders.push_back(btn);
            int index = m_btnOrders.size()-1;
            connect(btn, &QPushButton::clicked, [=]()
            {
                emit updateOrder(index);
            });
        }

}

MainWindow::~MainWindow()
{

}
