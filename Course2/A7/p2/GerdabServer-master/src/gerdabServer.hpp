#ifndef GERDABSERVER_HPP_
#define GERDABSERVER_HPP_


#include "web++.hpp"
#include <map>
#include <string>
class Server
{
private:
    WPPServer* server;
public:
    Server();
    void start(int port);
    void get(std::string path, RequestHandler* handler);
    void post(std::string path, RequestHandler* handler);
};


#endif