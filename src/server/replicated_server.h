#pragma once //Ensures this file is only compiled once

#include <iostream>
#include <string>
#include <boost/optional.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <cpp_redis/cpp_redis>

using boost::optional;
using namespace std;

#define PORT 1337
#define MAX_VAL_SIZE 1024

class ReplicatedServer
{

public:
    ReplicatedServer (int port, optional<pair<string, int>> prev_server, optional<pair<string, int>> next_server);
    void run();

private:
    int server_fd_;
    int port_;
    int max_fd_;
    pair<string, int> redis_addr_;
    vector<int> client_fds_;
    fd_set readfds_;
    optional<pair<string, int>> prev_server_;
    optional<pair<string, int>> next_server_;
    void create();
    void serve();
    void handle_request(int client_fd);
    int connect_to_redis();
    string recv_msg(int fd);
    void send_msg(int fd, string msg);
};
