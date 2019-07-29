#include "business.h"
#include <QDir>

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

void Business::tryOrder(Order order)
{
    auto backup = m_store;
    for (QString good : order)
    {
        if (m_store.find(good)!=m_store.end() &&
                m_store[good] > 0)
        {
            m_store[good]--;
        }
        else
        {
            m_store = backup;
        }
    }
    m_orders.push_back(order);
}
