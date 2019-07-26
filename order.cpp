#include "order.h"
#include <QtWidgets>

order::order(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    auto *layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<3; ++j)
        {
            QLabel* label = new QLabel(QString::number(i));
            QImage img(":/img/cart2.jpg");
            label->setPixmap(QPixmap::fromImage(img));

            label->resize(200,200);
            layout->addWidget(label, j, i);
            auto labellay = new QGridLayout(label);
            labellay->addWidget(new QPushButton("inside"));
        }


}
