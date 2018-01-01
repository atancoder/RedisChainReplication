#pragma once //Ensures this file is only compiled once

#include <iostream>
#include <string>
#include <boost/optional.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <cpp_redis/cpp_redis>
#include <vector>
#include <RepServer_client.pb.h> // Google protobuf

using boost::optional;
using namespace std;

#define MAX_VAL_SIZE 1024

// Define our own static parse function
void parse_client_request(string, vector<string>&);

class ReplicatedServer
{

public:
    ReplicatedServer (int port, optional<pair<string, int>> prev_server, optional<pair<string, int>> next_server);
    void run();
    void create();
    void serve();
    void handle_request(int client_fd);
    void connect_to_redis();
    string recv_msg(int fd);
    void send_msg(int fd, string msg);
    string send_redis_cmd(string request);

private:
    int server_fd_;
    int port_;
    int max_fd_;
    pair<string, int> redis_addr_;
    vector<int> client_fds_;
    fd_set readfds_;
    optional<pair<string, int>> prev_server_;
    optional<pair<string, int>> next_server_;
    cpp_redis::client redis_client_;
};
