#include <stdio.h>
#include "socket.h"

int main(int argc, char *argv[]) {
	cresty_socket *socket = cresty_socket_create();
	if (cresty_socket_init(socket) == 0) {
		printf("Socket initialized: %d\n", socket->fd);
	} else {
		printf("Error initializing socket.\n");
	}
	cresty_socket_destroy(socket);
	return 0;
}
