#ifndef GOODSELECTWIDGET_H
#define GOODSELECTWIDGET_H

#include <QtWidgets>
#include "business.h"

class GoodSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoodSelectWidget(QString Picname, Order *&porder, QWidget *parent = nullptr);
    void updateUI();

    void showGood(QString name);

    void mouseReleaseEvent(QMouseEvent*) override;

    void setOrder(Order* order);

signals:

public:
    const QString pref = "remian number: ";
//    int ncur=0, nremian=0;
    QString name;

private:
    QLabel *number, *remain, *wname;
    QLabel* pic;
    Order* &porder;
};

#endif // GOODSELECTWIDGET_H
