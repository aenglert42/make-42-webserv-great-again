#include "custom.hpp"

void run_custom_tests(void)
{
	// Usage: custom_request(HTTP request, expected resonse body or status code);
	custom_request("GET / HTTP/1.1\r\nHost: webserv\r\n\r\n", "content of index.html in root", FILE_LINE);
}