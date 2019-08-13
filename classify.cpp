#include "classify.h"
#include "business.h"

ClassifyWidget::ClassifyWidget()
{
    auto &b = Business::instance();
    auto lay = new QGridLayout(this);

    int row = 4;
    int col = 4;

    for (int i=0; i<row; ++i)
        for (int j=0; j<col; ++j)
        {
            if (col*i + j >= b.m_store.size())
            {
                auto btn = new QPushButton;


                auto ico = new QPixmap(100,100);
                ico->fill(Qt::transparent);
                btn->setIcon(QIcon( *ico ));
                btn->setIconSize(QSize(100,100));
                connect(btn, &QPushButton::clicked, [=]()
                {
                    id = 0;
                });
                lay->addWidget(btn, i, j);
                continue;
            }
            auto it = std::next(b.m_store.begin(), col*i + j);
            auto btn = new QPushButton;


            btn->setIcon(QIcon(QPixmap::fromImage(b.m_images[it->first]).scaled(100,100)));
            btn->setIconSize(QSize(100,100));
            connect(btn, &QPushButton::clicked, [=]()
            {
                id = col*i + j + 1;
            });
            lay->addWidget(btn, i, j);
        }

}
