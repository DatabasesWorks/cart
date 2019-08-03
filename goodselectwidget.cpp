#include "goodselectwidget.h"
#include "order.h"
#include <QtWidgets>


GoodSelectWidget::GoodSelectWidget(QString Picname, Order *&order, QWidget *parent) : QWidget(parent),
    porder(order)
{
    porder = order;

    connect(&Business::instance(), &Business::orderChanged, [this](Order* pcorder)
    {
        if (pcorder == porder)
        {
            number->setText(QString::number(porder->count(name)));
            if (Business::instance().m_store.count(name)) remain->setText(pref + QString::number(Business::instance().m_store.at(name)));
        }
    });
    auto labellay = new QGridLayout(this);

    int id = porder - Business::instance().m_orders.data();
    QImage img(Picname);
    img = img.scaled(200,200);
    pic = new QLabel();
    pic->setPixmap(QPixmap::fromImage(img));

    labellay->addWidget(pic, 0, 0, 1, 3);

    auto left = new QPushButton("");
    labellay->addWidget(left, 1, 0, 1, 1);
    auto right = new QPushButton("");
//    right->setStyleSheet("QPushButton {\
//                         color: #333;\
//                         border: 2px solid #555;\
//                         border-radius: 20px;\
//                         border-style: outset;\
//                         background: qradialgradient(\
//                             cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,\
//                             radius: 1.35, stop: 0 #fff, stop: 1 #888\
//                             );\
//                         padding: 5px;\
//                         }"
//                         );
    labellay->addWidget(right, 1, 2, 1, 1);

    number = new QLabel();
    number->setAlignment(Qt::AlignCenter);

    labellay->addWidget(number, 1, 1, 1, 1);

    remain = new QLabel();
    remain->setAlignment(Qt::AlignCenter);
    labellay->addWidget(remain, 2, 0, 1, 3);

    wname = new QLabel("good name");
    wname->setAlignment(Qt::AlignCenter);
    labellay->addWidget(wname, 3, 0, 1, 3);

    auto setRound = [](QPushButton *btn)
    {
        QRect rect(2,2,34,34);
            QRegion region(rect, QRegion::Ellipse);
            btn->setFixedSize(38,38);
            btn->setMask(region);
    };

    setRound(left);
    setRound(right);

    auto seticon = [](QPushButton *btn, QString icon)
    {
        QPixmap pixmap(icon);
        QIcon ButtonIcon(pixmap.scaled(36, 36));
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(30, 30));
    };

    seticon(left, "./icon/sub.png");
    seticon(right, "./icon/add.png");


    connect(left, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        if (porder->count(name))
        {
            Business::instance().orderSub(porder, name);
//            number->setText(QString::number(--ncur));
//            remain->setText(pref + QString::number(++nremian));
//            porder->erase(porder->find(name));
//            Business::instance().orderChanged(porder);
        }
    });
    connect(right, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        if (Business::instance().m_store.at(name)>0)
        {
            Business::instance().orderAdd(porder, name);
//            number->setText(QString::number(++ncur));
//            remain->setText(pref + QString::number(--nremian));
        }
    });

    resize(200,200);
}

void GoodSelectWidget::updateUI()
{
    number->setText(QString::number(porder->count(name)));
    if (Business::instance().m_store.count(name))
        remain->setText(pref + QString::number(Business::instance().m_store.at(name)));
    wname->setText((name));


    if (OrderWidget::m_pixmaps.count(name)) pic->setPixmap(OrderWidget::m_pixmaps[name]);
}

void GoodSelectWidget::showGood(QString goodname)
{
    name = goodname;
//    updateUI();
}

void GoodSelectWidget::mouseReleaseEvent(QMouseEvent *)
{

}

void GoodSelectWidget::setOrder(Order *order)
{
    porder = order;
//    updateUI();
}
