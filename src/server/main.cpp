#include "replicated_server.h"

#define PORT 1337
int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    ReplicatedServer s (PORT, optional<pair<string, int>>{}, optional<pair<string, int>>{});
    s.run();
    return 0;
}
