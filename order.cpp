#include "order.h"
#include <QtWidgets>

#include "business.h"
#include "goodrowwidget.h"

OrderWidget::OrderWidget()
{
    resize(800, 600);
    auto layoutall = new QGridLayout(this);

    QLineEdit *search = new QLineEdit("search:");
    layoutall->addWidget(search, 0, 0, 1, 2);

    QPushButton *cart = new QPushButton();
    layoutall->addWidget(cart, 0, 2, 1, 2);
    connect(cart, &QPushButton::clicked, [=]()
    {
        QMenu modelMenu;
        for (int i=0; i<2; ++i)
        {
            auto *txtBoxAction = new QWidgetAction(&modelMenu);
            auto goodline = new GoodRowWidget();
            Order order = {"双汇", "OLAY"};
            goodline->setGood("双汇", order);
            txtBoxAction->setDefaultWidget(goodline);

            modelMenu.addAction(txtBoxAction);
        }

        modelMenu.exec(cart->mapToGlobal(QPoint(0,cart->height())));

    });

    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,1,0);
    layoutall->addWidget(right,1,2);
    layoutall->addWidget(central,1,1);

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
                            (it->first)+".png";
                    it++;
                }
                auto label = new GoodSelectWidget(goodpicname);


                layout->addWidget(label, i, j);
                m_wgoods.push_back(label);

                QSizePolicy sp_retain = label->sizePolicy();
                sp_retain.setRetainSizeWhenHidden(true);
                label->setSizePolicy(sp_retain);

                if (index > Business::instance().m_store.size())
                {

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

void OrderWidget::loadFromOrder(Order *order)
{
    porder = order;
    auto &business = Business::instance();
    auto it = business.m_store.begin();
    for (int i = 0;
         i< business.m_store.size();
         ++i, ++it)
//    for (Good good : business.m_store)
    {
        Good good = *(it);
        QString name = good.first;
        m_wgoods[i]->ncur = order->count(name);
        m_wgoods[i]->nremian = good.second;
        m_wgoods[i]->name = name;
        m_wgoods[i]->updateUI();
    }
}

void OrderWidget::backToOrder()
{
    auto &business = Business::instance();
    porder->clear();
    auto it = business.m_store.begin();
    for (int i = 0;
         i< business.m_store.size();
         ++i, ++it)
//    for (Good good : business.m_store)
    {
        QString name = it->first;
        for (int j=0; j< m_wgoods[i]->ncur; ++j) porder->insert(name);
        it->second = m_wgoods[i]->nremian;
    }
}
