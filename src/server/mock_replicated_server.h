#include "gmock/gmock.h"
#define CLIENT_HOST "localhost"
#define CLIENT_PORT 1336
#define CLIENT_FD 1
#define FIRST_SERVER_PORT 1337
#define FIRST_SECOND_FD 2
#define SECOND_SERVER_PORT 1338
#define SECOND_THIRD_FD 3
#define THIRD_SERVER_PORT 1339

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class MockReplicatedServer: public ReplicatedServer {
public:
    MockReplicatedServer(int port, optional<pair<string, int>> next_server) : ReplicatedServer(port, next_server){
        ON_CALL(*this, send_redis_cmd(_)).WillByDefault(Invoke(this, &MockReplicatedServer::do_redis_cmd));
        ON_CALL(*this, connect_to_server("localhost", SECOND_SERVER_PORT)).WillByDefault(Return(FIRST_SECOND_FD));
        ON_CALL(*this, connect_to_server("localhost", THIRD_SERVER_PORT)).WillByDefault(Return(SECOND_THIRD_FD));
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
