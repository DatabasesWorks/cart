#include "mainwindow.h"
#include <QtWidgets>
#include "business.h"
#include "OrderServer.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 600);
    auto layoutall = new QGridLayout(this);

    auto top = new QHBoxLayout;

    QLabel *logo = new QLabel();
//    logo->setFixedSize(144, 100);
    logo->setPixmap(QPixmap::fromImage(QImage("../icon/logo.png")).scaled(36, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setStyleSheet("QLabel { background-color : blue; }");

    QLabel *title = new QLabel("订单中心");
    title->setStyleSheet("QLabel { background-color : blue; }");
    top->setSpacing(0);

    top->addWidget(logo);
    top->addWidget(title);
    layoutall->addLayout(top,0,0,1,3);

    int row = 0;


    row++;

    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,row,0);
    layoutall->addWidget(right,row,2);
    layoutall->addWidget(central,row,1);

    row++;
    auto start = new QPushButton("开始捡选");
//    layoutall->addWidget(new QWidget, row, 0, 1, 2);
    layoutall->addWidget(start, row, 2);
    connect(start, &QPushButton::clicked, [=]()
    {
        start->setEnabled(false);
        startPick();
    });
//    connect(start, &QPushButton::clicked, this, &MainWindow::startPick);


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

    int height = 4;
    int width = 4;

    int cnt = height*width;
    for (int stackid = 0; stackid < (Business::instance().size-1)/cnt +1; ++stackid)
    {
        auto widget = new QWidget;
        central->addWidget(widget);
        auto *layout = new QGridLayout(widget);
        for (int i=0; i< height; ++i)
            for (int j =0; j<width; ++j)
            {
                auto btn = new QPushButton(QString::number(stackid*cnt + i*width +j));
                QSizePolicy sp_retain = btn->sizePolicy();
//                sp_retain.setHorizontalStretch();
                btn->setMinimumSize(200,150);
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
                        if (!Business::instance().lockOrder) emit updateOrder(index);
                    });
                }
            }
    }

}

MainWindow::~MainWindow()
{

}

void MainWindow::setOrderIcon(int index, Order order)
{
    int width = m_btnOrders[index]->width();
    int height = m_btnOrders[index]->height();
    auto &b = Business::instance();
    QPixmap all(width, height);
    all.fill();
    QPixmap sub(width/2, height/2);
    sub.fill();
    std::vector<QPixmap> goods(4, sub);

    int cnt = -1;
    Order picked;
    if (Business::instance().lockOrder) picked = Business::instance().m_havePicked[index];
    for (QString good : order)
    {
        cnt++;
        bool color = false;
        if (picked.count(good))
        {
            color = true;
            picked.erase(picked.find(good));
        }

        if (Business::instance().lockOrder && !color)
        {
            auto im = b.m_images[good].scaled(width/2, height/2).convertToFormat(QImage::Format_ARGB32);

            for (int y = 0; y < im.height(); ++y) {
                QRgb *scanLine = (QRgb*)im.scanLine(y);
                for (int x = 0; x < im.width(); ++x) {
                    QRgb pixel = *scanLine;
                    uint ci = uint(qGray(pixel));
                    *scanLine = qRgba(ci, ci, ci, qAlpha(pixel));
                    ++scanLine;
                }
            }
//            return QPixmap::fromImage(im);

            goods[cnt] =  QPixmap::fromImage(im);
        }
        else
        {
            goods[cnt] = QPixmap::fromImage(b.m_images[good].scaled(width/2, height/2));
        }
    }

    QPainter painter(&all);
    for (int i=0; i<4; ++i)
    {
        QRectF target = QRectF((i%2)*width/2, i/2*height/2, width/2, height/2);
        painter.drawPixmap(target, goods[i], QRectF(0,0,width/2, height/2));
    }



    m_btnOrders[index]->setText("");
    m_btnOrders[index]->setIcon(QIcon(all));
    m_btnOrders[index]->setIconSize(QSize(width, height));
}

void MainWindow::startPick()
{
    Business::instance().arrangeLeftGoods();
    Business::instance().lockOrder = true;
    Business::instance().m_havePicked.clear();
    Business::instance().m_havePicked.resize(Business::instance().m_orders.size());

    for (int i=0; i<Business::instance().m_orders.size(); ++i)
    {
        setOrderIcon(i, Business::instance().m_orders[i]);
    }
    auto server = new OrderServer;
    server->start();
}
