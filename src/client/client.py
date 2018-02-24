import socket
import json
import RepServer_client_pb2

MAX_VAL_SIZE = 1024
MASTER_ADDR = ('localhost', 1338)
class Client:
    def __init__(self):
        self.objID_to_addr = {}
        self.addr_to_socket = {} # Maps addr to socket (if exists)
        self.max_val_size = MAX_VAL_SIZE
        self.master_addr = MASTER_ADDR
        self.master_socket = socket.socket()

        # To Do:
        #self.connect_to_master()

    def connect_to_master(self):
        self.master_socket.connect(self.master_addr)

    def set_obj_servers(self, obj, head_server, tail_server):
        self.objID_to_addr[obj] = (head_server, tail_server)

    def get_servers(self, obj):
        """
        Checks if obj is in local state
        Otherwise, asks master for the HEAD/TAIL server associated with the objID
        Return HEAD server, TAIL server
        """
        if not obj in self.objID_to_addr:
            """
            request = obj
            self.send_request(request,client_socket=self.master_socket)
            reply = self.get_reply(client_socket=self.master_socket)
            reply = json.loads(reply)
            head_addr = tuple(i for i in reply['HEAD'])
            tail_addr = tuple(i for i in reply['TAIL'])
            self.objID_to_addr[obj] = (head_addr, tail_addr)
            """
            raise Exception("Not Yet Implemented")
        return self.objID_to_addr[obj]

    def background_check_for_master_update(self):
        """
        Have a threat listen in the background for any updates from the master
        """

    def send_request(self, request, client_socket):
        """
        Sends request to server over tcp
        Protocol is to send len of message + space + message
        """
        request = str(len(request)) + ' ' + request
        client_socket.sendall(request.encode())

    def get_reply(self, client_socket):
        reply = client_socket.recv(self.max_val_size).decode()
        separator = reply.find(' ')
        msg_len = int(reply[:separator])
        reply = reply[separator+1:]
        while len(reply) < msg_len:
            reply += client_socket.recv(msg_len - len(reply)).decode()
        return reply

    def command(self, string_command):
        """
        Sends the string command to the appropriate server (HEAD or TAIL)
        Listens on the TAIL server for reply
        """
        command_args = string_command.split(' ')
        action = command_args[0].upper()
        obj = command_args[1]
        val = None
        if len(command_args) > 2:
            val = command_args[2]

        HEAD_server, TAIL_server = self.get_servers(obj)

        if not TAIL_server in self.addr_to_socket:
            self.addr_to_socket[TAIL_server] = socket.socket()
            self.addr_to_socket[TAIL_server].connect(TAIL_server)
        tail_socket = self.addr_to_socket[TAIL_server]

        # Send request
        # Set client_address
        client_addr = RepServer_client_pb2.Request.Address()
        client_host, client_port = tail_socket.getsockname()
        client_addr.host, client_addr.port = client_host, client_port

        # Setup RedisRequest
        redis_request = RepServer_client_pb2.RedisRequest()
        redis_request.client_addr = client_addr
        redis_request.cmd = action
        redis_request.key = obj
        if val:
            redis_request.val = val

        request = RepServer_client_pb2.Request()
        request.type = RepServer_client_pb2.Request.REDIS
        request.redis = redis_request
        request_str = SerializeToString(request)

        if action == "GET":
            self.send_request(request_str, tail_socket)
        elif action == "SET":
            if not HEAD_server in self.addr_to_socket:
                self.addr_to_socket[HEAD_server] = socket.socket()
                self.addr_to_socket[HEAD_server].connect(HEAD_server)
            head_socket = self.addr_to_socket[HEAD_server]
            self.send_request(request_str, head_socket)

        # Listen to TAIL for reply
        reply = self.get_reply(tail_socket)
        return reply

if __name__ == '__main__':
    c = Client()
    redis_command = input(">> ")
    while (redis_command):
        print(c.command(redis_command))
        redis_command = input(">> ")
