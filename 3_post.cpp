#include "post.hpp"

void run_POST_tests(void)
{
	// Usage: POST_TEST("url", "expected resonse body or status code");
	POST_TEST("http://webserv/uploads/new.txt", "201");
}