#include "replicated_server.h"

int main()
{
    ReplicatedServer s (PORT, optional<pair<string, int>>{}, optional<pair<string, int>>{});
    s.run();
    return 0;
}
