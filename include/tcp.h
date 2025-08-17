#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define SOCKET_ERROR 	-1
#define BACKLOG			5


enum server_status_e {
	SERVER_OK,
	SERVER_SOCKET_ERROR,
	SERVER_BIND_ERROR,
	SERVER_LISTEN_ERROR,
	SERVER_ACCEPT_ERROR = SOCKET_ERROR
};


struct tcp_server_t {
	int socket_fd;
	struct sockaddr_in address;
};

typedef enum server_status_e server_status_e;
typedef struct tcp_server_t tcp_server;

server_status_e bind_tcp_port(tcp_server* server, unsigned short port);
int accept_client(int server_fd);

#endif