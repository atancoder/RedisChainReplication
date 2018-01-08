#include "gmock/gmock.h"

class MockReplicatedServer: public ReplicatedServer {
public:
    MockReplicatedServer(int port, optional<pair<string, int>> next_server) : ReplicatedServer(port, next_server){}
    string do_redis_cmd(Request request);
    MOCK_METHOD1(send_redis_cmd, string(Request request));
    MOCK_METHOD2(recv_msg, bool(int fd, string& msg));
    MOCK_METHOD2(send_msg, void(int fd, string msg));
};

string MockReplicatedServer::do_redis_cmd(Request request) {
    return ReplicatedServer::send_redis_cmd(request);
}
