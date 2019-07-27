#include "mainwindow.h"
#include <QApplication>
#include "order.h"
#include "bridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



        MainWindow w;
        w.show();




        OrderWidget od;
//        od.show();
        Business &b = Business::instance();

        int curorder;

        QObject::connect(&w, &MainWindow::updateOrder, [&](int i)
        {
            curorder = i;
            loadFromOrder(&od, b, b.m_orders[i]);
            od.show();
        });

        QObject::connect(&od, &OrderWidget::updateOrder, [&]()
        {
            backToOrder(&od, b, b.m_orders[curorder]);
            std::string order;
            for (auto good : b.m_orders[curorder]) order += (good + " ");
            w.m_btnOrders[curorder]->setText(QString::fromStdString(order));
        });




    return a.exec();
}
