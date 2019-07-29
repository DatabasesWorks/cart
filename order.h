#ifndef ORDER_H
#define ORDER_H

#include <QtWidgets>
#include "goodselectwidget.h"
#include "business.h"

class OrderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrderWidget();

    void loadFromOrder(Order *order);

signals:
    void updateOrder();
public:
    int col = 4;
    const int capacity = 4;
    int cnt = 0;
//    QGridLayout* layout;
    std::vector<GoodSelectWidget*> m_wgoods;

    void closeEvent(QCloseEvent *) override;

    Order *porder;
};

#endif // ORDER_H
