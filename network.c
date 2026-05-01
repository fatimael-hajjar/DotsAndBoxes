#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int setupServer() {
	int serverfd, newsocket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	bind(serverfd, (struct sockaddr *)&address, sizeof(address));
	listen(serverfd, 3);

	printf("Waiting for Player B to connect...\n");
	newsocket = accept(serverfd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	printf("Player B connected\n");
	return newsocket;
}

int connectToServer(const char *ip) {
	int sock = 0;
	struct sockaddr_in serv_addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	inet_pton(AF_INET, ip, &serv_addr.sin_addr);
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	printf("Connected to Player A\n");
	return sock;
}
