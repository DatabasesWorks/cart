#pragma once

#include <QThread>
class ClassifyWidget;
class OrderServer : public QThread
{
    Q_OBJECT
public:
    OrderServer();
    void run() override;
    ClassifyWidget *wclassify;
};
