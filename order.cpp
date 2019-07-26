#include "order.h"
#include <QtWidgets>

#include "goodselectwidget.h"

OrderWidget::OrderWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    auto *layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<2; ++j)
        {
            auto label = new GoodSelectWidget;
            layout->addWidget(label, j, i);
        }


}
