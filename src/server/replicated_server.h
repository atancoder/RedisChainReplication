#pragma once //Ensures this file is only compiled once

#include "server.h"
#include <cpp_redis/cpp_redis>
#include <RepServer_client.pb.h> // Google protobuf

using boost::optional;
using namespace std;

// Define our own static parse function
void parse_client_request(string request, vector<string>& redis_args);

class ReplicatedServer : public Server
{

public:
    ReplicatedServer (int port, optional<pair<string, int>> next_server);
    void handle_request(int client_fd);
    bool is_tail_server();
    void update_prev_server_existance(bool has_prev_server);
    string send_redis_cmd(string request);
    ~ReplicatedServer() {};

private:
    pair<string, int> redis_addr_;
    bool has_prev_server_;
    int next_server_fd_;
    cpp_redis::client redis_client_;
};
