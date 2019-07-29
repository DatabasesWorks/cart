#ifndef GOODROWWIDGET_H
#define GOODROWWIDGET_H

#include <QtWidgets>
#include "business.h"

class GoodRowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoodRowWidget(QWidget *parent = nullptr);
    void setGood(QString good, Order order);

    void mouseReleaseEvent(QMouseEvent*) override;

signals:

public:
    QLabel * m_goodImg, *m_goodName, *m_cnt;
    QPushButton* m_add, *m_sub;



};

#endif // GOODROWWIDGET_H
