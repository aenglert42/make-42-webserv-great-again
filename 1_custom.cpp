#include "custom.hpp"

// Port used to send the custom requests to. Make sure your server is listening to it, or change it here.
uint16_t g_port_for_custom_requests = 80;

void run_custom_tests(void)
{
	// Usage: custom_test("HTTP request", "expected resonse body or status code", FILE_LINE);
	custom_test("GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root", FILE_LINE); // all good
	custom_test("\n", "400", FILE_LINE); // bad request
	custom_test(" ", "400", FILE_LINE); // bad request
	custom_test("GET HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // incomplete request-line
	custom_test("GET HTTP/1.1 \r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // incomplete request-line
	custom_test("GET /\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // incomplete request-line
	custom_test("GET / \r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // incomplete request-line
	custom_test("GET /  HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // additional space in request-line before protocol
	custom_test("GET  / HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // additional space in request-line after method
	custom_test(" GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // request-line with leading space
	custom_test("GET / HTTP/1.1\r\nHost:webserv\r\n\r\n", "content of index.html in root", FILE_LINE); // headerfield without optional space
	custom_test("GET / HTTP/1.1\r\n Host: webserv\r\n\r\n", "400", FILE_LINE); // headerfield without leading space
	custom_test("GET / HTTP/1.1\r\nHost: webserv \r\n\r\n", "content of index.html in root", FILE_LINE); // headerfield without optional spaces
	custom_test("GET / HTTP/1.1\r\nHost:  webserv  \r\n\r\n", "400", FILE_LINE); // headerfield without additional spaces
	custom_test("GET / HTTP/1.1\r\nHost:      webserv      \r\n\r\n", "400", FILE_LINE); // headerfield without additional spaces
	custom_test("GET / HTTP/1.1\r\nHost:webserv      \r\n\r\n", "400", FILE_LINE); // headerfield without additional spaces
	custom_test("GET / HTTP/1.1\r\nHost:    webserv\r\n\r\n", "400", FILE_LINE); // headerfield without additional spaces
	custom_test("GET / HTTP/1.1\r\nHost : webserv\r\n\r\n", "400", FILE_LINE); // headerfield with invalid space (after key)
	custom_test("GET /route/dir/%25file HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of %file in dir", FILE_LINE); // valid percent encoding
	custom_test("GET /route/dir/%2myfile HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // invalid percent encoding
	custom_test("GET /ü-ei HTTP/1.1\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // invalid char
	custom_test("GET . HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root", FILE_LINE); // path resolving
	custom_test("GET .. HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root", FILE_LINE); // path resolving
	custom_test("GET ... HTTP/1.1\r\nHost: webserv\r\n\r\n", "404", FILE_LINE); // path resolving
	custom_test("GET .../README.md HTTP/1.1\r\nHost: webserv\r\n\r\n", "404", FILE_LINE); // path resolving
	custom_test("GET / HTTP/1.0\r\nHost: webserv\r\n\r\n", "505", FILE_LINE); // invalid protocol
	custom_test("GET / HTTP/1.1\r\n\r\n", "400", FILE_LINE); // no host
	custom_test("GET / HTTP/1.1\r\nHost: webserv\r\nHost: webserv\r\n\r\n", "400", FILE_LINE); // header field duplicate
	custom_test("GET / HTTP/1.1\r\nHost: webserv\r\ncontent-length: 0\r\ntransfer-encoding: chunked\r\n\r\n", "400", FILE_LINE); // both content-length and transfer-encoding is illegal
	custom_test("GET / HTTP/1.1\r\nUser-Agent: Go-http-client/1.1\r\n\r\n", "400", FILE_LINE); // no host
	custom_test("GET / HTTP/1.1\nHost: webserv\r\n\r\n", "400", FILE_LINE); // missing '\r'
	custom_test("PST / HTTP/1.1\r\nHost: webserv\r\n\r\n", "501", FILE_LINE); // invalid method
	custom_test("POST /new.txt HTTP/1.1\r\nHost: webserv\r\n\r\n", "411", FILE_LINE); // POST without content-length header field
	custom_test("POST /uploads/big.txt HTTP/1.1\r\nHost: webserv\r\ncontent-length: 200\r\n\r\n01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", "413", FILE_LINE); // body > max body size
}