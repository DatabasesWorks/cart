#ifndef BUSINESS_H
#define BUSINESS_H

#include <QObject>
#include <map>
#include <set>
#include <iostream>

typedef std::multiset<QString> Order;
typedef std::pair<QString, int> Good;

class Business : public QObject
{
    Q_OBJECT
public:
    static Business& instance();
    void orderSub(Order *order, QString name);
    void orderAdd(Order *order, QString name);

private:
    Business();
    void initStore();


signals:
    void orderChanged(Order* order);

public:
    const int size = 20;
    std::map<QString, int> m_store;
    std::vector< Order > m_orders;
};

#endif // BUSINESS_H
