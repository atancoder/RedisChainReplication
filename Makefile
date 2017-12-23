CFLAGS=-std=c++11

.PHONY: all # PHONY just in case there's a "all" file/directory
# PHONYing all doesn't PHONY its dependencies
all: replicated_server

.PHONY: replicated_server
replicated_server:
	g++ $(CFLAGS) replicated_server.cpp -o replicated_server

clean:
	rm replicated_server
