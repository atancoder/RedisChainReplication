#include "replicated_server.h"
#include "gtest/gtest.h"

class ReplicatedServerTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        s = new ReplicatedServer(1337, optional<pair<string, int>>{}, optional<pair<string, int>>{});
    }

    virtual void TearDown() {
        delete s;
    }
    ReplicatedServer* s;
};

TEST_F(ReplicatedServerTest, send_msg) {
    EXPECT_EQ(1, 1);
}

/* Deprecated Tests
TEST(ParseTest, get_request) {
    vector<string> redis_args;
    string request = "GET K1";
    parse_client_request(request, redis_args);
    EXPECT_EQ(2, redis_args.size());
    EXPECT_EQ("GET", redis_args[0]);
    EXPECT_EQ("K1", redis_args[1]);
}

TEST(ParseTest, set_request) {
    vector<string> redis_args;
    string request = "SET K1 V1";
    parse_client_request(request, redis_args);
    EXPECT_EQ(3, redis_args.size());
    EXPECT_EQ("SET", redis_args[0]);
    EXPECT_EQ("K1", redis_args[1]);
    EXPECT_EQ("V1", redis_args[2]);
}
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
