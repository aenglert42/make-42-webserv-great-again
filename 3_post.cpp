#include "post.hpp"

void run_POST_tests(void)
{
	// Usage: POST_test("url", "expected resonse body or status code", FILE_LINE);
	POST_test("http://webserv/uploads/new.txt", "201", FILE_LINE);
	POST_test("http://server2:8080/new.txt", "405", FILE_LINE);
	POST_test("http://webserv/uploads/new.txt", "201", FILE_LINE);
	POST_test("http://webserv/uploads/no_permission_file", "403", FILE_LINE);
	POST_test("http://webserv/uploads/doesnotexist/new.txt", "404", FILE_LINE);
	// POST_test("http://webserv/uploads/new.cgi", "THIS IS THE CONTENT OF MY NEW FILE.", FILE_LINE);
	POST_test("http://webserv/uploads/file.cgi.not", "201", FILE_LINE);
	POST_test("http://webserv/uploads/.cgi", "201", FILE_LINE); // not a file extension but a hidden file
	POST_test("http://webserv/uploads/file.cgi", "THIS IS MY POST BODY WITH LENGTH OF 39.", FILE_LINE);
	POST_test("http://server1:6000/route/file.cgi", "500", FILE_LINE); //no execute permission for cgi executable
	POST_test("http://server2:8080/route/file.cgi", "500", FILE_LINE); //cgi executable doesn't exist
	POST_test("http://webserv/uploads/no_permission_dir/file.cgi", "403", FILE_LINE);
}