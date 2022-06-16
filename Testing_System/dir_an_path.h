#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <conio.h>

using namespace std;

namespace fs = filesystem;

namespace dir_an_path
{
	void creating_directories();

	bool remove_all_directory();

	namespace Directories
	{
		string main_directory();  // Main Directory of Program : C:\Users\"username"\Documents\Testing System\...

		namespace Admin
		{
			string folder_admin_data(); // Admin save folder : C:\Users\"username"\Documents\Testing System\Admin\...
		}

		namespace User
		{
			string dir_sv_accounts(); // Directory save accounts : C:\Users\"username"\Documents\Testing System\Accounts\..

			string save_user_folder(const char*); // user data folder : C:\Users\"username"\Documents\Testing System\Accounts\'login
		}

		namespace Test
		{
			string dir_sv_tests(); // Directory save Tests(Category,Section,Tests) : C:\Users\"username"\Documents\Testing System\Tests...

			string folder_test(const char* category, const char* section, const char* test_name); // Test data folder : C:\Users\"username"\Documents\Testing System\Tests\Category(name)\Section(name)\Test(test_name)\...

			namespace Category
			{
				string dir_categories(); // Directory save categories : C:\Users\"username"\Documents\Testing System\Tests\Category\...

				string folder_category(const char*); // Folder Category (char* category) : C:\Users\"username"\Documents\Testing System\Category\Category(name)\...
			}

			namespace Section
			{
				string folder_section(const char*, const char*); // Folder Section(char* section) : C:\Users\"username"\Documents\Testing System\Tests\Category(name)\Section(name)\...
			}
		}
	}

	namespace Path
	{
		namespace Admin
		{
			string path_sv_adm_data(); // Path saving Admin Data : C:\Users\"username"\Documents\Testing System\Admin\AdminData.txt

			string path_adm_enc_key(); // Admin data encryption key path : C:\Users\"username"\Documents\Testing System\Admin\enc_key.txt
		}

		namespace User
		{
			string path_list_logins(); // the path to the list of user logins : C:\Users\"username"\Documents\Testing System\Accounts\logins.txt

			string path_sv_user_acc(const char*); // path to save the user account : C:\Users\"username"\Documents\Testing System\Accounts\Account(name)\AccountData(name).Tes

			string path_acc_enc_key(const char*); // the path to the encryption key from the user account (char* login) : C:\Users\"username"\Documents\Testing System\Accounts\Account(name)\enc_key.txt
		}

		namespace Test
		{
			string path_test_list(const char* category, const char* section); // location saving a list of tests

			string path_sv_n_questions(const char* category, const char* section, const char* test_name); // location saving a number questions

			string path_sv_questions(const char* category, const char* section, const char* test_name, int num); // path saving questions

			namespace Category
			{
				string path_category_list(); // the path to the list of categories
			}

			namespace Section
			{
				string path_section_list(const char*); // the path to the list of categories (char* category)
			}
		}
	}
}
