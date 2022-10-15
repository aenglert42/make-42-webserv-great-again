#include "custom.hpp"

// Port used to send the custom requests to. Make sure your server is listening to it, or change it here.
uint16_t g_port_for_custom_requests = 80;

void run_custom_tests(void)
{
	// Usage: CUSTOM_REQUEST("HTTP request", "expected resonse body or status code");
	CUSTOM_REQUEST("GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root");
}