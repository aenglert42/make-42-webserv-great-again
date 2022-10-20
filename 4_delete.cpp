#include "delete.hpp"

void run_DELETE_tests(void)
{
	// Usage: DELETE_test("url", "expected resonse body or status code", FILE_LINE);
	DELETE_test("http://webserv/uploads/new.txt", "204", FILE_LINE);
	DELETE_test("http://webserv/uploads/file.cgi.not", "204", FILE_LINE);
	DELETE_test("http://webserv/uploads/.cgi", "204", FILE_LINE);
	DELETE_test("http://webserv/uploads/doesnotexist", "404", FILE_LINE);
	DELETE_test("http://webserv/uploads/no_permission_file", "403", FILE_LINE);
}