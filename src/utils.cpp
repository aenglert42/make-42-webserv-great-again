#include "utils.hpp"

static long no_throw_stol(const std::string& string)
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

void evaluate_test(const std::string& response, const std::string& expected, const long& statuscode)
{
	if (response.compare(expected) == 0)
		std::cout << GREEN << "OK" << RESET << std::endl;
	else if (no_throw_stol(expected) == statuscode && statuscode > 99 && statuscode < 600)
		std::cout << GREEN << "OK" << RESET << " status code: " << statuscode << std::endl;
	else if (response.find(expected) != std::string::npos)
		std::cout << GREEN << "OK" << RESET << " found: " << expected << std::endl;
	else
	{
		g_ko_counter++;
		std::cout << RED << "KO" << RESET << std::endl;
		std::cout << "expected: " << expected << std::endl;
		std::cout << "recieved: " << response << std::endl;
	}
	std::cout << std::endl;
}

void evaluate_test(const std::string& response, const std::string& expected)
{
	if (response.compare(expected) == 0)
		std::cout << GREEN << "OK" << RESET << std::endl;
	else if (response.find(expected) != std::string::npos)
		std::cout << GREEN << "OK" << RESET << " found: " << expected << std::endl;
	else
	{
		g_ko_counter++;
		std::cout << RED << "KO" << RESET << std::endl;
		std::cout << "expected: " << expected << std::endl;
		std::cout << "recieved: " << response << std::endl;
	}
	std::cout << std::endl;
}