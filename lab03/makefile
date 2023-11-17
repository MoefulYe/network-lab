all: server client

server: src/server.c
	@clang -o target/server src/server.c -W

client: src/client.c
	@clang -o target/client src/client.c -W
