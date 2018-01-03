#include "replicated_server.h"

void
parse_client_request(string request, vector<string>& redis_args) {
    // modifies redis_args destructively by taking a reference variable
    size_t start = 0;
    size_t next = 0;
    while ((next = request.find(" ", start)) != std::string::npos) {
        redis_args.push_back(request.substr(start, next-start));
        start = next + 1;
    }
    // Add tail
    redis_args.push_back(request.substr(start));
}

ReplicatedServer::ReplicatedServer(int port, optional<pair<string, int>> prev_server, optional<pair<string, int>> next_server) {
    port_ = port;
    prev_server_ = prev_server;
    next_server_ = next_server;
}

void
ReplicatedServer::run() {
    create();
    connect_to_redis();
    serve();
}
void ReplicatedServer::connect_to_redis() {
    redis_client_.connect();
    cout << "Connected to redis server!\n";
}

void
ReplicatedServer::create() {
    struct sockaddr_in server_addr;

    // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // create socket
    server_fd_ = socket(PF_INET,SOCK_STREAM,0);
    if (!server_fd_) {
        perror("socket");
        exit(-1);
    }

    // set socket to immediately reuse port when the application closes
    int reuse = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with our local address and
    // port
    if (bind(server_fd_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

    // convert the socket to listen for incoming connections
    if (listen(server_fd_,SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }
}

void
ReplicatedServer::serve() {
    while (true) {
        FD_ZERO(&readfds_);
        // Add server socket to set
        FD_SET(server_fd_, &readfds_);
        for (const auto client_fd: client_fds_) {
            FD_SET(client_fd, &readfds_);
        }
        int ready_fd = select( FD_SETSIZE , &readfds_, NULL , NULL , NULL);
        // select removes fds that aren't ready for reading from readfds_
        if (FD_ISSET(server_fd_, &readfds_)) {
            //set up client structure
            int client_fd;
            struct sockaddr_in client_addr;
            socklen_t clientlen = sizeof(client_addr);

            // Handle incoming connection request
            client_fd = accept(server_fd_, (struct sockaddr *)&client_addr, &clientlen);
            client_fds_.insert(client_fd);
            cout << "Connected to a client!" << endl;
        }
        // Handle client request
        for (const auto client_fd: client_fds_) {
            if (FD_ISSET(client_fd, &readfds_)) {
                handle_request(client_fd);
            }
        }
    }
}

string
ReplicatedServer::send_redis_cmd(string request) {
    vector<string> redis_args;
    parse_client_request(request, redis_args);
    string response;
    redis_client_.send(redis_args, [&](cpp_redis::reply& reply) {
        response = reply.as_string();
    });
    redis_client_.sync_commit();
    return response;
}

void
ReplicatedServer::handle_request(int client_fd) {
    /*
     * Receives the client request
     * Establishes connection with the redis server
     * Sends it to the local redis server
     * Send client back the message from the redis server
     */
    cout << "Handling client request\n";
    string request = "";
    bool success = recv_msg(client_fd, request);
    if (success) {
        string reply = send_redis_cmd(request);
        send_msg(client_fd, reply);
    } else {
        // remove client
        // Should we unset the bit?
        close(client_fd);
        client_fds_.erase(client_fd);
    }
}

bool
ReplicatedServer::recv_msg(int fd, string& msg) {
    //Reads and returns the request from the client. Handles protocol
    char* buf = new char[MAX_VAL_SIZE]; // Heap memory
    int nread = read(fd, (void *) buf, MAX_VAL_SIZE);
    if (nread == 0) {
        // The other side closed their socket
        delete buf;
        return false;
    }
    msg.append(buf, nread);
    int separator = msg.find(" ");
    int msg_len = stoi(msg.substr(0, separator));
    msg = msg.substr(separator+1);

    while (msg.length() < msg_len) {
        nread = read(fd, (void *) buf, msg_len - msg.length());
        msg.append(buf, nread);
    }
    delete buf;
    return true;
}

void
ReplicatedServer::send_msg(int fd, string msg) {
    //Sends the msg through the socket. Handles the protocol
    msg = to_string(msg.length()) + " " + msg;
    const char* buf = msg.c_str(); // Stack memory
    int written = 0;
    while (written < msg.length()) {
        written += write(fd, buf, msg.length() - written);
        buf += written;
    }
}
