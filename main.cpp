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
        Business &b = Business::instance();

        QObject::connect(&w, &MainWindow::updateOrder, [&](int i)
        {
            loadFromOrder(&od, b, b.m_orders[i]);
            od.show();
        });




    return a.exec();
}
