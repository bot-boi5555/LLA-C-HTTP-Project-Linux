#include "http.h"


int read_raw_request(int cleint_fd, char** raw_request) {

	int bytes_read = 0;

	if (raw_request == NULL) {
		printf("Invalid request char pointer: read_raw_request\n");

		return RECV_ERROR;
	}


	*raw_request = calloc(1, HTTP_REQUEST_MAX_LEN);
    

	if (*raw_request == NULL) {
		printf("Failed to allocate memory for raw_request: read_raw_request\n");
        
		return RECV_ERROR;
    }

	if (cleint_fd <= 0) {
		printf("Client fd is invalid: read_raw_request\n");

		return RECV_ERROR;
    }
    
	bytes_read = recv(cleint_fd, *raw_request, HTTP_REQUEST_MAX_LEN - 1, 0);

	if (bytes_read == RECV_ERROR) {
		printf("Failed to read data from client: read_raw_request\n");

		return RECV_ERROR;
    }

	(*raw_request)[bytes_read] = '\0';


	return RECV_SUCCESS;
}



http_status_e parse_http_request(const char* raw_request, http_request* request) {

	

}