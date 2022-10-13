#include <iostream>
#include <string>
#include <curl/curl.h>

#include "Testsurf.hpp"
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
// #include <string.h>
#include <arpa/inet.h>

#define PORT 80
#define NONE -1
#define EMPTY -2

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
		return (NONE);
	}
	return (ret);
}

void evaluation(const std::string& testcase, const std::string& readBuffer, const std::string& expected, long statuscode, const std::string &testLocation)
{
	static int i = 1;

	std::cout << YELLOW << "Test " << i << ": " << testcase << BLUE << "\tfrom: " << testLocation << RESET << std::endl;
	if (readBuffer.compare(expected) == 0)
		std::cout << GREEN << "OK" << RESET << std::endl;
	else if (nothrow_stol(expected) == statuscode)
		std::cout << GREEN << "OK" << RESET << " status code: " << statuscode << std::endl;
	else if (readBuffer.find(expected) != std::string::npos)
		std::cout << GREEN << "OK" << RESET << " found: " << expected << std::endl;
	else
	{
		std::cout << RED << "KO" << RESET << std::endl;
		std::cout << "expected: " << expected << std::endl;
		std::cout << "recieved: " << readBuffer << std::endl;
	}
	i++;
}

void custom_request(const std::string& request, const std::string& expected, const std::string &testLocation)
{
	int sock = 0;
	size_t valread;
	struct sockaddr_in serv_addr;
	char readBuffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "\n Socket creation error" << std::endl;
		return ;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		std::cout << "\nInvalid address/ Address not supported" << std::endl;
		return ;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "\nConnection Failed" << std::endl;
		return ;
	}
	send(sock, request.c_str(), request.length(), 0);
	valread = read( sock , readBuffer, 1024);
	evaluation(request.substr(0, request.find_first_of('\n') - 1), readBuffer, expected, EMPTY, testLocation);
}


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void setup_get(CURL *curl, std::string *readBuffer, const std::string& url)
{
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_RESOLVE, host);
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);
}

void setup_post(CURL *curl, std::string *readBuffer, const std::string& url)
{
	setup_get(curl, readBuffer, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "This is my POST body with length of 39.");
}

void setup_delete(CURL *curl, std::string *readBuffer, const std::string& url)
{
	setup_get(curl, readBuffer, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
}

void curl_template(const std::string& url, const std::string& expected, const std::string &testLocation, void (*setup_curl)(CURL*, std::string*, const std::string&))
{
	long statuscode = 0;
	CURL *curl= curl_easy_init();
	// struct curl_slist *host = create_host_list();
	host = create_host_list();
	CURLcode res;
	std::string readBuffer;
	if(curl)
	{
		(*setup_curl)(curl, &readBuffer, url);
		res = curl_easy_perform(curl);
		if(res == CURLE_OK)
		{
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
			evaluation(url, readBuffer, expected, statuscode, testLocation);
		}
		curl_easy_cleanup(curl);
	}
	else
		std::cout << RED << "ERROR with curl" << RESET << std::endl;
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
	Testsurf Testsurf;
	print_welcome();
	// create directories
	// create files
	// create apply permissions
	// add hosts
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