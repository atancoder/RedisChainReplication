#include "replicated_server.h"

#define PORT 1337
int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    ReplicatedServer s (PORT);
    s.run();
    return 0;
}
