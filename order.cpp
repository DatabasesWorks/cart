#include "order.h"
#include <QtWidgets>

#include "business.h"

OrderWidget::OrderWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);
    auto layoutall = new QGridLayout(this);

    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,0,0);
    layoutall->addWidget(right,0,2);
    layoutall->addWidget(central,0,1);

    connect(left, &QPushButton::clicked, [=]()
    {
        int id = central->currentIndex();
        if (id >0)
            central->setCurrentIndex(id-1);
    });

    connect(right, &QPushButton::clicked, [=]()
    {
        int id = central->currentIndex();
        if (id < central->count()-1)
            central->setCurrentIndex(id+1);
    });

    auto it = Business::instance().m_store.begin();
    for (int stackid = 0; stackid < 2; ++stackid)
    {
        auto widget = new QWidget;
        central->addWidget(widget);
        auto *layout = new QGridLayout(widget);

        for (int i=0; i< 2; ++i)
            for (int j =0; j<4; ++j)
            {
                int index = m_wgoods.size()+1;

                QString goodpicname;

                if (it != Business::instance().m_store.end())
                {
                    goodpicname = "./icon/goods/" +
                            QString::fromStdString(it->first)+".png";
                    it++;
                }
                auto label = new GoodSelectWidget(goodpicname);


                layout->addWidget(label, i, j);
                m_wgoods.push_back(label);

                if (index > Business::instance().m_store.size())
                {
                    QSizePolicy sp_retain = label->sizePolicy();
                    sp_retain.setRetainSizeWhenHidden(true);
                    label->setSizePolicy(sp_retain);
                    label->hide();
                }

            }
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
