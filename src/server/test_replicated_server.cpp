#include "replicated_server.h"
#include "mock_replicated_server.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class ReplicatedServerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        s = new ReplicatedServer(1337, optional<pair<string, int>>{});
    }

    virtual void TearDown() {
        delete s;
    }
    ReplicatedServer* s;
};

TEST_F(ReplicatedServerTest, send_msg) {
    EXPECT_EQ(1, 1);
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
