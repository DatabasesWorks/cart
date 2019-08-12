#include "order.h"
#include <QtWidgets>
#include <QtGlobal>

#include "business.h"
#include "goodrowwidget.h"



OrderWidget::OrderWidget()
{

    resize(800, 600);
    auto layoutall = new QGridLayout(this);

    auto top = new QHBoxLayout;

    QLabel *logo = new QLabel();
    logo->setPixmap(QPixmap::fromImage(QImage("./icon/logo.png")).scaled(36*3, 25*3, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setStyleSheet("QLabel { background-color : blue; }");

    QLabel *title = new QLabel("订单中心");
    title->setStyleSheet("QLabel { background-color : blue; }");
    top->setSpacing(0);

    top->addWidget(logo);
    top->addWidget(title);
    layoutall->addLayout(top,0,0,1,3);

    int row = 0;


    row++;
    orders = new QComboBox;
    layoutall->addWidget(orders, row, 0);

    for (int i = 0; i< Business::instance().m_orders.size(); ++i)
    {
        orders->addItem("订单"+ QString::number(i+1));
    }



    QLineEdit *search = new QLineEdit("");
    layoutall->addWidget(search, row, 1);

    connect(orders, (void (QComboBox::*)(int))(&QComboBox::currentIndexChanged), [=](int id)
    {
        std::cerr<<"id = "<<id<<std::endl;
        loadFromOrder(Business::instance().m_orders.data() + id);
        emit search->textChanged(search->text());
    });

    connect(search, &QLineEdit::textChanged, [this](QString goodname)
    {
        if (Business::instance().m_store.count(goodname))
        {
            m_wgoods[0]->showGood(goodname);
            m_wgoods[0]->updateUI();

            for (int i =1; i< m_wgoods.size(); ++i) m_wgoods[i]->hide();
        }
        else
        {
            if (!goodname.isEmpty()) return;
            int id = 0;
            for (auto it =Business::instance().m_store.begin();
                 it != Business::instance().m_store.end(); ++it, ++id)
            {
                m_wgoods[id]->showGood(it->first);
                m_wgoods[id]->updateUI();
                m_wgoods[id]->show();
            }
        }
    });

    QPushButton *cart = new QPushButton();
    layoutall->addWidget(cart, row, 2);
    connect(cart, &QPushButton::clicked, [=]()
    {
        QMenu modelMenu;
        std::set<QString> goods;
        for (auto good : *porder)
        {
            if (goods.count(good) > 0) continue;
            goods.insert(good);

            auto *txtBoxAction = new QWidgetAction(&modelMenu);
            auto goodline = new GoodRowWidget(porder);
            goodline->setGood(good, *porder);
            txtBoxAction->setDefaultWidget(goodline);

            modelMenu.addAction(txtBoxAction);

        }
//        for (int i=0; i<2; ++i)
//        {
//            auto *txtBoxAction = new QWidgetAction(&modelMenu);
//            auto goodline = new GoodRowWidget();
//            Order order = {"双汇", "OLAY"};
//            goodline->setGood("双汇", order);
//            txtBoxAction->setDefaultWidget(goodline);

//            modelMenu.addAction(txtBoxAction);
//        }

        modelMenu.exec(cart->mapToGlobal(QPoint(0,cart->height())));

    });

    row++;
    auto left = new QPushButton("<");
    auto right = new QPushButton(">");
    auto central = new QStackedWidget;
    layoutall->addWidget(left,row,0);
    layoutall->addWidget(right,row,2);
    layoutall->addWidget(central,row,1);

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

                QString goodname;

                if (it != Business::instance().m_store.end())
                {
                    goodname =
                            (it->first);
                    it++;
                }
                auto label = new GoodSelectWidget(goodname, porder);


                layout->addWidget(label, i, j);
                label->setOrder(porder);
                m_wgoods.push_back(label);
                label->setOrder(porder);

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
//    for (auto wgood : m_wgoods) orderSize += wgood->ncur;
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
    auto &business = Business::instance();

    orders->setCurrentIndex(order - business.m_orders.data());
    porder = order;

    auto it = business.m_store.begin();
    for (int i = 0;
         i< business.m_store.size();
         ++i, ++it)
//    for (Good good : business.m_store)
    {
        Good good = *(it);
        QString name = good.first;
//        m_wgoods[i]->ncur = order->count(name);
//        m_wgoods[i]->nremian = good.second;
        m_wgoods[i]->name = name;
        m_wgoods[i]->updateUI();
    }
}

