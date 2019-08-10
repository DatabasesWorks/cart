#include "business.h"
#include <QDir>
#include <QtWidgets>

std::map<QString, QImage> Business::m_images;


Business &Business::instance()
{
    static Business b;
    return b;
}

Business::Business()
{
    initStore();
    m_orders.resize(size);

    for (auto name : m_store)
    {
        QImage img("./icon/goods/" + name.first+".png");
        img = img.scaled(200,200);
        m_images[name.first]   = img;//(QPixmap::fromImage(img));
    }
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
    std::vector<int> emptyorder;

    for (int i=0; i< m_orders.size(); ++i)
    {
        /*if (m_orders[i].empty())*/ emptyorder.push_back(i);
    }

    for (auto it = m_store.begin(); it != m_store.end(); ++it)
    {
        if (emptyorder.empty()) break;
        while (it->second)
        {
            it->second--;

            if (m_orders[emptyorder.back()].size() < 4)
            {
                m_orders[emptyorder.back()].insert(it->first);
            }
            else {
                emptyorder.erase(std::prev(emptyorder.end() ));
                if (emptyorder.empty()) break;
                m_orders[emptyorder.back()].insert(it->first);
            }
        }
    }

}
