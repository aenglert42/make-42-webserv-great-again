#include "hosts.hpp"

void add_hosts(void)
{
	// Usage: add_host("uri-host", "port");
	// note that no check for invalid input is done
	add_host("webserv", "80");
	add_host("webserv", "5500");
	add_host("server1", "6000");
	add_host("server2", "80");
	add_host("server2", "8080");
	add_host("server2", "8081");
	add_host("server2", "8082");
	add_host("nonexisting", "8080");
}