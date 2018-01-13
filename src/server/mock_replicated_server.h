#include "gmock/gmock.h"
#define CLIENT_HOST "localhost"
#define CLIENT_PORT 1336
#define CLIENT_FD 1
#define NEXT_SERVER_FD 2
#define HEAD_PORT 1000
#define TAIL_PORT 1100

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class MockReplicatedServer: public ReplicatedServer {
public:
    MockReplicatedServer(int port) : ReplicatedServer(port){
        ON_CALL(*this, send_redis_cmd(_)).WillByDefault(Invoke(this, &MockReplicatedServer::do_redis_cmd));
        ON_CALL(*this, connect_to_server("localhost", _)).WillByDefault(Return(NEXT_SERVER_FD));
    }
    string do_redis_cmd(Request::RedisRequest request);
    MOCK_METHOD1(send_redis_cmd, string(Request::RedisRequest request));
    MOCK_METHOD2(recv_msg, bool(int fd, string& msg));
    MOCK_METHOD2(send_msg, void(int fd, string msg));
    MOCK_METHOD2(connect_to_server, int(string host, int port));
    MOCK_METHOD2(get_client_fd, int(string host, int port));
};

string MockReplicatedServer::do_redis_cmd(Request::RedisRequest request) {
    // Call this method if we actually want to send a request to the running redis server
    return ReplicatedServer::send_redis_cmd(request);
}
