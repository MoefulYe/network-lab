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

void *handler(void *_fd) {
  int fd = (int)_fd;
  char buf[256];
  int n;
  while (1) {
    bzero(buf, sizeof(buf));
    if (read(fd, buf, sizeof(buf)) == 0) {
      printf("client close\n");
      break;
    }
    printf("recv: %s", buf);
    int to_send = strlen(buf);
    if (write(fd, buf, to_send) != to_send) {
      printf("write error\n");
      break;
    }
  }
  close(fd);
  return NULL;
}

int main(int argc, char *argv[]) {
  int listen_fd, conn_fd, n;
  struct sockaddr_in server_addr, client_addr;
  // 创建监听fd
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    exit(0);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(8081);

  if ((bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) <
      0) {
    exit(0);
  }

  if (listen(listen_fd, 10) < 0) {
    exit(0);
  }

  while (1) {
    socklen_t client_len = sizeof(client_addr);
    if ((conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                          &client_len)) < 0) {
      break;
    } else {
      pthread_t t;
      if (pthread_create(&t, NULL, handler, (void *)conn_fd) < 0) {
        break;
      }
    }
  }
  close(listen_fd);
  return 0;
}
