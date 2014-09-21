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

#ifndef __SWISH_COMMON_EXCEPTION__
#define __SWISH_COMMON_EXCEPTION__

#include <boost/exception/all.hpp>
#include <string>


namespace swish {
    namespace common {

        /***************************************************************************************
        The exception class will be the only exception thrown by the library. It will be handled
        internally and will NEVER cross the library's boundaries.

        Usage:
            try {
                throw swish::common::exception() << swish::common::error_code(1);
            } catch (swish::common::exception &x) {
                if ( int const * code = boost::get_error_info< swish::common::error_code >( x ) ) {
                    std::cerr << "swish error code : " << *code;
                }
            }

        ***************************************************************************************/
        typedef boost::error_info<struct tag_error_code, int> error_code; 
        typedef boost::error_info<struct tag_error_msg, std::string> error_msg;

        struct exception : virtual boost::exception, virtual std::exception { }; 
        
    }
}


#endif // __SWISH_COMMON_EXCEPTION__