#include "goodselectwidget.h"
#include <QtWidgets>

GoodSelectWidget::GoodSelectWidget(QWidget *parent) : QWidget(parent)
{
    auto labellay = new QGridLayout(this);

    QImage img(":/img/cart2.jpg");
    img = img.scaled(200,200);
    QLabel* pic = new QLabel();
    pic->setPixmap(QPixmap::fromImage(img));

    labellay->addWidget(pic, 0, 0, 1, 3);

    auto left = new QPushButton("-");
    labellay->addWidget(left, 1, 0, 1, 1);
    auto right = new QPushButton("+");
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

    auto remain = new QLabel("remian number: 5");
    remain->setAlignment(Qt::AlignCenter);
    labellay->addWidget(remain, 2, 0, 1, 3);

    auto name = new QLabel("good name");
    name->setAlignment(Qt::AlignCenter);
    labellay->addWidget(name, 3, 0, 1, 3);

    resize(200,200);
}
