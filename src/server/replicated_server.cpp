#include "replicated_server.h"

ReplicatedServer::ReplicatedServer(int port, optional<pair<string, int>> next_server): Server(port) {
    has_prev_server_ = false;
    next_server_fd_ = -1;
    if (next_server) {
      cout << "Not yet implemented\n";
    }
    redis_client_.connect();
}

bool ReplicatedServer::is_tail_server() {
    return next_server_fd_ == -1;
}

void ReplicatedServer::update_prev_server_existance(bool has_prev_server) {
    has_prev_server_ = has_prev_server;
}

string
ReplicatedServer::send_redis_cmd(Request request) {
    vector<string> redis_args = {request.cmd(), request.key()};
    if (request.has_val()) {
        redis_args.push_back(request.val());
    }
    string response;
    cout << "Sending redis cmd: " << redis_args[0] << " " << redis_args[1] << endl;
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
    string request_str = "";
    bool success = recv_msg(client_fd, request_str);
    if (success) {
        //Convert request to protobuf object
        Request request;
        if (request.ParseFromString(request_str)) {
            string reply = send_redis_cmd(request);
            if (is_tail_server()) {
                send_msg(client_fd, reply);
            } else {
                // Send the request to the next server. Make sure to pass the original client's address. Good time to use Protobuf
                send_msg(next_server_fd_, request_str);
            }
        } else {
            cout << "Invalid request format\n";
        }
    }
}

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
