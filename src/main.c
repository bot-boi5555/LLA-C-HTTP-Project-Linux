#include "main.h"
#include "tcp.h"
#include "common.h"

int main() {

	tcp_server server = {0};
	int client_fd = -1;

	if (bind_tcp_port(&server, PORT) != SERVER_OK) {
		debug_log("Server initialization failed");

		exit(EXIT_FAILURE);
	}

	printf("Server listening on port: %d\n", PORT);

	client_fd = accept_client(server.socket_fd);

	if (client_fd == (int) SERVER_ACCEPT_ERROR) {
		debug_log("Failed to accept client connection");

		close(server.socket_fd);
		exit(EXIT_FAILURE);
	}

	debug_log("Client connected!!");


	close(client_fd);
	close(server.socket_fd);

	return 0;
}