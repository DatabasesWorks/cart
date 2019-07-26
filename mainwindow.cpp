#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<3; ++j)
        {
            layout->addWidget(new QPushButton(QString::number(i)), j, i);
        }
}

MainWindow::~MainWindow()
{

}
