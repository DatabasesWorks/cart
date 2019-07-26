#include "order.h"
#include <QtWidgets>

order::order(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    auto *layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<3; ++j)
        {
            QLabel* label = new QLabel();

            auto labellay = new QGridLayout(label);

            QImage img(":/img/cart2.jpg");
            img = img.scaled(200,200);
            QLabel* pic = new QLabel();
            pic->setPixmap(QPixmap::fromImage(img));

            labellay->addWidget(pic, 0, 0, 1, 3);

            auto left = new QPushButton("left");
            labellay->addWidget(left, 1, 0, 1, 1);
            auto right = new QPushButton("right");
            labellay->addWidget(right, 1, 2, 1, 1);

            QLabel* number = new QLabel("0");
            number->setAlignment(Qt::AlignCenter);
            connect(left, &QPushButton::clicked, [=]()
            {
                int num = number->text().toInt();
                number->setText(QString::number(--num));
            });
            connect(right, &QPushButton::clicked, [=]()
            {
                int num = number->text().toInt();
                number->setText(QString::number(++num));
            });
            labellay->addWidget(number, 1, 1, 1, 1);

            label->resize(200,200);
            layout->addWidget(label, j, i);
        }


}
