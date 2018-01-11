#pragma once //Ensures this file is only compiled once

#include "server.h"
#include <cpp_redis/cpp_redis>
#include <RepServer_client.pb.h> // Google protobuf

using boost::optional;
using namespace std;

class ReplicatedServer : public Server
{

public:
    ReplicatedServer (int port, optional<pair<string, int>> next_server);
    void handle_request(string request_str);
    bool is_tail_server();
    void update_prev_server_existance(bool has_prev_server);
    virtual string send_redis_cmd(Request request);
    ~ReplicatedServer() {};
    int next_server_fd_;

private:
    pair<string, int> redis_addr_;
    bool has_prev_server_;
    int get_client_fd(string addr, int port);
    cpp_redis::client redis_client_;
};
