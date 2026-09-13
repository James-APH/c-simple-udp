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
  // Declaring Variables:
  const char *message = "Hello Server";
  AddressInfo address_info;
  struct sockaddr client_address;
  ssize_t status = -1;
  int client_socket = -1;

  // Creating client socket
  if ((client_socket = socket(AF_INET, SOCK_DGRAM, NO_FLAGS)) == -1) {
    printf("Error, failed at creating socket");
    exit(EXIT_FAILURE);
  }

  // Creating client address
  address_info._sockaddr_in = (struct sockaddr_in){
      .sin_family = AF_INET,
      .sin_port = htons(PORT_NUMBER),
      .sin_addr.s_addr = inet_addr("127.0.0.1"),
  };
  client_address = address_info._sockaddr;

  // Sending message to the server
  if ((status = sendto(client_socket, message, strlen(message), NO_FLAGS,
                       &client_address, sizeof(client_address))) == -1) {
    printf("Error, failed to send message");
    close(client_socket);
    exit(EXIT_FAILURE);
  }

  // Closing the client socket and returning success
  close(client_socket);
  return EXIT_SUCCESS;
}
