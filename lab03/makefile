all: tcp-server tcp-client udp-server udp-client

tcp-server: src/tcp_server.c
	@clang -o target/tcp-server src/tcp_server.c -W

tcp-client: src/tcp_client.c
	@clang -o target/tcp-client src/tcp_client.c -W

udp-server: src/udp_server.c
	@clang -o target/udp-server src/udp_server.c -W

udp-client: src/udp_client.c
	@clang -o target/udp-client src/udp_client.c -W
