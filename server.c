#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// needed for server stuff
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
// file reading utility
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define CLIENT_NUM (5)  // 1 client

char* read_file(const char* file_name);
void exit_fn();

int main() {
  atexit(exit_fn);

  // HTML file
  char* content;
  // TODO accept file name
  if ((content = read_file("./index.html")) == NULL) {
    printf("Error handling file.");
    exit(EXIT_FAILURE);
  }

  char* header = "HTTP/1.1 200 OK\r\n\n";
  int response_len = strlen(content) + strlen(header);
  char response[response_len];
  strcpy(response, header);
  strcat(response, content);

  // meet sock the socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // this defines our address (TODO accept address)
  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = INADDR_ANY,
      .sin_port = htons(3000),
  };
  // bind the two
  bind(sock, (struct sockaddr*)&addr, sizeof(addr));
  listen(sock, CLIENT_NUM);

  int sock_client;  // sock but this time it's a client socket

  while (1) {
    // Dobby is a free elf!
    sock_client = accept(sock, NULL, NULL);
    send(sock_client, response, sizeof(response), 0);
    close(sock_client);
  }

  return 0;
}

void exit_fn() { printf("\n\nServer closed."); }

// utility functions
char* read_file(const char* file_name) {
  char* dest;
  int f = open(file_name, O_RDONLY);
  if (f == -1) return NULL;

  struct stat sb;
  if (fstat(f, &sb) == -1) return NULL;
  dest = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f, 0);
  if (dest == MAP_FAILED) return NULL;
  return dest;
}

/*
 * NOTES *
note to self uhh, AF_INET6 is for _IPv6_ stuff
 */