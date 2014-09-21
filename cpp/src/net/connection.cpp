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
#include <boost/bind.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include "connection.hpp"


using namespace swish::common;
using namespace swish::net;


void connection::start() {
    _socket.async_read_some(boost::asio::buffer(_buffer),
        _strand.wrap(
            boost::bind(
                &connection::handle_read, 
                shared_from_this(), 
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        )
    );
}

void connection::handle_read(const boost::system::error_code& e,
    std::size_t bytes_transferred)
{
    if (!e) {
        boost::tribool result;
    }
}

void connection::handle_write(const boost::system::error_code& e)
{
    if (!e){
    
    }
}