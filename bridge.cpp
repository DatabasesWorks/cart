#include "bridge.h"

void addGood(OrderWidget *worder, Good good, Order order)
{

}

void loadFromOrder(OrderWidget *worder, Business &business, Order order)
{
    for (int i = 0; i< business.m_store.size(); ++i)
//    for (Good good : business.m_store)
    {
        Good good = business.m_store[i];
        std::string name = good.first;
        worder->m_wgoods[i]->ncur = order.count(name);
        worder->m_wgoods[i]->nremian = good.second;
        worder->m_wgoods[i]->name = name;
        worder->m_wgoods[i]->updateUI();
    }
}
