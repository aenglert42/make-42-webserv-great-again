#include "curl_requests.hpp"

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

static void setup_get(CURL *curl, std::string *response, const std::string& url)
{
	curl_easy_reset(curl);
	curl_easy_setopt(curl, CURLOPT_RESOLVE, g_curl_host_list);
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
}

static void setup_post(CURL *curl, std::string *response, const std::string& url)
{
	setup_get(curl, response, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "This is my POST body with length of 39.");
}

static void setup_delete(CURL *curl, std::string *response, const std::string& url)
{
	setup_get(curl, response, url);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
}

static void curl_request_test_template(const std::string& url, const std::string& expected, void (*setup_curl)(CURL*, std::string*, const std::string&))
{
	long statuscode = 0;
	CURL *curl= curl_easy_init();
	CURLcode res;
	std::string response = "";
	if(curl)
	{
		(*setup_curl)(curl, &response, url);
		res = curl_easy_perform(curl);
		if(res == CURLE_OK)
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statuscode);
		else
		{
			response = "Error: ";
			response += curl_easy_strerror(res);
		}
		evaluate_test(response, expected.substr(1, expected.length() - 2), statuscode);
		curl_easy_cleanup(curl);
	}
	else
		std::cout << RED << "Error: curl_easy_init failed" << RESET << std::endl;
}

void GET_test(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	static int i_get = 1;

	print_test_title(i_get, GET, url.substr(1, url.length() - 2), testLocation);
	curl_request_test_template(url.substr(1, url.length() - 2), expected, setup_get);
	i_get++;
}

void POST_test(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	static int i_post = 1;

	print_test_title(i_post, POST, url.substr(1, url.length() - 2), testLocation);
	curl_request_test_template(url.substr(1, url.length() - 2), expected, setup_post);
	i_post++;
}

void DELETE_test(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	static int i_delete = 1;

	print_test_title(i_delete, DELETE, url.substr(1, url.length() - 2), testLocation);
	curl_request_test_template(url.substr(1, url.length() - 2), expected, setup_delete);
	i_delete++;
}

void create_curl_host_list(void)
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

void add_host(const std::string& uri_host, const std::string& port)
{
	if (uri_host.empty() == false && port.empty() == false)
		g_host_set.insert(std::make_pair(uri_host, port));
}