/***************************************************************
Swish
Copyright(c) 2014, Swish, All rights reserved.

This library is free software; you can redistribute it and / or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.
***************************************************************/



#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


#include "server.hpp"

using namespace swish::common;
using namespace swish::net;


server::server(const std::string& ip_address, const std::string& port, std::size_t thread_pool_size)
    : _thread_pool_size(thread_pool_size), _acceptor(_io_service), _new_connection()
{
    
    // Open the acceptor with the option to reuse the address
    boost::asio::ip::tcp::resolver resolver(_io_service);
    boost::asio::ip::tcp::resolver::query query(ip_address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    start_accept();
}


void server::start()
{
    // Create a pool of threads to run all of the io_services.
    for (std::size_t i = 0; i < _thread_pool_size; ++i) {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
            boost::bind(&boost::asio::io_service::run, &_io_service)));
        _threads.push_back(thread);
    }
}

void server::stop() {
    // Stop the service and ...
    _io_service.stop();

    // ... wait for all the threads to stop
    for (std::size_t i = 0; i < _threads.size(); ++i) {
        _threads[i]->join();
    }
}

void server::start_accept()
{
    _new_connection.reset(new connection(_io_service, _msg_handler));
    _acceptor.async_accept(
        _new_connection->socket(),
        boost::bind(
            &server::handle_accept,
            this,
            boost::asio::placeholders::error
        )
    );
}


void server::handle_accept(const boost::system::error_code& e)
{
    if (!e) {
        _new_connection->start();
    }

    start_accept();
}
