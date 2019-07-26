#include "mainwindow.h"
#include <QApplication>
#include "order.h"
#include "bridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    {
        MainWindow w;
        w.show();
    }



        OrderWidget od;
        Order order{"box"};
        Business &b = Business::instance();
        loadFromOrder(&od, b, order);
        od.show();


    return a.exec();
}
