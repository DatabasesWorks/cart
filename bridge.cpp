#include "bridge.h"

void addGood(OrderWidget *worder, Good good, Order order)
{

}

void loadFromOrder(OrderWidget *worder, Business &business, Order order)
{
    for (Good good : business.m_store)
    {
        addGood(worder, good, order);
    }
}
