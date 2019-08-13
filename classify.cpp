#include "classify.h"
#include "business.h"

ClassifyWidget::ClassifyWidget()
{
    auto &b = Business::instance();
    auto lay = new QGridLayout(this);

    for (int i=0; i<3; ++i)
        for (int j=0; j<5; ++j)
        {
            auto it = std::next(b.m_store.begin(), 3*i + j);
            auto btn = new QPushButton;


            btn->setIcon(QIcon(QPixmap::fromImage(b.m_images[it->first]).scaled(100,100)));
            btn->setIconSize(QSize(100,100));
            connect(btn, &QPushButton::clicked, [=]()
            {
                id = 3*i + j;
            });
            lay->addWidget(btn, i, j);
        }

}
