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
    void handle_redis_request(Request::RedisRequest request, string orig_request_str);
    void handle_master_request(Request::MasterRequest request);
    bool is_tail_server();
    virtual string send_redis_cmd(Request::RedisRequest request);
    virtual int get_client_fd(string host, int port);
    virtual void update_next_server(optional<pair<string, int>> next_server);
    ~ReplicatedServer() {};

private:
    int next_server_fd_;
    pair<string, int> redis_addr_;
    cpp_redis::client redis_client_;
};
