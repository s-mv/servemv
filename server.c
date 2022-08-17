#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  // meet sock, the socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // this is the address
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_port = htons(3000),
      .sin_addr.s_addr = INADDR_ANY,
  };
  // connect and get the status back
  int status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
  if (status == -1) {
    printf("Connection error!\n");  // oof
    exit(EXIT_FAILURE);
  }
  char response[256];  // just a big char array to get response

  // "recieve"
  // no flags because I have 0 knowledge about this
  recv(sock, &response, sizeof(response), 0);
  printf("Data: %s\n", response);
  close(sock);
  return 0;
}

/*
 * NOTES *
note to self uhh, AF_INET6 is for _IPv6_ stuff
 */