#ifndef BUSINESS_H
#define BUSINESS_H

#include <QObject>
#include <map>
#include <set>

class Business : public QObject
{
    Q_OBJECT
public:
    explicit Business(QObject *parent = nullptr);
    void initStore();

signals:

public:
    std::map<std::string, int> m_store;
    std::vector<std::multiset<std::string>> m_orders;
};

#endif // BUSINESS_H
