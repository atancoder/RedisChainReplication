"""
Reads commands from stdin and sends each to the appropriate HEAD server
Outputs replies from the Chain Replicated Servers.


Requires state:
    - ObjID -> HEAD server and TAIL server
    - Established conenction with master

When receiving a command:
    - Determine whether or not it's an update or a get request
    - Extract the obj and find the appropriate server
        - If obj doesn't exist in cache, ask the master for it
            - Store result given my master in the cache
    - Send the full command to the appropriate server
    - Print out the reply from the server

Be on the lookout from master: (Future)
    - Master will inform clients if a server ever gets updated
    - Client should update their cache accordingly
"""

master_ip = "localhost:1989"
redis_command = input()
obj_to_server = {}
while (redis_command):
    command, args = redis_command.split(" ")
    obj = args[1]
    if obj in obj_to_server:
        
