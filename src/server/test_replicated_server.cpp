#include "replicated_server.h"
#include "mock_replicated_server.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class ReplicatedServerTest : public ::testing::Test {
public:
    static string set_request;
    static string get_request;
    virtual void SetUp() {
        tail_server = new MockReplicatedServer(TAIL_PORT, optional<pair<string, int>>{});
        pair<string, int> tail_addr("localhost", TAIL_PORT);
        head_server = new MockReplicatedServer(HEAD_PORT, optional<pair<string, int>>{tail_addr});

        Request::RedisRequest* set_r = new Request::RedisRequest;
        set_r->set_client_addr(CLIENT_ADDR);
        set_r->set_client_port(CLIENT_PORT);
        set_r->set_cmd("set");
        set_r->set_key("k1");
        set_r->set_val("v1");

        Request::RedisRequest* get_r = new Request::RedisRequest;
        get_r->set_client_addr(CLIENT_ADDR);
        get_r->set_client_port(CLIENT_PORT);
        get_r->set_cmd("get");
        get_r->set_key("k1");

        Request r;
        r.set_type(Request::REDIS);
        r.set_allocated_redis(set_r);
        r.SerializeToString(&set_request);

        r.set_allocated_redis(get_r);
        r.SerializeToString(&get_request);

        reply.set_key("k1");
    }

    virtual void TearDown() {
        delete tail_server;
        delete head_server;
    }
    MockReplicatedServer* tail_server;
    MockReplicatedServer* head_server;
    Reply reply;
};

string ReplicatedServerTest::get_request;
string ReplicatedServerTest::set_request;

TEST_F(ReplicatedServerTest, tail_handle_request) {
    // Sends set msg to tail server. Verifies we can obtain the value right after
    string reply_str;
    reply.set_response("OK");
    reply.SerializeToString(&reply_str);
    EXPECT_CALL(*tail_server, send_msg(CLIENT_FD, reply_str)).Times(1);

    reply.set_response("v1");
    reply.SerializeToString(&reply_str);
    EXPECT_CALL(*tail_server, send_msg(CLIENT_FD, reply_str)).Times(1);

    EXPECT_CALL(*tail_server, get_client_fd(CLIENT_ADDR, CLIENT_PORT)).Times(2).WillRepeatedly(Return(CLIENT_FD));

    tail_server->handle_request(ReplicatedServerTest::set_request); //set k1 v1
    tail_server->handle_request(ReplicatedServerTest::get_request); //get k1
}

TEST_F(ReplicatedServerTest, modify_tail_server) {
    tail_server->update_next_server(make_pair("localhost", TAIL_PORT+1));
    EXPECT_CALL(*tail_server, send_msg(CLIENT_FD, "OK")).Times(0);
    EXPECT_CALL(*tail_server, send_msg(tail_server->next_server_fd_, ReplicatedServerTest::set_request)).Times(1);

    tail_server->handle_request(ReplicatedServerTest::set_request);
}

TEST_F(ReplicatedServerTest, head_handle_request) {
    // Sends a set messsage to the head server
    EXPECT_CALL(*head_server, send_msg(head_server->next_server_fd_, ReplicatedServerTest::set_request)).Times(1);
    head_server->handle_request(ReplicatedServerTest::set_request); //set k1 v1
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
