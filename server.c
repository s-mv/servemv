#include <stdio.h>
#include <stdlib.h>
// needed for server stuff
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CLIENT_NUM (1)  // 1 client

int main() {
  char message[256] = "Hello, world.";
  // meet server sock, the server socket
  int server_sock = socket(AF_INET, SOCK_STREAM, 0);
  // server address
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = inet_addr("127.0.0.1"),
      .sin_port = htons(3000),
  };
  // woo BIND to port and stuff
  bind(server_sock, (struct sockaddr *)&addr, sizeof(addr));
  listen(server_sock, CLIENT_NUM);
  // client sock is a free elf
  int client_sock = accept(server_sock, NULL, NULL);
  // then send
  send(client_sock, message, sizeof(message), 0);  // yay
  close(server_sock);

  return 0;
}

/*
 * NOTES *
note to self uhh, AF_INET6 is for _IPv6_ stuff
 */