#include "delete.hpp"

void run_DELETE_tests(void)
{
	// Usage: DELETE_request(url, expected resonse body or status code);
	DELETE_request("http://webserv/uploads/new.txt", "204", FILE_LINE);
}