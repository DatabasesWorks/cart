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

public:
    int row, col;
    QGridLayout* layout;
    std::vector<GoodSelectWidget*> m_wgoods;
};

#endif // ORDER_H
