#include "bridge.h"

void loadFromOrder(OrderWidget *worder, Business &business, Order order)
{
    auto it = business.m_store.begin();
    for (int i = 0;
         i< business.m_store.size();
         ++i, ++it)
//    for (Good good : business.m_store)
    {
        Good good = *(it);
        std::string name = good.first;
        worder->m_wgoods[i]->ncur = order.count(name);
        worder->m_wgoods[i]->nremian = good.second;
        worder->m_wgoods[i]->name = name;
        worder->m_wgoods[i]->updateUI();
    }
}

void backToOrder(OrderWidget *worder, Business &business, Order &order)
{
    order.clear();
    auto it = business.m_store.begin();
    for (int i = 0;
         i< business.m_store.size();
         ++i, ++it)
//    for (Good good : business.m_store)
    {
        std::string name = it->first;
        for (int j=0; j< worder->m_wgoods[i]->ncur; ++j) order.insert(name);
        it->second = worder->m_wgoods[i]->nremian;
    }
}
