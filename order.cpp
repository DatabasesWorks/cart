#include "order.h"
#include <QtWidgets>

#include "business.h"

OrderWidget::OrderWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    layout = new QGridLayout(this);
    for (int i=0; i< 2; ++i)
        for (int j =0; j<4; ++j)
        {
            auto label = new GoodSelectWidget;
            layout->addWidget(label, i, j);
            m_wgoods.push_back(label);
        }


}

void OrderWidget::closeEvent(QCloseEvent *e)
{
    int orderSize = 0;
    for (auto wgood : m_wgoods) orderSize += wgood->ncur;
    if (orderSize <= capacity)
    {
        emit updateOrder();
    }
    else
    {
        QMessageBox::information(this, "overflow", "too many goods");
        e->ignore();
    }
}
