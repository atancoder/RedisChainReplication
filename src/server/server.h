#pragma once //Ensures this file is only compiled once

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <set>
#include <boost/optional.hpp>

using namespace std;
#define MAX_VAL_SIZE 1024

class Server
{
public:
    Server (int port);
    virtual bool recv_msg(int fd, string& msg);
    virtual void send_msg(int fd, string msg);
    virtual void serve();
    virtual void run();
    virtual void handle_request(int client_fd);
    virtual void create_server_socket();
    virtual ~Server() {}

private:
    int server_fd_;
    int port_;
    fd_set readfds_;
    set<int> client_fds_;
};
