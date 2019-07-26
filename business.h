#ifndef BUSINESS_H
#define BUSINESS_H

#include <QObject>
#include <map>
#include <set>

typedef std::multiset<std::string> Order;
typedef std::pair<std::string, int> Good;

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
    std::map<std::string, int> m_store;
    std::vector< Order > m_orders;
    void tryOrder(Order order);
};

#endif // BUSINESS_H
