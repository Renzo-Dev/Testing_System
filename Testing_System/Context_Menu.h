#pragma once
#include "Local_Database.h"

class Context_Menu : protected Local_Database
{
public:

	Context_Menu(); // // Constructor -> Local_Database

	void main_menu();  // Context main menu

	/* menu_authorization */
	bool menu_authorization();
	// If you enter the correct data of the
	// administrator, you will enter the Admin Menu
	// Entering correct user data will bring you to the User Menu

	~Context_Menu(); // Destructor -> Local_Database

private:

	static void show_time_an_date(); // display the local time on the screen

	class User_Context
	{
	public:

		class User_Menu
		{
		public:
			static void user_menu(Account& user);  // User Menu
		private:
			class User_Profile
			{
			public:
				static void profile_information(Account& user); // Show Profile , Change profile_information data
			};
		};

		User_Context(); // Default Destructor

		~User_Context(); // Default Destructor
	};
public:
	class Admin_Context
	{
	public:

		class Admin_Menu
		{
			// friend class
			friend class User_Context::User_Menu;

		public:
			static void admin_menu(Local_Database& lc_database); // Admin Menu
		private:

			class Admin_Setting
			{
			public:
				static void admin_settings(Admin& obj); // Admin Stetting (Show Admin Data,change admin data)
			private:

				static void show_adm_data(const Admin& obj); // show admin data

				static void change_adm_data(Admin& obj); // change admin data

				static void change_password(Admin& obj); // change_adm_data-> change password

				static void change_key_recovery(Admin& obj); // change_adm_data-> change key recovery
			};

			class User_Management
			{
			public:
				// friend class
				friend class User_Context::User_Menu;

				static void user_management(set<string>& logins_); // User management menu
			private:

				static bool find_user(set<string>& logins_, bool type); // Find a user, acc_management_menu, 2 - delete account

				static void show_all_users(set<string>& logins_); // Show All Users(logins)

				class Account_management
				{
					// friend class
					friend class User_Context::User_Menu;

				public:
					static void acc_management_menu(const string& login, set<string>& logins); // Account Management Menu

					static bool delete_account(const string& login, set<string>& logins);  // Delete Account (menu)

				private:
					static void view_details(const string& login);  // Show all data by user

					class Change_Details
					{
					public:

						static void change_data(const string& login); // User data change menu
					private:

						//
						static void change_personal_Information(const string& login);  // Change personal information
						static void change_date_of_birth(const string& login);   // Change user's date of birth
						static void change_place_of_residence(const string& login);    // Change a user's place of residence
						static void change_contact_Information(const string& login);   // Change user's contact information

						//
						static void change_name(const string& login);  // menu changing name(Account(*no login))
						static void change_surname(const string& login);  // menu changing surname
						static void change_patronymic(const string& login); // menu changing patronymic

						//
						static void change_city(const string& login);  // menu changing city
						static void change_country(const string& login); // menu changing Country

						//
						static void change_email(const string& login);   // menu changing email
						static void change_phone_n(const string& login); // menu changing Phone Number
					};
				};
			};
		public:
			class Test_Management
			{
			public:
				static void test_management_menu();  // Test management menu (Assign,Create,Edit,Delete)

				static void edit_menu(const char* category, const char* section, string test); // test change menu

			private:

				static void change_test_name(const char* category, const char* section, Test& obj);

				static void change_number_questions(const char* category, const char* section, Test& obj);

				static void change_question(const char* category, const char* section, Test& obj);
			};
		};

		~Admin_Context();
	};

	class Creating_Menu
	{
	public:
		static bool create_adm_acc(Admin& admin);  // context menu to create an admin account

		static void creating_user_account(Context_Menu& lc_database); // context menu to create an User account
	};
};