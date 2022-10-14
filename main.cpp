#include <iostream>
#include <string>
#include <curl/curl.h>

// #include "Testsurf.hpp"
#include "defines.hpp"
#include "custom.hpp"
#include "get.hpp"
#include "post.hpp"
#include "delete.hpp"
#include "hosts.hpp"

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define INVALID -1
#define UNKNOWN -2
#define BUFFER_SIZE 1024

struct curl_slist *g_curl_host_list = NULL;
host_set g_host_set;

void print_welcome(void)
{
	std::cout << GREEN << BOLD << "\
   __            __                  ____\n\
  / /____  _____/ /________  _______/ __/\n\
 / __/ _ \\/ ___/ __/ ___/ / / / ___/ /_\n\
/ /_/  __(__  ) /_(__  ) /_/ / /  / __/\n\
\\__/\\___/____/\\__/____/\\__,_/_/  /_/\n\
" << RESET<< std::endl;
}

void print_custom(void)
{
	std::cout << GREEN << BOLD << "Custom Requests" << RESET<< std::endl;
}

void print_GET(void)
{
	std::cout << GREEN << BOLD << "GET Requests" << RESET<< std::endl;
}

void print_POST(void)
{
	std::cout << GREEN << BOLD << "POST Requests" << RESET<< std::endl;
}

void print_DELETE(void)
{
	std::cout << GREEN << BOLD << "DELETE Requests" << RESET<< std::endl;
}

void print_summary(void)
{
	std::cout << GREEN << BOLD << std::endl << "Done." << RESET << std::endl;
}

long nothrow_stol(const std::string& string)
{
	long ret;
	try {
		ret = stol(string);
	}
	catch (std::exception &e)
	{
		return (INVALID);
	}
	return (ret);
}

void evaluation(const std::string& testcase, const std::string& response, const std::string& expected, long statuscode, const std::string &testLocation)
{
	static int i = 1;

	std::cout << YELLOW << "Test " << i << ": " << testcase << BLUE << "\tfrom: " << testLocation << RESET << std::endl;
	if (response.compare(expected) == 0)
		std::cout << GREEN << "OK" << RESET << std::endl;
	else if (nothrow_stol(expected) == statuscode && statuscode > 99)
		std::cout << GREEN << "OK" << RESET << " status code: " << statuscode << std::endl;
	else if (response.find(expected) != std::string::npos)
		std::cout << GREEN << "OK" << RESET << " found: " << expected << std::endl;
	else
	{
		std::cout << RED << "KO" << RESET << std::endl;
		std::cout << "expected: " << expected << std::endl;
		std::cout << "recieved: " << response << std::endl;
	}
	i++;
}

void add_hosts_to_curl(void)
{
	host_set::iterator it;
	for (it = g_host_set.begin(); it != g_host_set.end(); ++it)
	{
		std::string str = (*it).first + ":" + (*it).second + ":" + "127.0.0.1";
		if (g_curl_host_list == NULL)
			g_curl_host_list = curl_slist_append(NULL, str.c_str());
		else
			curl_slist_append(g_curl_host_list, str.c_str());
	}
}

void add_host(const std::string& server_name, const std::string& port)
{
	if (server_name.empty() == false && port.empty() == false)
		g_host_set.insert(std::make_pair(server_name, port));
}

void custom_request(const std::string& request_raw, const std::string& expected_raw, const std::string &testLocation)
{
	std::string request = request_raw.substr(1, request_raw.length() - 2);
	std::string expected = expected_raw.substr(1, expected_raw.length() - 2);
	int sock = 0;
	long valread;
	struct sockaddr_in serv_addr;
	char readBuffer[BUFFER_SIZE] = {0};
	std::string response;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "Error: Couldn't create socket" << std::endl;
		return ;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(g_port_for_custom_requests);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		std::cout << "Error: Invalid address / Address not supported" << std::endl;
		return ;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Error: Failed to connect to port " << g_port_for_custom_requests << ", which is used to send the custom requests. Make sure your server is listening to it, or change it in: " << BLUE << "custom.cpp:3" << RESET << std::endl;
		return ;
	}
	send(sock, request.c_str(), request.length(), 0);
	do
	{
		valread = read(sock, readBuffer, BUFFER_SIZE);
		response += readBuffer;
	}
	while (valread > 0);
	if (valread < 0)
		response = "Error: Read failed";
	evaluation(request.substr(0, request.find_first_of('\n') - 1), response, expected, UNKNOWN, testLocation);
}


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void setup_get(CURL *curl, std::string *response, const std::string& url)
{
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_RESOLVE, g_curl_host_list);
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

void setup_post(CURL *curl, std::string *response, const std::string& url)
{
	setup_get(curl, response, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "This is my POST body with length of 39.");
}

void setup_delete(CURL *curl, std::string *response, const std::string& url)
{
	setup_get(curl, response, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
}

void curl_template(const std::string& url, const std::string& expected, const std::string &testLocation, void (*setup_curl)(CURL*, std::string*, const std::string&))
{
	long statuscode = 0;
	CURL *curl= curl_easy_init();
	CURLcode res;
	std::string response = "";
	if(curl)
	{
		(*setup_curl)(curl, &response, url.substr(1, url.length() - 2));
		res = curl_easy_perform(curl);
		if(res == CURLE_OK)
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
		else
		{
			response = "Error: ";
			response += curl_easy_strerror(res);
		}
		evaluation(url.substr(1, url.length() - 2), response, expected.substr(1, expected.length() - 2), statuscode, testLocation);
		curl_easy_cleanup(curl);
	}
	else
		std::cout << RED << "Error: curl_easy_init failed" << RESET << std::endl;
}

void GET_request(const std::string& url, const std::string& expected, const std::string &testLocation)
{
	curl_template(url, expected, testLocation, setup_get);
}

void POST_request(const std::string& url, const std::string& expected, const std::string &testLocation)
{
	curl_template(url, expected, testLocation, setup_post);
}

void DELETE_request(const std::string& url, const std::string& expected, const std::string &testLocation)
{
	curl_template(url, expected, testLocation, setup_delete);
}

int main(void)
{
	print_welcome();
	// create directories
	// create files
	// create apply permissions
	add_hosts();
	add_hosts_to_curl();
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