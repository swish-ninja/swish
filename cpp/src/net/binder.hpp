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




#ifndef __SWISH_NET_SERVER__
#define __SWISH_NET_SERVER__


#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

#include "common/exception.hpp"
#include "message_handler.hpp"
#include "connection.hpp"

namespace swish {
    namespace net {

        class server : private boost::noncopyable
        {
        public:
            /// Construct the server to listen on the specified TCP address and port, and
            /// serve up files from the given directory.
            explicit server(const std::string& ip_address, const std::string& port, std::size_t thread_pool_size);

            /// Run the server's io_service loop.
            void start();

            /// Stop the server
            void stop();

        private:
            /// Initiate an asynchronous accept operation.
            void start_accept();

            /// Handle completion of an asynchronous accept operation.
            void handle_accept(const boost::system::error_code& e);

            /// The number of threads that will call io_service::run().
            std::size_t _thread_pool_size;

            /// The io_service used to perform asynchronous operations.
            boost::asio::io_service _io_service;

            /// Acceptor used to listen for incoming connections.
            boost::asio::ip::tcp::acceptor _acceptor;

            /// The next connection to be accepted.
            connection_ptr _new_connection;

            /// The handler for all incoming requests.
            message_handler _msg_handler;

            /// The threads that will be running the io_service
            std::vector<boost::shared_ptr<boost::thread> > _threads;
        };
    }
}



#endif //__SWISH_NET_SERVER__