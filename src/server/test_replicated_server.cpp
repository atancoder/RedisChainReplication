#include "replicated_server.h"
#include "mock_replicated_server.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class ReplicatedServerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        tail_server = new MockReplicatedServer(1337, optional<pair<string, int>>{});
        pair<string, int> tail_addr("localhost", 1337);
        head_server = new MockReplicatedServer(1338, optional<pair<string, int>>{tail_addr});
    }

    virtual void TearDown() {
        delete tail_server;
        delete head_server;
    }
    MockReplicatedServer* tail_server;
    MockReplicatedServer* head_server;
};

bool mock_recv_msg_set(int fd, string& msg) {
    Request request;
    request.set_cmd("set");
    request.set_key("k1");
    request.set_val("v1");
    return request.SerializeToString(&msg);
}

bool mock_recv_msg_get(int fd, string& msg) {
    Request request;
    request.set_cmd("get");
    request.set_key("k1");
    return request.SerializeToString(&msg);
}

TEST_F(ReplicatedServerTest, tail_handle_request) {
    // Sends set msg to tail server
    EXPECT_CALL(*tail_server, recv_msg(::testing::_, ::testing::_)).WillOnce(testing::Invoke(mock_recv_msg_set)).WillOnce(testing::Invoke(mock_recv_msg_get)); // '_' means any argument
    EXPECT_CALL(*tail_server, send_redis_cmd(::testing::_)).Times(2).WillRepeatedly(testing::Invoke(tail_server,&MockReplicatedServer::do_redis_cmd));
    EXPECT_CALL(*tail_server, send_msg(3, "OK")).Times(1);
    EXPECT_CALL(*tail_server, send_msg(5, "v1")).Times(1);

    tail_server->handle_request(3); //set k1 v1
    tail_server->handle_request(5); //get k1
}

TEST_F(ReplicatedServerTest, head_handle_request) {
    EXPECT_CALL(*head_server, recv_msg(::testing::_, ::testing::_)).WillOnce(testing::Invoke(mock_recv_msg_set)); // '_' means any argument
    EXPECT_CALL(*head_server, send_redis_cmd(::testing::_)).Times(1).WillRepeatedly(testing::Invoke(head_server,&MockReplicatedServer::do_redis_cmd));
    EXPECT_CALL(*head_server, send_msg(3, "OK")).Times(1);
    //EXPECT_CALL(*head_server, send_msg(head_server->next_server_fd_, SET_REQUEST)).Times(1);

    head_server->handle_request(3); //set k1 v1
}

//Mock redis_client
/*
 * Tests to write:
 *
 * - Test head server get request: Should respond back to client w/o modifying state
 *   "              " set request: Should update locally and then forward to next server
 * - Test tail server get request: Should respond back to client w/o modifying state
 *   "              " set request: Should update locally and then respond back to client
 */

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
