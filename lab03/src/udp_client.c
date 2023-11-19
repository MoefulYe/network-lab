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
  socklen_t server_len;
  assert((conn_fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0);
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8081);
  assert((inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) >= 0));
  char *buf = malloc(256);
  size_t len;
  len = getline(&buf, &len, stdin);
  assert(sendto(conn_fd, buf, len, 0, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == len);
  char recv_buf[256];
  bzero(recv_buf, 256);
  assert(recvfrom(conn_fd, buf, 256, 0, (struct sockaddr *)&server_addr,
                  &server_len) == len);
  printf("recv: %s", buf);
  close(conn_fd);
  return 0;
}
