#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H
#include <string>
#include <boost/asio.hpp>
#include "query.h"
class Database_client
{
private:

    std::string _ipAddress;
    std::string _port;
    boost::asio::ip::tcp::resolver _resolver;
    boost::asio::ip::tcp::resolver::results_type _endpoints;
    boost::asio::ip::tcp::socket _socket;
    std::string curDatabaseName;
    std::string resultFromServer;
protected:
    void _sendQuery(const std::string &query);
    void _read();
    std::string _timeStamp();
public:
    Database_client(boost::asio::io_context &service, const std::string ipAddress, const std::string port);
    Database_client(const Database_client &other) = delete;
    Database_client(const Database_client &&other) = delete;
    void startShell();
    void sendQuery(const Query &query);

    std::string result();
    ~Database_client();
};

#endif // DATABASE_CLIENT_H
