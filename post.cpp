#include "post.hpp"

void run_POST_tests(void)
{
	// Usage: POST_REQUEST("url", "expected resonse body or status code");
	POST_REQUEST("http://webserv/uploads/new.txt", "201");
}