#include "http.h"
#include <string.h>


int read_raw_request(int cleint_fd, char** raw_request) {

	int bytes_read = 0;

	if (raw_request == NULL) {
		printf("Invalid request char pointer: read_raw_request\n");

		return RECV_ERROR;
	}


	*raw_request = malloc(HTTP_REQUEST_MAX_LEN);
    

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
	
	size_t request_len = 0;
	size_t req_line_len = 0;
	size_t headers_len = 0;
	

	char* headers_start = NULL;
	char* headers_end = NULL;	

	
	if (raw_request == NULL) {
		printf("raw_request pointer is null: parse_http_request\n");

		return HTTP_BAD_REQUEST;
	}
	
	request_len = strlen(raw_request);
	
	
	if (sscanf(raw_request, "%15s %255s %15s", request->method, request->path, request->version) != 3) {
		printf("Invalid request line\n");

		return HTTP_BAD_REQUEST;
	}


	
	if (strncmp(request->method, "GET", sizeof(request->method)) != 0) {
		printf("HTTP method not implemented\n");

		return HTTP_NOT_IMPLEMENTED;
	}

	if (strncmp(request->version, "HTTP/1.1", sizeof(request->version)) != 0) {
		printf("HTTP version not supported\n");

		return HTTP_VERSION_NOT_SUPPORTED;
	}


	headers_start = strstr(raw_request, "\r\n");

	if (headers_start == NULL) {
		return HTTP_OK;
	}

	headers_start += 2;

	headers_end = strstr(raw_request, "\r\n\r\n");

	if (headers_end == NULL) {
		printf("Invalid header format\n");

		return HTTP_BAD_REQUEST;
	}

	headers_len = headers_end - headers_start;
	
	if (headers_len >= HTTP_HEADER_MAX_LEN) {
		printf("headers too large\n");

		return HTTP_BAD_REQUEST;
	}

	printf("%s\n", headers_start);


	strncpy(request->headers, headers_start, headers_len);

	// if there is no body (ie the sizeof req line and headers == request length)
	if (request_len == req_line_len + headers_len) {
		return HTTP_OK;
	}

	strncpy(request->body, headers_end, sizeof(request->body) - 1);


	
	return HTTP_OK;
}