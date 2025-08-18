#include "tcp.h"
#include "main.h"
#include "common.h"

server_status_e bind_tcp_port(tcp_server* server, int port) {

	int sockopt = 1;

	if (server == NULL) {
		printf("tcp_server pointer is null: bind_tcp_port\n");

		return SERVER_SOCKET_ERROR;
	}

	if (port < 0 || port > INT16_MAX) {
		printf("invalid port value\n");

		return SERVER_SOCKET_ERROR;
	}

	memset(server, 0, sizeof(tcp_server));

	server->address.sin_family = AF_INET;
	server->address.sin_addr.s_addr = INADDR_ANY;
	server->address.sin_port = htons(port);

	server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server->socket_fd == SOCKET_ERROR) {
		perror("socket");

		return SERVER_SOCKET_ERROR;
	}

	if (setsockopt(server->socket_fd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt)) == SOCKET_ERROR) {
		perror("setsockopt");
		close(server->socket_fd);

		return SERVER_SOCKET_ERROR;
	}

	if (bind(server->socket_fd, (struct sockaddr*) &server->address, sizeof(server->address)) <= SOCKET_ERROR) {
		perror("bind");
		close(server->socket_fd);

		return SERVER_BIND_ERROR;
	}

	if (listen(server->socket_fd, BACKLOG) == SOCKET_ERROR) {
		perror("listen");
		close(server->socket_fd);

		return SERVER_LISTEN_ERROR;
	}



	return SERVER_OK;
}


int accept_client(int server_fd) {
	
	int client_fd = 0;
	struct sockaddr_in client_address = {0};
	socklen_t client_size = sizeof(client_address);

	client_fd = accept(server_fd, (struct sockaddr*) &client_address, &client_size);

	if (client_fd == SOCKET_ERROR) {
		perror("accept");

		return (int) SERVER_ACCEPT_ERROR;
	}

	return client_fd;
}
