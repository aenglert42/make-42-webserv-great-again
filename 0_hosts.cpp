#include "hosts.hpp"

void add_hosts(void)
{
	// Usage: add_host("uri-host", "port");
	// note that no check for invalid input is done
	add_host("webserv", "8080");
	add_host("webserv", "80");
}