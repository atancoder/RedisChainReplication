#include "server.h"

Server::Server(int port) {
    port_ = port;
}

void
Server::run() {
    create_server_socket();
    serve();
}

void
Server::create_server_socket() {
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
    if (::bind(server_fd_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
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
Server::serve() {
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

void
Server::handle_request(int client_fd) {
    cout << "Must be implemented by subclass\n";
}

bool
Server::recv_msg(int fd, string& msg) {
    //Reads and returns the request from the client. Handles protocol
    char* buf = new char[MAX_VAL_SIZE]; // Heap memory
    // We only need to read enough for the max length
    int nread = read(fd, (void *) buf, to_string(MAX_VAL_SIZE).length());
    if (nread == 0) {
        // The other side closed their socket
        close(fd);
        client_fds_.erase(fd);
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
Server::send_msg(int fd, string msg) {
    //Sends the msg through the socket. Handles the protocol
    msg = to_string(msg.length()) + " " + msg;
    const char* buf = msg.c_str(); // Stack memory
    int written = 0;
    while (written < msg.length()) {
        written += write(fd, buf, msg.length() - written);
        buf += written;
    }
}
