#include "hosts.hpp"

#include <iostream>

host_set add_hosts_to_curl(void)
{
	host_set hosts;
	hosts.insert(std::make_pair("host", "port"));
	hosts.insert(std::make_pair("localhost", "4242"));

	// host_set::iterator it;
	// for (it = hosts.begin(); it != hosts.end(); ++it)
	// {
	// 	std::cout << (*it).first << ":" << (*it).second << std::endl;
	// }

	return (hosts);
}

curl_slist *create_host_list(void)
{
	// struct curl_slist *host;
	
	host = curl_slist_append(NULL, "webserv:80:127.0.0.1");
	curl_slist_append(host, "webserv:5500:127.0.0.1");
	curl_slist_append(host, "server1:6000:127.0.0.1");
	curl_slist_append(host, "server2:80:127.0.0.1");
	curl_slist_append(host, "server2:8080:127.0.0.1");
	curl_slist_append(host, "server2:8081:127.0.0.1");
	curl_slist_append(host, "server2:127.0.0.1");
	curl_slist_append(host, "nonexistingserver:8080:127.0.0.1");
	add_hosts_to_curl();
	return (host);
}

void add_hosts()
{

}