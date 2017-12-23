from client import Client


def check_value(key, val):
    redis_val = c.command("get {}".format(key))
    assert val == redis_val

def set_value(key, val):
    c.command("set {} {}".format(key, val))

c = Client()

# Simple Test
set_value("k1", "v1")
set_value("k2", "v2")
check_value("k1", "v1")
check_value("k2", "v2")
set_value("k1", "v2")
check_value("k1", "v2")
check_value("k2", "v2")
