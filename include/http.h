#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <sys/socket.h>

#define HTTP_REQUEST_MAX_LEN 			INT16_MAX

#define HTTP_METHOD_MAX_LEN 			16
#define HTTP_PATH_MAX_LEN 				512
#define HTTP_VERSION_MAX_LEN 			16
#define HTTP_HEADER_MAX_LEN 			1024
#define HTTP_BODY_MAX_LEN 				4096
#define HTTP_HDR_KEY_MAX_LEN			256
#define HTTP_HDR_VAL_MAX_LEN			512

#define RECV_ERROR 						-1
#define RECV_SUCCESS 					0



enum http_status_e {
	HTTP_OK,                        	// 200
	HTTP_BAD_REQUEST,               	// 404
	HTTP_NOT_IMPLEMENTED,           	// 501
	HTTP_VERSION_NOT_SUPPORTED      	// 505
};


struct http_header_t {
	char key[HTTP_HDR_KEY_MAX_LEN];
	char value[HTTP_HDR_VAL_MAX_LEN];
};

typedef struct http_header_t 			http_header_t;

struct http_request_t {
	char method[HTTP_METHOD_MAX_LEN];
	char path[HTTP_PATH_MAX_LEN];
	char version[HTTP_VERSION_MAX_LEN];
	char headers[HTTP_HEADER_MAX_LEN];
	char body[HTTP_BODY_MAX_LEN];
};

typedef enum http_status_e 				http_status_e;
typedef struct http_request_t 			http_request;

int read_raw_request(int client_fd, char** raw_request);
http_status_e parse_http_request(const char* raw_request, http_request* request);



#endif