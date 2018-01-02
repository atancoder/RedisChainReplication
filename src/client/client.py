import socket
import json
MAX_VAL_SIZE = 1024
MASTER_ADDR = ('localhost', 1337)
class Client:
    def __init__(self):
        self.objID_servers = {"k1": (('localhost', 1337), ('localhost', 1337))} # Maps obj -> (Head server, Tail server) May be sockets
        self.max_val_size = MAX_VAL_SIZE
        self.master_addr = MASTER_ADDR
        #self.master_socket = socket.socket()
        #self.connect_to_master()

    def connect_to_master(self):
        self.master_socket.connect(self.master_addr)

    def get_servers(self, obj):
        """
        Checks if obj is in local state
        Otherwise, asks master for the HEAD/TAIL server associated with the objID
        Return HEAD server, TAIL server
        """
        if not obj in self.objID_servers:
            request = obj
            self.send_request(request,client_socket=self.master_socket)
            reply = self.wait_for_reply(client_socket=self.master_socket)
            reply = json.loads(reply)
            head_addr = tuple(i for i in reply['HEAD'])
            tail_addr = tuple(i for i in reply['TAIL'])
            self.objID_servers[obj] = (head_addr, tail_addr)
        return self.objID_servers[obj]

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

    def wait_for_reply(self, client_socket):
        reply = client_socket.recv(self.max_val_size).decode()
        separator = reply.find(' ')
        msg_len = int(reply[:separator])
        reply = reply[separator+1:]
        while len(reply) < msg_len:
            reply += client_socket.recv(msg_len - len(reply))
        return reply

    def command(self, string_command):
        """
        Sends the string command to the appropriate server (HEAD or TAIL)
        Listens on the TAIL server for reply
        """
        command_args = string_command.split(' ')
        action = command_args[0]
        obj = command_args[1]
        HEAD_server, TAIL_server = self.get_servers(obj)

        tail_socket = socket.socket()
        tail_socket.connect(TAIL_server)
        # Send request
        if action.lower() == "get":
            self.send_request(string_command, tail_socket)
        elif action.lower() == "set":
            if HEAD_server == TAIL_server:
                head_socket = tail_socket
            else:
                head_socket = socket.socket()
                head_socket.connect(HEAD_server)
            self.send_request(string_command, head_socket)

        # Listen to TAIL for reply
        reply = self.wait_for_reply(tail_socket)
        return reply

if __name__ == '__main__':
    c = Client()
    redis_command = input(">> ")
    while (redis_command):
        print(c.command(redis_command))
        redis_command = input(">> ")
