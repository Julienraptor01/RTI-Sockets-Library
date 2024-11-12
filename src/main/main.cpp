#include <stdio.h>
#include <string.h>

#include "socketTCP.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <client/server>\n", argv[0]);
	}
	if (strcmp(argv[1], "server") == 0) {
		int serverSocket = createServerSocket(6942);
		if (serverSocket < 0) {
			printf("Failed to create server socket\n");
			return 1;
		}
		ipv4Address clientIP;
		int clientSocket = acceptClient(serverSocket, &clientIP);
		if (clientSocket < 0) {
			printf("Failed to accept client connection\n");
			return 1;
		}
		char clientIPString[16];
		ipv4AddressToString(clientIP, clientIPString);
		printf("Accepted connection from %s\n", clientIPString);
		uint8_t data[256];
		ssize_t received = receive(clientSocket, data, sizeof(data));
		if (received < 0) {
			printf("Failed to receive data\n");
			return 1;
		}
		printf("Received %zd bytes: ", received);
		for (ssize_t i = 0; i < received; i++) {
			printf("%02x ", data[i]);
		}
		printf("\n");
	} else if (strcmp(argv[1], "client") == 0) {
		ipv4Address serverIP = {.bytes = {127, 0, 0, 1}};
		int clientSocket = createClientSocket(serverIP, 6942);
		if (clientSocket < 0) {
			printf("Failed to create client socket\n");
			return 1;
		}
		uint8_t data[] = {0xde, 0xad, 0xbe, 0xef};
		ssize_t sent = send(clientSocket, data, sizeof(data));
		if (sent < 0) {
			printf("Failed to send data\n");
			return 1;
		}
		printf("Sent %zd bytes:", sent);
		for (ssize_t i = 0; i < sent; i++) {
			printf(" %02x", data[i]);
		}
		printf("\n");
	}
}
