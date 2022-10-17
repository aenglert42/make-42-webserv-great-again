#include "custom.hpp"

// Port used to send the custom requests to. Make sure your server is listening to it, or change it here.
uint16_t g_port_for_custom_requests = 80;

void run_custom_tests(void)
{
	// Usage: CUSTOM_TEST("HTTP request", "expected resonse body or status code");
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root"); // all good
	CUSTOM_TEST("\n", "400"); // bad request
	CUSTOM_TEST(" ", "400"); // bad request
	CUSTOM_TEST("GET HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // incomplete request-line
	CUSTOM_TEST("GET HTTP/1.1 \r\nHost: webserv\r\n\r\n", "400"); // incomplete request-line
	CUSTOM_TEST("GET /\r\nHost: webserv\r\n\r\n", "400"); // incomplete request-line
	CUSTOM_TEST("GET / \r\nHost: webserv\r\n\r\n", "400"); // incomplete request-line
	CUSTOM_TEST("GET /  HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // additional space in request-line before protocol
	CUSTOM_TEST("GET  / HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // additional space in request-line after method
	CUSTOM_TEST(" GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // request-line with leading space
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost:webserv\r\n\r\n", "content of index.html in root"); // headerfield without optional space
	CUSTOM_TEST("GET / HTTP/1.1\r\n Host: webserv\r\n\r\n", "400"); // headerfield without leading space
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost: webserv \r\n\r\n", "content of index.html in root"); // headerfield without optional spaces
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost:  webserv  \r\n\r\n", "400"); // headerfield without additional spaces
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost:      webserv      \r\n\r\n", "400"); // headerfield without additional spaces
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost:webserv      \r\n\r\n", "400"); // headerfield without additional spaces
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost:    webserv\r\n\r\n", "400"); // headerfield without additional spaces
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost : webserv\r\n\r\n", "400"); // headerfield with invalid space (after key)
	CUSTOM_TEST("GET /route/dir/%25file HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of %file in dir"); // valid percent encoding
	CUSTOM_TEST("GET /route/dir/%2myfile HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // invalid percent encoding
	CUSTOM_TEST("GET /ü-ei HTTP/1.1\r\nHost: webserv\r\n\r\n", "400"); // invalid char
	CUSTOM_TEST("GET . HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root"); // path resolving
	CUSTOM_TEST("GET .. HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root"); // path resolving
	CUSTOM_TEST("GET ... HTTP/1.1\r\nHost: webserv\r\n\r\n", "404"); // path resolving
	CUSTOM_TEST("GET .../README.md HTTP/1.1\r\nHost: webserv\r\n\r\n", "404"); // path resolving
	CUSTOM_TEST("GET / HTTP/1.0\r\nHost: webserv\r\n\r\n", "505"); // invalid protocol
	CUSTOM_TEST("GET / HTTP/1.1\r\n\r\n", "400"); // no host
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost: webserv\r\nHost: webserv\r\n\r\n", "400"); // header field duplicate
	CUSTOM_TEST("GET / HTTP/1.1\r\nHost: webserv\r\ncontent-length: 0\r\ntransfer-encoding: chunked\r\n\r\n", "400"); // both content-length and transfer-encoding is illegal
	CUSTOM_TEST("GET / HTTP/1.1\r\nUser-Agent: Go-http-client/1.1\r\n\r\n", "400"); // no host
	CUSTOM_TEST("GET / HTTP/1.1\nHost: webserv\r\n\r\n", "400"); // missing '\r'
	CUSTOM_TEST("PST / HTTP/1.1\r\nHost: webserv\r\n\r\n", "501"); // invalid method
	CUSTOM_TEST("POST /new.txt HTTP/1.1\r\nHost: webserv\r\n\r\n", "411"); // POST without content-length header field
	CUSTOM_TEST("POST /uploads/big.txt HTTP/1.1\r\nHost: webserv\r\ncontent-length: 200\r\n\r\n01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", "413"); // body > max body size
}