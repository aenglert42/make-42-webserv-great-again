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

static void curl_template(const std::string& url, const std::string& expected, const std::string& testLocation, void (*setup_curl)(CURL*, std::string*, const std::string&))
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

void GET_request(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	curl_template(url, expected, testLocation, setup_get);
}

void POST_request(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	curl_template(url, expected, testLocation, setup_post);
}

void DELETE_request(const std::string& url, const std::string& expected, const std::string& testLocation)
{
	curl_template(url, expected, testLocation, setup_delete);
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