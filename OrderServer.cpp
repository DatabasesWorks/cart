#include "OrderServer.h"
#include "business.h"
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
using namespace boost;
using boost::asio::ip::tcp;

using namespace  std;

void OrderServer::run()
{
    auto &business = Business::instance();

    //socket
    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

    std::cerr<<"======waiting for client's request======"<<std::endl;
    while(1)
    {
        tcp::socket socket(io_service);
        acceptor.accept(socket);

        char classify;
        //cmd receive
        boost::asio::read(socket, boost::asio::buffer(&classify, 1));

        std::cerr<<"recv msg from client:"<<classify<<std::endl;

        int goodid = classify - '0';
        if (goodid < 0 || goodid > Business::instance().m_store.size()) break;

        QString good = next(business.m_store.begin(), goodid)->first;

        char orderid;

        for (int i =0; i< business.m_orders.size(); ++i)
        {
            if (business.m_orders[i].count(good) > business.m_havePicked[i].count(good))
            {
                orderid = i;
                business.m_havePicked[i].insert(good);
                emit business.orderChanged(business.m_orders.data() + orderid);
                break;
            }
        }


        boost::asio::write(socket, boost::asio::buffer(&orderid, 1));

    }


    return;
}
