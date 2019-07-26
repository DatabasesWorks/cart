#include "mainwindow.h"
#include <QApplication>
#include "order.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    {
        MainWindow w;
        w.show();
    }



        order od;
        od.show();


    return a.exec();
}
