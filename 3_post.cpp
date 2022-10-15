#include "post.hpp"

void run_POST_tests(void)
{
	// Usage: POST_TEST("url", "expected resonse body or status code");
	POST_TEST("http://webserv/uploads/new.txt", "201");
	POST_TEST("http://server2:8080/new.txt", "405");
	POST_TEST("http://webserv/uploads/new.txt", "201");
	POST_TEST("http://webserv/uploads/no_permission_file", "403");
	POST_TEST("http://webserv/uploads/doesnotexist/new.txt", "404");
	// POST_TEST("http://webserv/uploads/new.cgi", "THIS IS THE CONTENT OF MY NEW FILE.");
	POST_TEST("http://webserv/uploads/file.cgi.not", "201");
	POST_TEST("http://webserv/uploads/.cgi", "201"); // not a file extension but a hidden file
	POST_TEST("http://server1:6000/route/file.cgi", "500"); //no execute permission for cgi executable
	POST_TEST("http://server2:8080/route/file.cgi", "500"); //cgi executable doesn't exist
	POST_TEST("http://webserv/uploads/no_permission_file.cgi", "403");
}