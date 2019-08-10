#include "business.h"
#include <QDir>
#include <QtWidgets>

Business &Business::instance()
{
    static Business b;
    return b;
}

Business::Business()
{
    initStore();
    m_orders.resize(size);
}

void Business::initStore()
{
    QDir dirOfGoods("./icon/goods");

    QStringList list = dirOfGoods.entryList();

    for (QString file : list)
    {
        if (file.endsWith(".png", Qt::CaseInsensitive))
        {
            QString main = file.left(file.size()-4);
            m_store.insert({main, 5});
        }
    }

}

void Business::orderSub(Order *order, QString name)
{
    if (lockOrder) return;
    int id = order - m_orders.data();
    std::cerr<<"order "<<id<<" sub "<<name.toStdString()<<std::endl;
    {
        //will erase all
        //order->erase(name);
        //will erase all
        order->erase(order->find(name));
    }
    m_store[name]++;
    emit orderChanged(order);
}

void Business::orderAdd(Order *order, QString name)
{
    if (lockOrder) return;
    if (order->size()>=4)
    {
        QMessageBox::information(nullptr, "Overflow", "Too many goods!\n"
                                                      "One order can contain at most 4 goods.");
        return;
    }
    order->insert(name);
    m_store[name]--;
    emit orderChanged(order);
}

void Business::arrangeLeftGoods()
{

}
