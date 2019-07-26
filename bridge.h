#ifndef BRIDGE_H
#define BRIDGE_H

#include "business.h"
#include "order.h"

void loadFromOrder(OrderWidget* worder, Business &business, Order order);
void backToOrder(OrderWidget* worder, Business &business, Order &order);

#endif // BRIDGE_H
