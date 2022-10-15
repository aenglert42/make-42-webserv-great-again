#include "delete.hpp"

void run_DELETE_tests(void)
{
	// Usage: DELETE_TEST("url", "expected resonse body or status code");
	DELETE_TEST("http://webserv/uploads/new.txt", "204");
}