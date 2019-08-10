#include "mainwindow.h"
#include <QApplication>
#include "order.h"
//#include "bridge.h"

#include "norwegianwoodstyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QApplication::setStyle(new NorwegianWoodStyle);



        MainWindow w;
        w.show();




        OrderWidget od;
//        od.show();
        Business &b = Business::instance();


        QObject::connect(&w, &MainWindow::updateOrder, [&](int i)
        {
            od.loadFromOrder(&(b.m_orders[i]));
//            loadFromOrder(&od, b, b.m_orders[i]);
            od.show();
            od.setFixedSize(od.size());
        });

        QObject::connect(&b, &Business::orderChanged, [&](Order *order)
        {
            int id = order - b.m_orders.data();
//            backToOrder(&od, b, b.m_orders[curorder]);
            w.setOrderIcon(id, *order);
//            w.m_btnOrders[curorder]->setText(QString::fromStdString(order));
        });




    return a.exec();
}
