#include "gerdabServer.hpp"
using namespace std;
Server::Server()
{
    server = new WPPServer();
}
void Server::start(int port){
    server->start(port);
}
void Server::get(string path, RequestHandler* handler)
{
    server->get(path, handler);
}
void Server::post(string path, RequestHandler* handler)
{
    server->post(path, handler);
}
