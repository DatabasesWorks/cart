#pragma once

#include <QThread>

class OrderServer : public QThread
{
    Q_OBJECT
public:
    void run() override;
};
