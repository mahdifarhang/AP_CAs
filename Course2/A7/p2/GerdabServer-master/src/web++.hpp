#ifndef WEBPLUSPLUS_HPP_
#define WEBPLUSPLUS_HPP_

#include <dirent.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#define SERVER_NAME "Web++"
#define SERVER_VERSION "1.0.1"

#define BUFSIZE 8096

class Request {
public:
    Request();
    std::string method;
    std::string path;
    std::string params;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query;
    std::map<std::string, std::string> cookies;
    std::string getParam(std::string key){
        return query[key];
    }
    std::string getHeader(std::string key){
        return headers[key];
    }
};
class Response {
public:
    Response();
    int code;
    std::string phrase;
    std::string type;
    std::string date;
    std::stringstream body;
    void send(std::string str);
    void send(const char* str);
};
class RequestHandler{
public:
    virtual void callback(Request*, Response*) = 0;
};
class Exception : public std::exception {
    public:
        Exception();
        Exception(const char* pStr);
        const char* getMessage();
    private:
        const char* pMessage;

};

struct Route {
    std::string path;
    std::string method;
    RequestHandler* handler;
    std::string params;
};



class WPPServer {
    public:
        void get(std::string, RequestHandler*);
        void post(std::string, RequestHandler*);
        void all(std::string, RequestHandler*);
        bool start(int, std::string);
        bool start(int);
        bool start();
    private:
        void* main_loop(void*);
        void parse_headers(char*, Request*, Response*);
        bool match_route(Request*, Response*);
        std::string trim(std::string);
        void split(std::string, std::string, int, std::vector<std::string>*);
        std::vector<Route> ROUTES;
        std::map<std::string, std::string> mime;

};

#endif