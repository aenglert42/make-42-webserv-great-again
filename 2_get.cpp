#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_REQUEST("url", "expected resonse body or status code");
	// GET_request("http://webserv:8080", "content of index.html in root", FILE_LINE);
	GET_REQUEST("http://webserv", "content of index.html in root");
}