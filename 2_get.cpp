#include "get.hpp"

void run_GET_tests(void)
{
	// Usage: GET_test("url", "expected resonse or status code", FILE_LINE);
	GET_test("http://webserv/", "content of index.html in ./server/root/", FILE_LINE);
	GET_test("http://webserv:80/", "content of index.html in ./server/root/", FILE_LINE);
	GET_test("http://webserv/route/one/", "content of custom.html in ./server/root/dir/one/", FILE_LINE);
	GET_test("http://webserv/route/one/two/", "content of index.html in ./server/root/dir/index/", FILE_LINE);
	GET_test("http://webserv:5500/", "", FILE_LINE); //  can't connect
	GET_test("http://webserv/route/permission_dir/file", "content of file in ./server/root/dir/permission_dir/", FILE_LINE);
	GET_test("http://server1:6000/file", "content of file in ./server/root/server1/", FILE_LINE);
	GET_test("http://server1:6000/doesnotexist", "MY_CUSTOM_404_PAGE", FILE_LINE);
	GET_test("http://server2:8080/route/file", "content of file in ./server/root/server2/", FILE_LINE);
	GET_test("http://server2:8081/route/file", "content of file in ./server/root/server2/", FILE_LINE);
	GET_test("http://nonexisting:8080/route/file", "content of file in ./server/root/server2/", FILE_LINE); // going for default server
	GET_test("http://webserv/route/permission_dir/file.cgi", "CONTENT OF FILE.CGI IN ./SERVER/ROOT/DIR/PERMISSION_DIR/", FILE_LINE);
	GET_test("http://webserv/route/permission_dir/no_permission_file", "403", FILE_LINE);
	GET_test("http://webserv/route/no_permission_dir/file", "403", FILE_LINE);
	GET_test("http://webserv/route/nonexistingfile", "404", FILE_LINE);
	GET_test("http://webserv/route/nonexistingdir/", "404", FILE_LINE);
	GET_test("http://webserv/index", "404", FILE_LINE);
	GET_test("http://webserv/index/", "content of index.html in ./server/root/dir/index/", FILE_LINE);
	GET_test("http://webserv/index/custom/", "content of custom.html in ./server/root/dir/index/custom/", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/", "autoindex123", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/no_permission_dir/", "403", FILE_LINE);
	GET_test("http://webserv/index/no/autoindex/nonexisting/", "404", FILE_LINE);
	GET_test("http://webserv/index/no/no_autoindex/", "404", FILE_LINE);
	GET_test("http://webserv/uploads/no_permission_file.cgi", "403", FILE_LINE);
	GET_test("http://webserv/uploads/no_permission_dir/file.cgi", "403", FILE_LINE);
}