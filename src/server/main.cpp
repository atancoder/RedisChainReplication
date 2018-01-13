#include "replicated_server.h"

int main(int argc, char** argv)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    if (argc < 2) {
        cout << "Must enter 1 argument: Server Port" << endl;
    }
    char *p;
    int port = strtol(argv[1], &p, 10);
    if (*p) {
      cout << "Invalid port number. Please enter a number" << endl;
    } else {
        ReplicatedServer s (port);
        cout << "Running replicated server on port: " << to_string(port) << endl;
        s.run();
    }
    return 0;
}
