#include "goodrowwidget.h"

GoodRowWidget::GoodRowWidget(QWidget *parent) : QWidget(parent)
{

}

void GoodRowWidget::setGood(std::string good, Order order)
{
    QString goodQstr = QString::fromStdString(good);
    auto lay = new QHBoxLayout(this);

    m_goodImg = new QLabel;
    m_goodImg->setPixmap(QPixmap::fromImage(QImage("./icon/goods/"+goodQstr+".png").scaled(100,100)));

    m_goodName = new QLabel(goodQstr);

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
