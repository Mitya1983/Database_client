#include "database_client.h"
#include <iostream>
#include <chrono>
#include <ctime>
Database_client::Database_client(boost::asio::io_context &service, const std::string ipAddress, const std::string port) :
    _ipAddress(ipAddress), _port(port), _resolver(service), _socket(service)
{
    _endpoints = _resolver.resolve(_ipAddress, _port);
}

void Database_client::startShell()
{
    std::cout << "Please enter Database name which you want to work with: ";
    std::getline(std::cin, curDatabaseName);
    std::cout << curDatabaseName + '>';
    std::string input;
    std::getline(std::cin, input);
    while (true)
    {
        if (input == "q")
            break;
        std::string query = curDatabaseName + '\n' + input;
        boost::asio::connect(_socket, _endpoints);
        _sendQuery(query);
        _read();
        std::cout << curDatabaseName + '>';
        input.clear();
        std::getline(std::cin, input);
    }
}

void Database_client::_sendQuery(const std::string &query)
{
    boost::system::error_code error;
    std::string _query = std::move(query);
    boost::asio::write(_socket, boost::asio::buffer(_query), error);
    if( !error ) {
        std::cout << _timeStamp() << ": Query \"" << _query << "\" sent to Database \"" << curDatabaseName << "\"" << std::endl;
    }
    else {
        std::cout << _timeStamp()  << ": Send query \"" << _query << "\" to Database \"" << curDatabaseName << "\" failed: " << error.message() << std::endl;
    }
}

void Database_client::_read()
{
    boost::system::error_code error;
    boost::asio::streambuf buffer;

        boost::asio::read(_socket, buffer, error);
        if (error && error != boost::asio::error::eof)
            std::cerr << error << std::endl;
        std::cout << buffer.size() << std::endl;
        resultFromServer = boost::asio::buffer_cast<const char*>(buffer.data());
        std::cout << resultFromServer << std::endl;
}

std::string Database_client::_timeStamp()
{
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timeStamp(20, '\0');
    std::strftime(&timeStamp[0], 20, "%d-%m-%Y %H:%M:%S", std::localtime(&time));
    return timeStamp;
}

std::string Database_client::result()
{
    return resultFromServer;
}

Database_client::~Database_client()
{
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    _socket.close();
}

