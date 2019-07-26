#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void updateOrder(int);
public:
    std::vector<QPushButton*> m_btnOrders;
};

#endif // MAINWINDOW_H
