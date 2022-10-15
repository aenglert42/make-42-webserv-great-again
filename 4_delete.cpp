#include "delete.hpp"

void run_DELETE_tests(void)
{
	// Usage: DELETE_TEST("url", "expected resonse body or status code");
	DELETE_TEST("http://webserv/uploads/new.txt", "204");
	DELETE_TEST("http://webserv/uploads/file.cgi.not", "204");
	DELETE_TEST("http://webserv/uploads/.cgi", "204");
	DELETE_TEST("http://webserv/uploads/doesnotexist", "404");
	DELETE_TEST("http://webserv/uploads/no_permission_file", "403");
}