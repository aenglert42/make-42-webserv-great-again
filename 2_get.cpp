#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_TEST("url", "expected resonse body or status code");
	GET_TEST("http://webserv", "content of index.html in root");
}