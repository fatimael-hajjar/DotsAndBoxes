#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>

#define PORT 8080

typedef struct {
	int r1, c1, r2, c2;
} GamePacket;

int setupServer();
int connectToServer(const char *ip);

#endif
