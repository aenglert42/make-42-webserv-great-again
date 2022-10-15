#include "delete.hpp"

void run_DELETE_tests(void)
{
	// Usage: DELETE_REQUEST("url", "expected resonse body or status code");
	DELETE_REQUEST("http://webserv/uploads/new.txt", "204");
}