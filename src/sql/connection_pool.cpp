//
// connection_pool.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2013 Alex Caudill (alex at furosys.com)
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <vector>
#include <market_config.hpp>
#include <market_types.hpp>
#include <connection_pool.hpp>

const std::string database(DATABASE);
const std::string url(DBHOST);
const std::string user(USER);
const std::string password(PASSWORD);

ConnectionPool::ConnectionPool(uint32_t max_connections) {
    for (uint32_t i = 0; i < max_connections; i++) {
        SharedConnectionPtr con = createConnection();
        free_connections.push_back(con);
    }
}

SharedConnectionPtr ConnectionPool::getConnection() {
    if ( free_connections.size() > 0 ) {
        SharedConnectionPtr con = *(free_connections.end() - 1);
        free_connections.pop_back();
        return con;
    } else { 
        return createConnection();
    }
}

void ConnectionPool::releaseConnection(SharedConnectionPtr con) {
    free_connections.push_back(con);
}

SharedConnectionPtr ConnectionPool::createConnection() {
    try {
        sql::Driver *driver;
        driver = get_driver_instance();
        auto con = std::shared_ptr<sql::Connection>(driver->connect(url, user, password));
        con->setSchema(database);
        return con;
    } catch (sql::SQLException) {
        std::cout << "Failed to connect to database. Exiting..." << std::endl;
        exit(1);
    }
}