#ifndef BUSINESS_H
#define BUSINESS_H

#include <QObject>
#include <map>
#include <set>

typedef std::multiset<QString> Order;
typedef std::pair<QString, int> Good;

class Business : public QObject
{
    Q_OBJECT
public:
    static Business& instance();
private:
    Business();
    void initStore();

signals:

public:
    const int size = 20;
    std::map<QString, int> m_store;
    std::vector< Order > m_orders;
    void tryOrder(Order order);
};

#endif // BUSINESS_H
