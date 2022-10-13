#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_request(url, expected resonse body or status code);
	GET_request("http://webserv", "content of index.html in root", FILE_LINE);
}