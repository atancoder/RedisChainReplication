PORT=1290

all: clean redis replicated_server #test

redis:
# @ Means don't echo the command to the output
# Run in background and save PID
	@/Users/anthonytan/cs/redis/src/redis-server & echo $$! >> PIDS.log

replicated_server: redis
	../build_debug.sh
	@../build/src/server/main $(PORT) & echo $$! >> PIDS.log

test: replicated_server redis
	PYTHONPATH=../src/client python3 integration.py $(PORT) $(PORT)

clean:
# The - ignores errors
	-kill $$(cat PIDS.log)
	-rm PIDS.log

