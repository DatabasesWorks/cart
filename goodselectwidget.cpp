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

    number = new QLabel(QString::number(ncur));
    number->setAlignment(Qt::AlignCenter);

    labellay->addWidget(number, 1, 1, 1, 1);

    remain = new QLabel(pref + QString::number(nremian));
    remain->setAlignment(Qt::AlignCenter);
    labellay->addWidget(remain, 2, 0, 1, 3);

    wname = new QLabel("good name");
    wname->setAlignment(Qt::AlignCenter);
    labellay->addWidget(wname, 3, 0, 1, 3);

    connect(left, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        number->setText(QString::number(--ncur));
        remain->setText(pref + QString::number(++nremian));
    });
    connect(right, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        number->setText(QString::number(++ncur));
        remain->setText(pref + QString::number(--nremian));
    });

    resize(200,200);
}

void GoodSelectWidget::updateUI()
{
    number->setText(QString::number(ncur));
    remain->setText(pref + QString::number(nremian));
    wname->setText(QString::fromStdString(name));
}
