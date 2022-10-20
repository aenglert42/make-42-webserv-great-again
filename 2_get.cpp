#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_test("url", "expected resonse body or status code", FILE_LINE);
	GET_test("http://webserv", "content of index.html in root", FILE_LINE);
	GET_test("http://webserv:80", "content of index.html in root", FILE_LINE);
	GET_test("http://webserv/route/lol/", "content of different.html in lol", FILE_LINE);
	GET_test("http://webserv/route/lol/troll/", "content of index.html in troll", FILE_LINE);
	GET_test("http://webserv:5500", "", FILE_LINE); //  can't connect
	GET_test("http://webserv/route/dir/file", "content of file in dir", FILE_LINE);
	GET_test("http://webserv/route/cgi/file", "content of file in cgi", FILE_LINE);
	GET_test("http://server1:6000/route/file", "content of file in server1", FILE_LINE);
	GET_test("http://server1:6000/route/doesnotexist", "MY_CUSTOM_PAGE", FILE_LINE);
	GET_test("http://server2/route/file", "405", FILE_LINE); // going for default server
	GET_test("http://nonexisting:8080/route/file", "405", FILE_LINE); // going for default server
	GET_test("http://server2:8080/route/file", "content of file in server2", FILE_LINE);
	GET_test("http://server2:8081/route/file", "content of file in server2", FILE_LINE);
	GET_test("http://webserv/route/dir/file.cgi", "CONTENT OF FILE.CGI IN DIR", FILE_LINE);
	GET_test("http://webserv/route/dir/norfile", "403", FILE_LINE);
	GET_test("http://webserv/route/nordir/file", "content of file in nordir", FILE_LINE);
	GET_test("http://webserv/route/nowdir/file", "content of file in nowdir", FILE_LINE);
	GET_test("http://webserv/route/noxdir/file", "403", FILE_LINE);
	GET_test("http://webserv/route/nordir/subdir/file", "content of file in nordirsubdir", FILE_LINE);
	GET_test("http://webserv/route/nowdir/subdir/file", "content of file in nowdirsubdir", FILE_LINE);
	GET_test("http://webserv/route/noxdir/subdir/file", "403", FILE_LINE);
	GET_test("http://webserv/route/dir/nowfile", "content of nowfile in dir", FILE_LINE);
	GET_test("http://webserv/route/dir/nonexistingfile", "404", FILE_LINE);
	GET_test("http://webserv/route/dir/nonexistingdir/", "404", FILE_LINE);
	GET_test("http://webserv/index", "404", FILE_LINE);
	GET_test("http://webserv/index/", "content of index.html in index", FILE_LINE);
	GET_test("http://webserv/index/custom/", "content of custom_index.html in custom", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/", "autoindex123", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/nopermission/", "403", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/nonexisting/", "404", FILE_LINE);
	GET_test("http://webserv/index/no/noautoindex/", "404", FILE_LINE);
	GET_test("http://webserv/uploads/nopermissionfile.cgi", "403", FILE_LINE); // file to call the cgi on has no permissions
}