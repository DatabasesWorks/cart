#include "business.h"

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

    m_store = {
        {"box", 5},
        {"noodle", 5},
        {"ball", 5},
    };
}

void Business::tryOrder(Order order)
{
    auto backup = m_store;
    for (std::string good : order)
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
