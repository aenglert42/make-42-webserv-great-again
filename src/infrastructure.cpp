#include "infrastructure.hpp"

static void create_files(void)
{

}

static void create_directories(void)
{
	std::string root = ROOT;
	std::string server1 = SERVER1;
	std::string server2 = SERVER2;
	std::filesystem::create_directories(root + "/1/2/a");
	std::filesystem::create_directories(root + "/" + server1);
	std::filesystem::create_directories(root + "/" + server2);
}

static void clear_infrastructure(void)
{
	std::filesystem::remove_all(ROOT);
}

void create_infrastructure(void)
{
	clear_infrastructure();
	create_directories();
	create_files();
}