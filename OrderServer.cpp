#include "OrderServer.h"
#include "business.h"
#include "classify.h"
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
using namespace boost;
using boost::asio::ip::tcp;

using namespace  std;

OrderServer::OrderServer()
{
    wclassify = new ClassifyWidget;
    wclassify->show();
//    connect(this, &OrderServer::show, wclassify, )
}

void OrderServer::run()
{
    auto &business = Business::instance();

    //socket
    asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1111));



    std::cerr<<"======waiting for client's request======"<<std::endl;
    while(1)
    {
        tcp::socket socket(io_service);
        acceptor.accept(socket);

        string classify(100, 0);
        //cmd receive
//        boost::asio::read(socket, boost::asio::buffer(&classify, 1));
        boost::system::error_code ec;
        int len = socket.read_some(boost::asio::buffer((char*)classify.data(), classify.size()), ec);

        cerr<<"len ="<<len<<endl;
        cerr<<"message ="<<ec.message()<<endl;

        if (!len) continue;

        string res = classify.substr(0, len);

        std::cerr<<"recv msg from client:"<<res<<std::endl;
        int goodid = std::stoi(res);



        wclassify->id = -1;
        while(wclassify->id == -1)
        {
            wclassify->show();
            usleep(100000);
        }
        goodid = wclassify->id;
        wclassify->id = -1;
        wclassify->hide();



//        int goodid = resid - '0';
        if (goodid < 0 || goodid > Business::instance().m_store.size()) break;

        QString good = next(business.m_store.begin(), goodid)->first;

        int orderid = -1;

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


        string pos = std::to_string(orderid);
        cerr<<"send "<<pos<<endl;
        boost::asio::write(socket, boost::asio::buffer(pos.data(), pos.size()));

    }


    return;
}
