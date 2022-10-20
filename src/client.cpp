#include "client.hpp"

void custom_test(const std::string& request, const std::string& expected, const std::string& testLocation)
{
	static int i = 1;
	// std::string request = request_raw.substr(1, request_raw.length() - 2);
	// std::string expected = expected_raw.substr(1, expected_raw.length() - 2);
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
		std::cout << "Error: Failed to connect to port " << g_port_for_custom_requests << ", which is used to send the custom requests. Make sure your server is listening to it, or change it in: " << BLUE << "1_custom.cpp:4" << RESET << std::endl;
		return ;
	}
	send(sock, request.c_str(), request.length(), 0);
	valread = read(sock, readBuffer, BUFFER_SIZE - 1);
	response = readBuffer;
	std::cout << YELLOW << "Test " << i << ": " << request.substr(0, request.find_first_of('\n') - 1) << RESET << " located in: " << BLUE << testLocation << RESET << std::endl;
	evaluate_test(response, expected);
	i++;
}