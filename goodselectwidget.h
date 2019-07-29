#ifndef GOODSELECTWIDGET_H
#define GOODSELECTWIDGET_H

#include <QtWidgets>

class GoodSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GoodSelectWidget(QString name, QWidget *parent = nullptr);
    void updateUI();

    void showGood(QString name);

    void mouseReleaseEvent(QMouseEvent*) override;

signals:

public:
    const QString pref = "remian number: ";
    int ncur=0, nremian=0;
    QString name;

private:
    QLabel *number, *remain, *wname;
    QLabel* pic;
};

#endif // GOODSELECTWIDGET_H
