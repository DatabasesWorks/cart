#ifndef GOODSELECTWIDGET_H
#define GOODSELECTWIDGET_H

#include <QtWidgets>

class GoodSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoodSelectWidget(QWidget *parent = nullptr);
    void updateUI();

signals:

public:
    const QString pref = "remian number: ";
    int ncur, nremian;
    std::string name;

private:
    QLabel *number, *remain, *wname;
};

#endif // GOODSELECTWIDGET_H
