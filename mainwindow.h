#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "business.h"
class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setOrderIcon(int index, Order order);

    void startPick();
signals:
    void updateOrder(int);
public:
    std::vector<QPushButton*> m_btnOrders;
};

#endif // MAINWINDOW_H
