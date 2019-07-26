#ifndef ORDER_H
#define ORDER_H

#include <QtWidgets>
#include "goodselectwidget.h"

class OrderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrderWidget(QWidget *parent = nullptr);

signals:
    void updateOrder();
public:
    int col = 4;
    QGridLayout* layout;
    std::vector<GoodSelectWidget*> m_wgoods;

    void closeEvent(QCloseEvent *) override;
};

#endif // ORDER_H
