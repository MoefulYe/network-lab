#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int conn_fd;
  struct sockaddr_in server_addr;
  if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    exit(0);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8081);
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) < 0) {
    exit(0);
  }

  if (connect(conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    exit(0);
  }

  char *buf = malloc(256);
  size_t len;
  len = getline(&buf, &len, stdin);
  if (write(conn_fd, buf, len) != len) {
    exit(0);
  }
  bzero(buf, len);
  char recv_buf[256];
  bzero(recv_buf, 256);
  if (read(conn_fd, recv_buf, 256) != len) {
    exit(0);
  }
  printf("recv: %s", recv_buf);
  close(conn_fd);
  return 0;
}
