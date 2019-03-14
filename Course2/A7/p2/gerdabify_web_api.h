#ifndef GERDABIFY_WEB_API_H_
#define GERDABIFY_WEB_API_H_

#include <iostream>
#include <map>
#include <string>
#include "gerdabServer.hpp"


using namespace std;



class GerdabifyWebAPI : public RequestHanler
{
public:

private:
	
};



class HomePageHandler: public RequestHandler{
    void callback(Request* req, Response* res) {
        cout<<req->getParam("token")<<endl;
        res->body << "<body><h1>GerdabServer</h1><p>This is Gerdab Server Home Page</p></body>";
    }
};
class FormHandler: public RequestHandler{
    void callback(Request* req, Response* res) {
        cout<<req->getParam("token")<<endl;
        res->body << "<body><h1>Gerdab Server</h1><p>This is gerdab server main page<p/></body>";
    }
};
int main(int argc, const char* argv[]) {
    try {
        Server server;
        RequestHandler* homePage = new HomePageHandler();
        RequestHandler* form = new FormHandler();
        server.get("/home", homePage);
        server.post("/form", form);
        cout << "Listening on port 5000" << endl;
        server.start(5000);
    } catch(Exception e) {
        cerr << "WebServer: " << e.getMessage() << endl;
    }

    return EXIT_SUCCESS;
}





#endif