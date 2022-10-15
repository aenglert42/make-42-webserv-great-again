#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_TEST("url", "expected resonse body or status code");
	GET_TEST("http://webserv", "content of index.html in root");
	GET_TEST("http://webserv:80", "content of index.html in root");
	GET_TEST("http://webserv/route/lol/", "content of different.html in lol");
	GET_TEST("http://webserv/route/lol/troll/", "content of index.html in troll");
	GET_TEST("http://webserv:5500", ""); //  can't connect
	GET_TEST("http://webserv/route/dir/file", "content of file in dir");
	GET_TEST("http://webserv/route/cgi/file", "content of file in cgi");
	GET_TEST("http://server1:6000/route/file", "content of file in server1");
	GET_TEST("http://server1:6000/route/doesnotexist", "MY_CUSTOM_PAGE");
	GET_TEST("http://server2/route/file", "405"); // going for default server
	GET_TEST("http://nonexistingserver:8080/route/file", "405"); // going for default server
	GET_TEST("http://server2:8080/route/file", "content of file in server2");
	GET_TEST("http://server2:8081/route/file", "content of file in server2");
	GET_TEST("http://webserv/route/dir/file.cgi", "CONTENT OF FILE.CGI IN DIR");
	GET_TEST("http://webserv/route/dir/norfile", "403");
	GET_TEST("http://webserv/route/nordir/file", "content of file in nordir");
	GET_TEST("http://webserv/route/nowdir/file", "content of file in nowdir");
	GET_TEST("http://webserv/route/noxdir/file", "403");
	GET_TEST("http://webserv/route/nordir/subdir/file", "content of file in nordirsubdir");
	GET_TEST("http://webserv/route/nowdir/subdir/file", "content of file in nowdirsubdir");
	GET_TEST("http://webserv/route/noxdir/subdir/file", "403");
	GET_TEST("http://webserv/route/dir/nowfile", "content of nowfile in dir");
	GET_TEST("http://webserv/route/dir/nonexistingfile", "404");
	GET_TEST("http://webserv/route/dir/nonexistingdir/", "404");
	GET_TEST("http://webserv/index", "404");
	GET_TEST("http://webserv/index/", "content of index.html in index");
	GET_TEST("http://webserv/index/custom/", "content of custom_index.html in custom");
	GET_TEST("http://webserv/index/no/autoindex/", "autoindex123");
	GET_TEST("http://webserv/index/no/autoindex/nopermission/", "403");
	GET_TEST("http://webserv/index/no/autoindex/nonexisting/", "404");
	GET_TEST("http://webserv/index/no/noautoindex/", "404");
	GET_TEST("http://webserv/uploads/nopermissionfile.cgi", "403"); // file to call the cgi on has no permissions
}