#include <iostream>
#include <chrono>
#include <string>
#include "database_client.h"
using namespace std;

int main()
{
    boost::asio::io_context service;
    std::string IP = "127.0.0.1";
    string port = "9090";
    Database_client client(service, IP, port);
    client.startShell();

    return 0;
}
