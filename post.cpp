#include "post.hpp"

void run_POST_tests(void)
{
	// Usage: POST_request(url, expected resonse body or status code);
	POST_request("http://webserv/uploads/new.txt", "201", FILE_LINE);
}