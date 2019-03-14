#include "web++.hpp"

using namespace std;
Request::Request() {}

Response::Response() {
        code = 200;
        phrase = "OK";
        type = "text/html";
        body << "";
        char buffer[100];
        time_t now = time(0);
        struct tm tstruct = *gmtime(&now);
        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", &tstruct);
        date = buffer;
    }

void Response::send(string str) {
        body << str;
    };

void Response::send(const char* str) {
        body << str;
    };

void WPPServer::split(string str, string separator, int max, vector<string>* results){
        int i = 0;
        size_t found = str.find_first_of(separator);

        while(found != string::npos){
            if(found > 0){
                results->push_back(str.substr(0, found));
            }
            str = str.substr(found+1);
            found = str.find_first_of(separator);

            if(max > -1 && ++i == max) break;
        }

        if(str.length() > 0){
            results->push_back(str);
        }
    }

string WPPServer::trim(string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());

        return s;
    }

void WPPServer::parse_headers(char* headers, Request* req, Response* res) {
        // Parse request headers
        int i = 0;
        char * pch;
        for (pch = strtok(headers, "\n"); pch; pch = strtok(NULL, "\n" ))
        {
            if(i++ == 0)  {
                vector<string> R;
                string line(pch);
                this->split(line, " ", 3, &R);
                if(R.size() != 3) {
                    //                throw error
                }

                req->method = R[0];
                req->path = R[1];

                size_t pos = req->path.find('?');

                // We have GET params here
                if(pos != string::npos)  {
                    vector<string> Q1;
                    this->split(req->path.substr(pos + 1), "&", -1, &Q1);

                    for(vector<string>::size_type q = 0; q < Q1.size(); q++) {
                        vector<string> Q2;
                        this->split(Q1[q], "=", -1, &Q2);

                        if(Q2.size() == 2) {
                            req->query[Q2[0]] = Q2[1];
                        }
                    }

                    req->path = req->path.substr(0, pos);
                }
            } else {
                vector<string> R;
                string line(pch);
                this->split(line, ": ", 2, &R);

                if(R.size() == 2) {
                    req->headers[R[0]] = R[1];

                    // Yeah, cookies!
                    if(R[0] == "Cookie") {
                        vector<string> C1;
                        this->split(R[1], "; ", -1, &C1);

                        for(vector<string>::size_type c = 0; c < C1.size(); c++) {
                            vector<string> C2;
                            this->split(C1[c], "=", 2, &C2);

                            req->cookies[C2[0]] = C2[1];
                        }
                    }
                }
            }
        }
    }

void WPPServer::get(string path, RequestHandler* callback) {
        Route r = {
                path,
                "GET",
                callback
        };

        ROUTES.push_back(r);
    }

void WPPServer::post(string path, RequestHandler*callback) {
        Route r = {
                path,
                "POST",
                callback
        };

        ROUTES.push_back(r);
    }

void WPPServer::all(string path, RequestHandler*callback) {
        Route r = {
                path,
                "ALL",
                callback
        };

        ROUTES.push_back(r);
    }

bool WPPServer::match_route(Request* req, Response* res) {
        for (vector<Route>::size_type i = 0; i < ROUTES.size(); i++) {
            if(ROUTES[i].path == req->path && (ROUTES[i].method == req->method || ROUTES[i].method == "ALL")) {
                req->params = ROUTES[i].params;

                ROUTES[i].handler->callback(req, res);

                return true;
            }
        }

        return false;
    }

void* WPPServer::main_loop(void* arg) {
        int* port = reinterpret_cast<int*>(arg);

        int newsc;

        int sc = socket(AF_INET, SOCK_STREAM, 0);

        if (sc < 0) {
            throw Exception("ERROR opening socket");
        }

        struct sockaddr_in serv_addr, cli_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(*port);

        if (::bind(sc, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
            throw Exception("ERROR on binding");
        }

        listen(sc, 5);

        socklen_t clilen;
        clilen = sizeof(cli_addr);

        while(true) {
            newsc = accept(sc, (struct sockaddr *) &cli_addr, &clilen);

            if (newsc < 0) {
                throw Exception("ERROR on accept");
            }

            // handle new connection
            Request req;
            Response res;

            static char headers[BUFSIZE + 1];
            long ret = read(newsc, headers, BUFSIZE);
            if(ret > 0 && ret < BUFSIZE) {
                headers[ret] = 0;
            } else {
                headers[0] = 0;
            }

            this->parse_headers(headers, &req, &res);

            if(!this->match_route(&req, &res)) {
                res.code = 404;
                res.phrase = "Not Found";
                res.type = "text/plain";
                res.send("Not found");
            }

            char header_buffer[BUFSIZE];
            string body = res.body.str();
            size_t body_len = strlen(body.c_str());

            // build http response
            sprintf(header_buffer, "HTTP/1.0 %d %s\r\n", res.code, res.phrase.c_str());

            // append headers
            sprintf(&header_buffer[strlen(header_buffer)], "WPPServer: %s %s\r\n", SERVER_NAME, SERVER_VERSION);
            sprintf(&header_buffer[strlen(header_buffer)], "Date: %s\r\n", res.date.c_str());
            sprintf(&header_buffer[strlen(header_buffer)], "Content-Type: %s\r\n", res.type.c_str());
            sprintf(&header_buffer[strlen(header_buffer)], "Content-Length: %zd\r\n", body_len);

            // append extra crlf to indicate start of body
            strcat(header_buffer, "\r\n");

            ssize_t t;
            t = write(newsc, header_buffer, strlen(header_buffer));
            t = write(newsc, body.c_str(), body_len);
        }
    }

bool WPPServer::start(int port, string host) {
//         pthread_t worker;

//         for(int i = 0; i < 1; ++i) {
//              int rc = pthread_create (&worker, NULL, &mainLoop, NULL);
//              assert (rc == 0);
//         }

        this->main_loop(&port);

        return true;
    }

bool WPPServer::start(int port) {
        return this->start(port, "0.0.0.0");
    }

bool WPPServer::start() {
        return this->start(80);
    }

Exception::Exception(){}

Exception::Exception(const char* pStr) {
        pMessage = pStr;
    }

const char* Exception::getMessage(){ return pMessage; }
