#include "main.h"
#include "tcp.h"
#include "common.h"
#include "http.h"

int main() {

	tcp_server server = {0};
	int client_fd = -1;

	http_request request = {0};
	char* raw_request = NULL;

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

	debug_log("Client connected!!\n");
	
	if (read_raw_request(client_fd, &raw_request) == RECV_ERROR) {
		debug_log("Failed to read http request");

		close(server.socket_fd);
		close(client_fd);

		exit(EXIT_FAILURE);
	}



	printf("%s", raw_request);
	
	
	if (parse_http_request(raw_request, &request) != HTTP_OK) {
		debug_log("Failed to parse http request");

		close(server.socket_fd);
		close(client_fd);

		exit(EXIT_FAILURE);
	}
	

	printf("%s, %s, %s\n", request.method, request.path, request.version);
	printf("------------------------\n%s\n-----------------------", request.headers);
	printf("%s\n", request.body);

	

	free(raw_request);
	raw_request == NULL;

	close(client_fd);
	close(server.socket_fd);

	return 0;
}