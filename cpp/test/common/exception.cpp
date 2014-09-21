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



#include "common/exception.hpp"

#include <boost/test/unit_test.hpp>
#include <sstream>



BOOST_AUTO_TEST_SUITE(ut_exception)

// test to see if the error code comes through
BOOST_AUTO_TEST_CASE(test_error_code)
{
    int err_code = 41;
    try {
        throw swish::common::exception() << swish::common::error_code(err_code);
    } catch (swish::common::exception &x) {
        if (int const * code = boost::get_error_info< swish::common::error_code >(x)) {
            BOOST_CHECK(err_code == *code);
        } else {
            BOOST_FAIL("Failed to get error code!");
        }
    }
}


// test to see if the error message comes through
BOOST_AUTO_TEST_CASE(test_error_message)
{
    std::string message("test message");
    try {
        throw swish::common::exception() << swish::common::error_msg(message);
    } catch (swish::common::exception &x) {
        if (std::string const * msg = boost::get_error_info< swish::common::error_msg >(x)) {
            BOOST_CHECK(message == *msg);
        } else {
            BOOST_FAIL("Failed to get string message!");
        }
    }
}


// test to see if the error message and code come through
BOOST_AUTO_TEST_CASE(test_error_message_code)
{
    int err_code = 41; 
    std::string message("test message");
    try {
        throw swish::common::exception() << swish::common::error_code(err_code) << swish::common::error_msg(message);
    } catch (swish::common::exception &x) {
        // check for the error code
        if (int const * code = boost::get_error_info< swish::common::error_code >(x)) {
            BOOST_CHECK(err_code == *code);
        } else {
            BOOST_FAIL("Failed to get error code!");
        }
        
        // check for the error message
        if (std::string const * msg = boost::get_error_info< swish::common::error_msg >(x)) {
            BOOST_CHECK(message == *msg);
        } else {
            BOOST_FAIL("Failed to get string message!");
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()