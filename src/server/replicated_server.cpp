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
    cpp_redis::client redis_client_;
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
    max_fd_ = server_fd_;
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
    FD_ZERO(&readfds_);
    // Add server socket to set
    FD_SET(server_fd_, &readfds_);

    while (true) {
        int ready_fd = select( max_fd_ + 1 , &readfds_, NULL , NULL , NULL);
        if (FD_ISSET(server_fd_, &readfds_)) {
            //set up client structure
            int client_fd;
            struct sockaddr_in client_addr;
            socklen_t clientlen = sizeof(client_addr);

            // Handle incoming connection request
            client_fd = accept(server_fd_, (struct sockaddr *)&client_addr, &clientlen);
            client_fds_.push_back(client_fd);
        } else {
            // Hanlde client request
            // Better way than loooping through all connections?
            for (const auto client_fd: client_fds_) {
                if (FD_ISSET(client_fd, &readfds_)) {
                    handle_request(client_fd);
                }
            }
        }
    }
}

string
ReplicatedServer::send_redis_cmd(string request) {
    vector<string> redis_args;
    parse_client_request(request, redis_args);
    redis_client_.send(redis_args, [&](cpp_redis::reply& reply) {
        cout<<reply;
    });
    redis_client_.sync_commit();
    return "success";
}

void
ReplicatedServer::handle_request(int client_fd) {
    /*
     * Receives the client request
     * Establishes connection with the redis server
     * Sends it to the local redis server
     * Send client back the message from the redis server
     */
    string request = recv_msg(client_fd);
    string reply = send_redis_cmd(request);
    send_msg(client_fd, reply);
}

string
ReplicatedServer::recv_msg(int fd) {
    //Reads and returns the request from the client. Handles protocol
    string msg = "";
    char* buf = new char[MAX_VAL_SIZE];
    while (msg.length() == 0 or msg[msg.length()-1] != '\n') {
        int nread = read(fd, (void *) buf, MAX_VAL_SIZE);
        msg.append(buf, nread);
    }
    return msg;
}

void
ReplicatedServer::send_msg(int fd, string msg) {
    //Sends the msg through the socket. Handles the protocol
    msg += "\n";
}
