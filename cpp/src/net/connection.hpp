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



#ifndef __SWISH_NET_CONNECTION__
#define __SWISH_NET_CONNECTION__


#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "common/exception.hpp"
#include "message_handler.hpp"

namespace swish {
    namespace net {

        /// Represents a single connection
        class connection : 
            public boost::enable_shared_from_this<connection>,
            private boost::noncopyable
        {
        public:
            /// Construct a connection with the given io_service.
            explicit connection(boost::asio::io_service& io_service, message_handler& handler) 
                : _strand(io_service), _socket(io_service), _msg_handler(handler)
            {}

            /// Get the socket associated with the connection.
            boost::asio::ip::tcp::socket& socket() { return _socket; }

            /// Start the first asynchronous operation for the connection.
            void start();

        private:
            /// Handle completion of a read operation.
            void handle_read(const boost::system::error_code& e,
                std::size_t bytes_transferred);

            /// Handle completion of a write operation.
            void handle_write(const boost::system::error_code& e);

            /// Strand to ensure the connection's handlers are not called concurrently.
            boost::asio::io_service::strand _strand;

            /// Socket for the connection.
            boost::asio::ip::tcp::socket _socket;

            /// The handler used to process the incoming request.
            message_handler& _msg_handler;

            /// Buffer for incoming data.
            boost::array<char, 8192> _buffer;
        };

        typedef boost::shared_ptr<connection> connection_ptr;
    }
}



#endif //__SWISH_NET_CONNECTION__