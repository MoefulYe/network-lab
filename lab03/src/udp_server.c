#include <assert.h>
#include <errno.h>
#include <fcntl.h>
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

int init() {
  int fd, n;
  struct sockaddr_in server_addr;
  assert((fd = socket(AF_INET, SOCK_DGRAM, 0)) != -1);
  int on = 1;
  assert(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != -1);
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(8081);
  assert((bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) !=
         -1);
  return fd;
}

int main(int argc, char *argv[]) {
  int fd = init();
  struct sockaddr_in client_addr;
  socklen_t socket_len = sizeof(client_addr);
  memset(&client_addr, 0, sizeof(client_addr));
  char buf[4096];
  while (1) {
    bzero(buf, sizeof(buf));
    int recv_len;
    assert(
        (recv_len = recvfrom(fd, buf, 4096, 0, (struct sockaddr *)&client_addr,
                             &socket_len)) != -1);
    printf("recv: %s", buf);
    assert(sendto(fd, buf, recv_len, 0, (struct sockaddr *)&client_addr,
                  sizeof(client_addr)) != -1);
  }
  close(fd);
  return 0;
}
