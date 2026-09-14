#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum {
  PORT_NUMBER = 8080,
  BUFFER_SIZE = 512,
  NO_FLAGS = 0,
};

typedef union AddressInfo {
  struct sockaddr_in _sockaddr_in;
  struct sockaddr _sockaddr;
} AddressInfo;

int main() {
  // Declaring variables
  char response[BUFFER_SIZE];
  ssize_t status = -1;
  AddressInfo address_info;
  socklen_t len = 0;
  int server_socket = -1;

  // Creating server socket
  if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    printf("Error, failed to create server socket");
    exit(EXIT_FAILURE);
  }

  // creating server address
  address_info._sockaddr_in = (struct sockaddr_in){
      .sin_family = AF_INET,
      .sin_port = htons(PORT_NUMBER),
      .sin_addr.s_addr = htonl(INADDR_ANY),
  };

  // Binding server socket to server address
  if ((status = bind(server_socket, &address_info._sockaddr,
                     sizeof(address_info._sockaddr))) < 0) {
    printf("Error, failed to bind socket.");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  // Receiving message from client
  if ((status = recvfrom(server_socket, response, BUFFER_SIZE, MSG_WAITALL, 0,
                         &len)) == -1) {
    printf("Error, failed to receive message");
    close(server_socket);
    exit(EXIT_FAILURE);
  }
  response[strlen(response)] = '\0';
  printf("%s", response);

  // Close server socket and return success
  close(server_socket);
  return EXIT_SUCCESS;
}
