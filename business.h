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

    void arrangeLeftGoods();

private:
    Business();
    void initStore();


signals:
    void orderChanged(Order* order);

public:
    const int size = 15;
    std::map<QString, int> m_store;
    std::map<QString, QString> m_fullname;
    std::map<QString, int> m_ids;


    std::vector< Order > m_orders;

    std::vector< Order > m_havePicked;
    bool lockOrder = false;

    static std::map<QString, QImage> m_images;

};

#endif // BUSINESS_H
