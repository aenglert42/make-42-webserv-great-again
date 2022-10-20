#include "infrastructure.hpp"

static void set_permission(const std::string& directory, std::filesystem::perms prms)
{
	std::filesystem::permissions(directory, prms);
}

static void set_permission(const std::string& directory, const std::string& file, std::filesystem::perms prms)
{
	std::filesystem::permissions(directory + file, prms);
}

static void apply_permissions(void)
{
	set_permission(PERMISSION_DIR, NO_PERMISSION_FILE, std::filesystem::perms::none);
	set_permission(UPLOADS, NO_PERMISSION_FILE, std::filesystem::perms::none);
	set_permission(UPLOADS, NO_PERMISSION_FILE_CGI, std::filesystem::perms::none);
	set_permission(NO_PERMISSION_DIR, std::filesystem::perms::owner_read | std::filesystem::perms::owner_write);
	set_permission(AUTOINDEX_NO_PERMISSION_DIR, std::filesystem::perms::owner_write);
}

static void create_file_with_content(const std::string& directory, const std::string& file, const std::string& content)
{
	std::string path = directory + file;
	std::ofstream outfile(path);

	if (outfile.is_open() == false)
		return ; // AE errorhandling
	outfile << content;
	outfile.close();
}

static void create_file_with_content(const std::string& directory, const std::string& file)
{
	std::string path = directory + file;
	std::ofstream outfile(path);

	if (outfile.is_open() == false)
		return ; // AE errorhandling
	outfile << "content of " << file << " in " << directory;
	outfile.close();
}

static void create_files(void)
{
	create_file_with_content(DIR, "%file");
	create_file_with_content(ROOT, INDEX_HTML);

	create_file_with_content(ONE, CUSTOM_HTML);

	create_file_with_content(TWO, INDEX_HTML);

	create_file_with_content(INDEX, INDEX_HTML);

	create_file_with_content(CUSTOM_INDEX, CUSTOM_HTML);
	
	create_file_with_content(PERMISSION_DIR, FILE);
	create_file_with_content(PERMISSION_DIR, NO_PERMISSION_FILE);
	create_file_with_content(PERMISSION_DIR, DOT_CGI);
	create_file_with_content(PERMISSION_DIR, CGI_FILE);

	create_file_with_content(NO_PERMISSION_DIR, FILE);
	create_file_with_content(NO_PERMISSION_DIR, CGI_FILE);

	create_file_with_content(UPLOADS, CGI_FILE);
	create_file_with_content(UPLOADS, NO_PERMISSION_FILE);
	create_file_with_content(UPLOADS, NO_PERMISSION_FILE_CGI);

	create_file_with_content(SERVER1, FILE);
	create_file_with_content(SERVER1, CGI_FILE);
	create_file_with_content(SERVER1_CUSTOM, CUSTOM_HTML, "MY_CUSTOM_404_PAGE");

	create_file_with_content(SERVER2, FILE);
	create_file_with_content(SERVER2, CGI_FILE);
}

static void create_directories(void)
{
	std::filesystem::create_directories(TWO);
	std::filesystem::create_directories(PERMISSION_DIR);
	std::filesystem::create_directories(NO_PERMISSION_DIR);
	std::filesystem::create_directories(UPLOADS);
	std::filesystem::create_directories(CUSTOM_INDEX);
	std::filesystem::create_directories(AUTOINDEX);
	std::filesystem::create_directories(NO_AUTOINDEX);
	std::filesystem::create_directories(AUTOINDEX_NO_PERMISSION_DIR);
	std::string tmp = AUTOINDEX;
	std::filesystem::create_directories(tmp + "autoindex123/");

	std::filesystem::create_directories(SERVER1_CUSTOM);
	std::filesystem::create_directories(SERVER2);
}

void clear_infrastructure(void)
{
	if (std::filesystem::exists(NO_PERMISSION_DIR))
		set_permission(NO_PERMISSION_DIR, std::filesystem::perms::owner_all);
	if (std::filesystem::exists(AUTOINDEX_NO_PERMISSION_DIR))
		set_permission(AUTOINDEX_NO_PERMISSION_DIR, std::filesystem::perms::owner_all);
	std::filesystem::remove_all(ROOT);
}

void create_infrastructure(void)
{
	clear_infrastructure();
	create_directories();
	create_files();
	apply_permissions();
}