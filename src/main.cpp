#include <limits>
#include "defines.hpp"
#include "custom.hpp"
#include "get.hpp"
#include "post.hpp"
#include "delete.hpp"
#include "hosts.hpp"
#include "curl_requests.hpp"
#include "print.hpp"
#include "infrastructure.hpp"

struct curl_slist *g_curl_host_list = NULL;
int g_ko_counter;
host_set g_host_set;

static void give_instructions(void)
{
	std::cout << "Make sure you configured your server as described in " << BLUE << "README.md" << RESET << " and that it is running!\nPress enter to continue . . . ";
	std::cin.sync();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(void)
{
	g_ko_counter = 0;
	print_welcome();
	// create directories
	// create files
	// create apply permissions
	give_instructions();
	create_infrastructure();
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

// AE libcurl documentation
// https://curl.se/libcurl/c/

// AE add headers
// https://curl.se/libcurl/c/httpcustomheader.html
