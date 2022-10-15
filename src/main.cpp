#include "defines.hpp"
#include "custom.hpp"
#include "get.hpp"
#include "post.hpp"
#include "delete.hpp"
#include "hosts.hpp"
#include "curl_requests.hpp"
#include "print.hpp"

struct curl_slist *g_curl_host_list = NULL;
int g_ko_counter;
host_set g_host_set;

int main(void)
{
	g_ko_counter = 0;
	print_welcome();
	// create directories
	// create files
	// create apply permissions
	add_hosts();
	create_curl_host_list();
	print_custom();
	run_custom_tests();
	print_GET();
	run_GET_tests();
	print_POST();
	run_POST_tests();
	print_DELETE();
	run_DELETE_tests();
	print_summary();
	// reset permissions
	// delete files
	// delete directories
	return 0;
}

// libcurl documentation
// https://curl.se/libcurl/c/

// add headers
// https://curl.se/libcurl/c/httpcustomheader.html


// c++ main.cpp Testsurf.cpp get.cpp post.cpp delete.cpp custom.cpp hosts.cpp -lcurl && ./a.out