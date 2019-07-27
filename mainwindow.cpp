#include "mainwindow.h"
#include <QtWidgets>
#include "business.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 600);
    auto layoutall = new QGridLayout(this);
    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,0,0);
    layoutall->addWidget(right,0,2);
    layoutall->addWidget(central,0,1);

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

    for (int stackid = 0; stackid < 3; ++stackid)
    {
        auto widget = new QWidget;
        central->addWidget(widget);
        auto *layout = new QGridLayout(widget);
        for (int i=0; i< 3; ++i)
            for (int j =0; j<3; ++j)
            {
                auto btn = new QPushButton(QString::number(stackid*9 + i*3 +j));
                QSizePolicy sp_retain = btn->sizePolicy();
//                sp_retain.setHorizontalStretch();
                btn->setMinimumSize(300,200);
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
                        emit updateOrder(index);
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
    QPixmap all(300, 200);
    all.fill();
    QPixmap sub(150, 100);
    sub.fill();
    std::vector<QPixmap> goods(4, sub);

//    for (int i=0; i< order.size(); ++i)
    int cnt = -1;
    for (std::string good : order)
    {
        cnt++;
        int id = std::distance(Business::instance().m_store.begin(),
                               Business::instance().m_store.find(good));

        auto goodpicname = "./icon/goods/" +
                QString::fromStdString(good)+".png";

        goods[cnt] = QPixmap::fromImage(QImage(goodpicname).scaled(150,100));
    }

    QPainter painter(&all);
    for (int i=0; i<4; ++i)
    {
        QRectF target = QRectF((i%2)*150, i/2*100, 150, 100);
        painter.drawPixmap(target, goods[i], QRectF(0,0,150,100));
    }



    m_btnOrders[index]->setIcon(QIcon(all));
    m_btnOrders[index]->setIconSize(QSize(300, 200));
}
