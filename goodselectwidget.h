#ifndef GOODSELECTWIDGET_H
#define GOODSELECTWIDGET_H

#include <QWidget>

class GoodSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoodSelectWidget(QWidget *parent = nullptr);

signals:

public:
    const QString pref = "remian number: ";
    int ncur, nremian;
};

#endif // GOODSELECTWIDGET_H
