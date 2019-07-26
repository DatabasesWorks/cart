#include "order.h"
#include <QtWidgets>



OrderWidget::OrderWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    layout = new QGridLayout(this);
    for (int i=0; i< 4; ++i)
        for (int j =0; j<2; ++j)
        {
            auto label = new GoodSelectWidget;
            layout->addWidget(label, j, i);
            m_wgoods.push_back(label);
        }


}
