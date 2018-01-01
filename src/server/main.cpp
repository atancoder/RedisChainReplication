#include "replicated_server.h"

#define PORT 1337
int main()
{
    Request request;
    ReplicatedServer s (PORT, optional<pair<string, int>>{}, optional<pair<string, int>>{});
    s.run();
    return 0;
}
