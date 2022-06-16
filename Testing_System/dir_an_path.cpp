#include "dir_an_path.h"

string dir_an_path::Directories::main_directory()
{
	long unsigned int nameSize = 100;

	auto* userLname = new char[nameSize];

	GetUserNameA(userLname, &nameSize);

	string path = R"(C:\Users\)";

	path += userLname;
	path += R"(\Documents\Testing System\)";

	delete[] userLname;
	return path;
}

string dir_an_path::Directories::Test::dir_sv_tests()
{
	return main_directory() + R"(Tests\)";
}

string dir_an_path::Directories::Test::folder_test(const char* category, const char* section, const char* test_name)
{
	return Section::folder_section(category, section) + test_name + '\\';
}

string dir_an_path::Directories::Test::Section::folder_section(const char* category, const char* section)
{
	return Category::folder_category(category) + section + '\\';
}

string dir_an_path::Directories::Test::Category::dir_categories()
{
	return  dir_sv_tests() + R"(Category\)";
}

string dir_an_path::Directories::Test::Category::folder_category(const char* category)
{
	return dir_categories() + category + '\\';
}

string dir_an_path::Directories::User::dir_sv_accounts()
{
	return main_directory() + R"(Accounts\)";
}

string dir_an_path::Directories::User::save_user_folder(const char* login)
{
	return dir_sv_accounts() + login + '\\';
}

string dir_an_path::Directories::Admin::folder_admin_data()
{
	return main_directory() + R"(Admin\)";
}

string dir_an_path::Path::Admin::path_sv_adm_data()
{
	return Directories::Admin::folder_admin_data() + R"(AdminData.txt)";
}

string dir_an_path::Path::Admin::path_adm_enc_key()
{
	return Directories::Admin::folder_admin_data() + R"(enc_key.txt)";
}

string dir_an_path::Path::User::path_list_logins()
{
	return Directories::User::dir_sv_accounts() + R"(logins.txt)";
}

string dir_an_path::Path::User::path_sv_user_acc(const char* login)
{
	return Directories::User::save_user_folder(login) + login + ".Tes";
}

string dir_an_path::Path::User::path_acc_enc_key(const char* login)
{
	return Directories::User::save_user_folder(login) + "enc_key.txt";
}

string dir_an_path::Path::Test::path_test_list(const char* category, const char* section)
{
	return Directories::Test::Section::folder_section(category, section) + "\\test.txt";
}

string dir_an_path::Path::Test::path_sv_n_questions(const char* category, const char* section, const char* test_name)
{
	return Directories::Test::folder_test(category, section, test_name) + "\\number questions.txt";
}

string dir_an_path::Path::Test::path_sv_questions(const char* category, const char* section, const char* test_name, int num)
{
	string tmp_path = to_string(num);
	tmp_path.insert(0, Directories::Test::folder_test(category, section, test_name));
	return tmp_path;
}

string dir_an_path::Path::Test::Section::path_section_list(const char* category)
{
	return Directories::Test::Category::folder_category(category) + "sections.txt";;
}

string dir_an_path::Path::Test::Category::path_category_list()
{
	return Directories::Test::Category::dir_categories() + R"(categories.txt)";
}

void dir_an_path::creating_directories()
{
	try
	{
		/*Main Directory*/
		fs::create_directory(Directories::main_directory());
	}
	catch (...)
	{
		string error_text = "Directory create \nPath";
		error_text += dir_an_path::Directories::main_directory();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
	try
	{
		/*Admin data save directory*/
		fs::create_directories(Directories::Admin::folder_admin_data());
	}
	catch (...)
	{
		string error_text = "Directory create \nPath";
		error_text += Directories::Admin::folder_admin_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
	try
	{
		/*Accounts save directory*/
		fs::create_directories(Directories::User::dir_sv_accounts());
	}
	catch (...)
	{
		string error_text = "Directory create \nPath";
		error_text += Directories::User::dir_sv_accounts();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
	try
	{
		/*Test save directory*/
		fs::create_directories(Directories::Test::dir_sv_tests());
	}
	catch (...)
	{
		string error_text = "Directory create \nPath";
		error_text += Directories::Test::dir_sv_tests();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
	try
	{
		/*Category save directory*/
		fs::create_directories(Directories::Test::Category::dir_categories());
	}
	catch (...)
	{
		string error_text = "Directory create \nPath";
		error_text += Directories::Test::Category::dir_categories();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

bool dir_an_path::remove_all_directory()
{
	return fs::remove_all(Directories::main_directory());
}