from client import Client
import sys

assert len(sys.argv) == 3, "Must provide head port and tail port of replicated server. \
                        Your arguments are {}".format(str(sys.argv))

head_port = int(sys.argv[1])
tail_port = int(sys.argv[2])

def check_value(c, key, val):
    redis_val = c.command("get {}".format(key))
    assert val == redis_val

def set_value(c, key, val):
    c.command("set {} {}".format(key, val))

c = Client()
c.set_obj_servers("test_key", ("localhost", head_port), ("localhost", tail_port))

# Simple Test
set_value(c, "test_key", "v1")
check_value(c, "test_key", "v1")
set_value(c, "test_key", "v2")
check_value(c, "test_key", "v2")
