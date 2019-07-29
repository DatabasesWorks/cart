#include "goodrowwidget.h"

GoodRowWidget::GoodRowWidget(Order *&order) :
porder(order)
{
    connect(&Business::instance(), &Business::orderChanged,
            this /*use this to disconnect the connection*/,
            [this](Order* pcorder)
    {
        if (pcorder == porder)
        {
            m_cnt->setText(QString::number(porder->count(m_name)));
        }
    });
}

void GoodRowWidget::setGood(QString good, Order order)
{
    m_name = good;
    QString goodQstr = (good);
    auto lay = new QHBoxLayout(this);

    m_goodImg = new QLabel;
    m_goodImg->setPixmap(QPixmap::fromImage(QImage("./icon/goods/"+goodQstr+".png").scaled(100,100)));
    m_goodImg->setFixedSize(100,100);

    m_goodName = new QLabel(goodQstr);
    m_goodName->setFixedSize(100,100);

    auto setRound = [](QPushButton *btn)
    {
        QRect rect(2,2,34,34);
        QRegion region(rect, QRegion::Ellipse);
        btn->setFixedSize(38,38);
        btn->setMask(region);
    };



    m_add = new QPushButton;
    m_sub = new QPushButton;

    auto seticon = [](QPushButton *btn, QString icon)
    {
        QPixmap pixmap(icon);
        QIcon ButtonIcon(pixmap.scaled(36, 36));
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(30, 30));
    };

    seticon(m_sub, "./icon/sub.png");
    seticon(m_add, "./icon/add.png");

    setRound(m_sub);
    setRound(m_add);

    connect(m_sub, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        if (porder->count(m_name))
        {
            Business::instance().orderSub(porder, m_name);
//            number->setText(QString::number(--ncur));
//            remain->setText(pref + QString::number(++nremian));
//            porder->erase(porder->find(name));
//            Business::instance().orderChanged(porder);
        }
    });
    connect(m_add, &QPushButton::clicked, [=]()
    {
//        int num = number->text().toInt();
        if (Business::instance().m_store.at(m_name)>0)
        {
            Business::instance().orderAdd(porder, m_name);
//            number->setText(QString::number(++ncur));
//            remain->setText(pref + QString::number(--nremian));
        }
    });

    m_cnt = new QLabel(QString::number(order.count(good)));

    lay->addWidget(m_goodImg);
    lay->addWidget(m_goodName);
    lay->addWidget(m_sub);
    lay->addWidget(m_cnt);

    lay->addWidget(m_add);
}

void GoodRowWidget::mouseReleaseEvent(QMouseEvent *)
{

}
