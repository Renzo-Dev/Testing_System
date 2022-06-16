#include "Context_Menu.h"
#include <regex>

Context_Menu::Context_Menu()
{
	if (strlen(this->admin_.login) > 0 && strlen(this->admin_.password) > 0)
	{
		main_menu();
	}
	else
	{
		if (Creating_Menu::create_adm_acc(this->admin_) == true)
		{
			main_menu();
		}
		else
		{
			return;
		}
	}
}

void Context_Menu::main_menu()
{
	char move_choose = '1'; // To switch to right to left

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(200));
		system("cls");
		show_time_an_date();
		switch (move_choose)
		{
		case '1':
		{
			cout << "\n\t\t\t\t----------------------------------------------------\n";
			cout << "\t\t\t\t|\033[94mCONTROL\033[97m| \033[95mLEFT   RIGHT \033[97m| Select - \033[92mENT \033[97m| Exit - \033[91mESC \033[97m|\n";
			cout << "\t\t\t\t----------------------------------------------------\n";
			cout << "\n\n\n\t\t\t\t\t\t----------------------\n";
			cout << "\t\t\t\t\t\t|   \033[36mTesting System\033[97m   |\n";
			cout << "\t\t\t\t\t\t----------------------\n";
			cout << "\t\t\t\t\t\t| \033[96mSign   \033[97m\033[104mIn\033[0m \033[97m/ \033[92mUp\033[97m     |";
			cout << " \033[33mSign in to account\033[0m\n";
			cout << "\t\t\t\t\t\t----------------------\n";
		}break;
		case '2':
		{
			cout << "\n\t\t\t\t----------------------------------------------------\n";
			cout << "\t\t\t\t|\033[94mCONTROL\033[97m| \033[95mLEFT   RIGHT \033[97m| Select - \033[92mENT \033[97m| Exit - \033[91mESC \033[97m|\n";
			cout << "\t\t\t\t----------------------------------------------------\n";
			cout << "\n\n\n\t\t\t\t\t\t----------------------\n";
			cout << "\t\t\t\t\t\t|   \033[36mTesting System\033[97m   |\n";
			cout << "\t\t\t\t\t\t----------------------\n";
			cout << "\t\t\t\t\t\t| \033[96mSign   \033[33mIn \033[97m/ \033[97m\033[104mUp\033[0m\033[97m     |";
			cout << " \033[92mAccount registration\033[0m\n";
			cout << "\t\t\t\t\t\t----------------------\n";
		}break;
		default:;
		}
		if (_kbhit())
		{
			const char choose = _getch();

			if (static_cast<int> (choose) == RIGHT)
			{
				move_choose = '2';
			}
			if (static_cast<int> (choose) == LEFT)
			{
				move_choose = '1';
			}
			if (static_cast<int> (choose) == ESC)
			{
				return;
			}
			if (static_cast<int> (choose) == ENTER)
			{
				if (move_choose == '1')
				{
					menu_authorization();
				}
				if (move_choose == '2')
				{
					Creating_Menu::creating_user_account(*this);
				}
			}
		}
	}
}

bool Context_Menu::menu_authorization()
{
	char move = '1';
	char choose;

	char* tmp_login = new char[login_len];
	tmp_login[0] = '\0';
	char* tmp_password = new char[pass_len];
	tmp_password[0] = '\0';

	bool a = false;

	while (true)
	{
		switch (move)
		{
		case '1':  // Entering a login
		{
			for (size_t i = strlen(tmp_login);;)
			{
				// Show
				system("cls");
				cout << "\t\t\t     \033[97m----------------------------------------------------------------\n";
				cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
				cout << "\t\t\t     ----------------------------------------------------------------\n";
				cout << "\n\n\n\n\t\t\t\t\t           -------------------\n";
				cout << "\t\t\t\t\t           | \033[96mTesting  System\033[97m |\n";
				cout << "\t\t\t\t\t           -------------------\n";
				cout << "\t\t\t\t\t           |  \033[95mAuthorization\033[97m  |\n";
				cout << "\t\t\t\t\t     -------------------------------\n";
				cout << "\t\t\t\t\t    \033[104m\033[97m" << char(26) << "\033[0m\033[97m| \033[33mLogin\033[97m: " << tmp_login << setw(23 - strlen(tmp_login)) << " |\n";
				cout << "\t\t\t\t\t     | \033[32mPassword\033[97m: ";
				for (size_t e = 0; e < strlen(tmp_password); e++)
				{
					if (e < 15)
					{
						cout << "*";
					}
					else
					{
						cout << ".."; break;
					}
				}
				if (strlen(tmp_password) <= 15)
				{
					cout << setw(20 - strlen(tmp_password)) << " |\n";
				}
				else
				{
					cout << setw(3) << " | [" << i << "]\n";
				}
				cout << "\t\t\t\t\t     -------------------------------\n";
				cout << "\t\t\t\t\t               | \033[94mLog  in \033[97m|\n";
				cout << "\t\t\t\t\t               -----------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && a == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
					{
						if (i < login_len - 1)
						{
							tmp_login[i] = choose;
							++i;
							tmp_login[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							tmp_login[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							delete[] tmp_login;
							delete[] tmp_password;
							return false;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && a == false) // if user typed key_down // first_key_down -32
				{
					a = true;
				}
				if (static_cast<int> (choose) == RIGHT && a == true)
				{
					a = false;
				}
				if (static_cast<int> (choose) == LEFT && a == true)
				{
					a = false;
				}
				if (static_cast<int> (choose) == UP && a == true)
				{
					a = false;
				}
				if (static_cast<int> (choose) == DOWN && a == true)  // second_key_down 80
				{
					a = false;
					move = '2';
					break;
				}
			}
		}break;
		case '2':
		{
			for (size_t i = strlen(tmp_password);;)
			{
				// Show
				system("cls");
				cout << "\t\t\t     ----------------------------------------------------------------\n";
				cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
				cout << "\t\t\t     ----------------------------------------------------------------\n";
				cout << "\n\n\n\n\t\t\t\t\t           -------------------\n";
				cout << "\t\t\t\t\t           | \033[96mTesting  System\033[97m |\n";
				cout << "\t\t\t\t\t           -------------------\n";
				cout << "\t\t\t\t\t           |  \033[95mAuthorization\033[97m  |\n";
				cout << "\t\t\t\t\t     -------------------------------\n";
				cout << "\t\t\t\t\t     | \033[33mLogin\033[97m: " << tmp_login << setw(23 - strlen(tmp_login)) << " |\n";
				cout << "\t\t\t\t\t    \033[104m\033[97m" << char(26) << "\033[0m\033[97m| \033[32mPassword\033[97m: ";

				for (size_t e = 0; e < strlen(tmp_password); e++)
				{
					if (e < 15)
					{
						cout << "*";
					}
					else
					{
						cout << ".."; break;
					}
				}
				if (strlen(tmp_password) <= 15)
				{
					cout << setw(20 - strlen(tmp_password)) << " |\n";
				}
				else
				{
					cout << setw(3) << " | [" << i << "]\n";
				}
				cout << "\t\t\t\t\t     -------------------------------\n";
				cout << "\t\t\t\t\t               | \033[94mLog  in \033[97m|\n";
				cout << "\t\t\t\t\t               -----------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && a == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '!' || choose == '@' || choose == '#' || choose == '%')
					{
						if (i < pass_len - 1)
						{
							tmp_password[i] = choose;
							++i;
							tmp_password[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							tmp_password[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							delete[] tmp_login;
							delete[] tmp_password;
							return false;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && a == false) // if user typed key_down // key =  -32
				{
					a = true;
				}
				if (static_cast<int> (choose) == RIGHT && a == true)
				{
					a = false;
				}
				if (static_cast<int> (choose) == LEFT && a == true)
				{
					a = false;
				}
				if (static_cast<int> (choose) == UP && a == true) // second_key_down 72
				{
					a = false;
					move = '1';
					break;
				}
				if (static_cast<int> (choose) == DOWN && a == true)  // second_key_down 80
				{
					a = false;
					move = '3';
					break;
				}
			}
		}break;
		case '3':
		{
			system("cls");
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\n\n\n\n\t\t\t\t\t           -------------------\n";
			cout << "\t\t\t\t\t           | \033[96mTesting  System\033[97m |\n";
			cout << "\t\t\t\t\t           -------------------\n";
			cout << "\t\t\t\t\t           |  \033[95mAuthorization\033[97m  |\n";
			cout << "\t\t\t\t\t     -------------------------------\n";
			cout << "\t\t\t\t\t     | \033[33mLogin\033[97m: " << tmp_login << setw(23 - strlen(tmp_login)) << " |\n";
			cout << "\t\t\t\t\t     | \033[32mPassword\033[97m: ";

			for (size_t e = 0; e < strlen(tmp_password); e++)
			{
				if (e < 15)
				{
					cout << "*";
				}
				else
				{
					cout << ".."; break;
				}
			}
			if (strlen(tmp_password) <= 15)
			{
				cout << setw(20 - strlen(tmp_password)) << " |\n";
			}
			else
			{
				cout << setw(3) << " |\n";
			}
			cout << "\t\t\t\t\t     -------------------------------\n";
			cout << "\t\t\t\t\t               | \033[104m\033[97mLog  in\033[0m \033[97m|\n";
			cout << "\t\t\t\t\t               -----------\n";

			choose = _getch();
			if (static_cast<int> (choose) == UP)
			{
				move = '2';
				break;
			}
			if (static_cast<int> (choose) == ESC)
			{
				delete[] tmp_login;
				delete[] tmp_password;
				return false;
			}
			if (static_cast<int> (choose) == ENTER && strlen(tmp_password) > 4 && strlen(tmp_login) > 3)
			{
				// Admin authentication
				if (strcmp(tmp_login, this->admin_.login) == 0)  // login check , with admin login
				{
					if (strcmp(tmp_password, this->admin_.password) == 0) // If it is correct, it allows you to enter the admin menu
					{
						// Admin Menu
						Admin_Context::Admin_Menu::admin_menu(*this);
						return false;
					}
					else   // If the administrator entered the wrong password
					{
						while (true)
						{
							system("cls");
							cout << "\n\n\n\n\t\t\t\t\t---------------------------------------------\n";
							cout << "\t\t\t\t\t| \033[95mLogging in to the \033[92mAdministrator's \033[96maccount \033[97m|\n";
							cout << "\t\t\t\t\t---------------------------------------------\n";
							cout << "\t\t\t\t\t             | \033[91mWrong \033[94mpassword \033[97m|\n";
							cout << "\t\t\t\t\t -------------------------------------------\n";
							cout << "\t\t\t\t\t | \033[33mPress \033[97m[\033[95mAnyButton\033[97m]  \033[94mto enter again       \033[97m|\n";
							cout << "\t\t\t\t\t | \033[33mPress    \033[97m[\033[95mESC\033[97m] \033[94mto exit to the main menu \033[97m|\n";
							cout << "\t\t\t\t\t | \033[33mPress   \033[97m[\033[95mENTER\033[97m]  \033[94mto restore the account \033[97m|\n";
							cout << "\t\t\t\t\t -------------------------------------------\n";
							choose = _getch();
							if (static_cast<int>(choose) == ESC)
							{
								delete[] tmp_login;
								delete[] tmp_password;
								return false;
							}
							if (static_cast<int>(choose) == ENTER)
							{
								// Recovery

								if (this->recovery_admin_account() == false)
								{
									delete[] tmp_login;
									delete[] tmp_password;
									return false;
								}
								else
								{
									delete[] tmp_login;
									delete[] tmp_password;

									Creating_Menu::create_adm_acc(this->admin_);
									return true;
								}
							}
							else
							{
								break;
							}
						}
					}
				}
				else
				{
					// user authentication
					for (auto it : this->logins_)
					{
						if (strcmp(tmp_login, it.c_str()) == 0)
						{
							Account temp;
							Local_Database::load_user_data(it, temp);
							if (strcmp(tmp_password, temp.password) == 0)
							{
								User_Context::User_Menu::user_menu(temp);
								return false;
							}
						}
					}
					system("cls");
					cout << "\t\t\t     ----------------------------------------------------------------\n";
					cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t     ----------------------------------------------------------------\n";
					cout << "\n\n\n\n\t\t\t\t\t           -------------------\n";
					cout << "\t\t\t\t\t           | \033[96mTesting  System\033[97m |\n";
					cout << "\t\t\t\t\t           -------------------\n";
					cout << "\t\t\t\t\t           |  \033[95mAuthorization\033[97m  |\n";
					cout << "\t\t\t\t\t     -------------------------------\n";
					cout << "\t\t\t\t\t     | \033[33mLogin\033[97m: " << tmp_login << setw(23 - strlen(tmp_login)) << " |\n";
					cout << "\t\t\t\t\t     | \033[32mPassword\033[97m: ";

					for (size_t e = 0; e < strlen(tmp_password); e++)
					{
						if (e < 15)
						{
							cout << "*";
						}
						else
						{
							cout << ".."; break;
						}
					}
					if (strlen(tmp_password) <= 15)
					{
						cout << setw(20 - strlen(tmp_password)) << " |\n";
					}
					else
					{
						cout << setw(3) << " |\n";
					}
					cout << "\t\t\t\t\t     -------------------------------\n";
					cout << "\t\t\t\t\t               | \033[104m\033[97mLog  in\033[0m \033[97m|\n";
					cout << "\t\t\t\t\t               -----------\n\n";
					cout << "\t\t\t\t\t     -------------------------------\n";
					cout << "\t\t\t\t\t     | \033[91mIncorrect \033[94mlogin \033[96mor \033[94mpassword \033[97m|\n";
					cout << "\t\t\t\t\t     -------------------------------\n";
					this_thread::sleep_for(chrono::seconds(2));
				}
			}
		}break;
		default:;
		}
	}
}

void Context_Menu::User_Context::User_Menu::user_menu(Account& user)
{
	char move = '1';
	char choose;
	system("cls");
	cout << "\n\n\n\n\t\t\033[92mSuccessfully logged into \033[96myour account\033[97m";
	this_thread::sleep_for(chrono::seconds(1));
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\033[92mSuccessfully logged into \033[96myour account\033[97m";
	this_thread::sleep_for(chrono::seconds(1));
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\033[92mSuccessfully logged into \033[96myour account\033[97m";
	this_thread::sleep_for(chrono::seconds(1));

	while (true)
	{
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n\n";

		cout << "\t\t\t\t\t      ------------------------------\n";
		cout << "\t\t\t\t\t      | \033[33mUser\033[97m: " << user.login << setw(static_cast<streamsize>(login_len - strlen(user.login)) + 2) << " |\n";
		cout << "\t\t\t\t\t      ------------------------------\n\n\n";
		cout << "\t\t\t\t\t              --------------\n";
		cout << "\t\t\t\t\t              | \033[94mUser  \033[94mMenu\033[97m |\n";
		cout << "\t\t\t\t\t              --------------\n";

		if (move == '1')
		{
			cout << "\t\t\t\t\t              |  \033[102mProfile\033[0m   \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[95mTest      \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[96mStatics   \033[97m|\n";
			cout << "\t\t\t\t\t              --------------\n";
		}
		if (move == '2')
		{
			cout << "\t\t\t\t\t              |  \033[92mProfile   \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[105mTest\033[0m      \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[96mStatics   \033[97m|\n";
			cout << "\t\t\t\t\t              --------------\n";
		}
		if (move == '3')
		{
			cout << "\t\t\t\t\t              |  \033[92mProfile   \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[95mTest      \033[97m|\n";
			cout << "\t\t\t\t\t              |  \033[106mStatics\033[0m   \033[97m|\n";
			cout << "\t\t\t\t\t              --------------\n";
		}

		choose = _getch();
		if (static_cast<int> (choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
		}
		if (static_cast<int> (choose) == UP)
		{
			if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int> (choose) == ESC)
		{
			return;
		}
		if (static_cast<int> (choose) == ENTER)
		{
			if (move == '1')  //
			{
				User_Profile::profile_information(user);
			}
			else if (move == '2')
			{
			}
			else if (move == '3')
			{
			}
		}
	}
}

void Context_Menu::User_Context::User_Menu::User_Profile::profile_information(Account& user)
{
	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";

		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t\t        -----------\n";
			cout << "\t\t\t\t\t\t        | \033[92mProfile\033[97m |\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
			cout << "\t\t\t\t\t\t     \033[104m" << char(26) << "\033[0m\033[97m| \033[93mShow   \033[94mData \033[97m|\n";
			cout << "\t\t\t\t\t\t      | \033[96mChange \033[94mData \033[97m|\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t        -----------\n";
			cout << "\t\t\t\t\t\t        | \033[92mProfile\033[97m |\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
			cout << "\t\t\t\t\t\t      | \033[93mShow   \033[94mData \033[97m|\n";
			cout << "\t\t\t\t\t\t     \033[104m" << char(26) << "\033[0m\033[97m| \033[96mChange \033[94mData \033[97m|\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
		}break;
		default:;
		}

		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				Admin_Context::Admin_Menu::User_Management::Account_management::view_details(user.login);
			}
			else if (move == '2')
			{
				Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_data(user.login);
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
	}
}

Context_Menu::User_Context::User_Context()
= default;

Context_Menu::User_Context::~User_Context()
= default;

void Context_Menu::Admin_Context::Admin_Menu::admin_menu(Local_Database& lc_database)
{
	char move = '1';
	char choose;
	bool key_st = false;

	while (true)
	{
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\n\n\n\t\t\t\t\t\t       --------------\n";
		cout << "\t\t\t\t\t\t       | \033[96mAdmin Menu \033[97m|\n";
		cout << "\t\t\t\t\t\t    --------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t\t   \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[33mAdmin \033[94mSetting    \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[92mUser  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[91mTest  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[96mStats \033[94mof Users   \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t    | \033[33mAdmin \033[94mSetting    \033[97m|\n";
			cout << "\t\t\t\t\t\t   \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[92mUser  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[91mTest  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[96mStats \033[94mof Users   \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t\t    | \033[33mAdmin \033[94mSetting    \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[92mUser  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t   \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[91mTest  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[96mStats \033[94mof Users   \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		case '4':
		{
			cout << "\t\t\t\t\t\t    | \033[33mAdmin \033[94mSetting    \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[92mUser  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[91mTest  \033[94mManagement \033[97m|\n";
			cout << "\t\t\t\t\t\t   \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[96mStats \033[94mof Users   \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		}

		choose = _getch();

		if (static_cast<int> (choose) == ENTER)
		{
			if (move == '1')
			{
				Admin_Setting::admin_settings(lc_database.admin_);
			}
			else if (move == '2')
			{
				User_Management::user_management(lc_database.logins_);
			}
			else if (move == '3')
			{
				Test_Management::test_management_menu();
			}
			else if (move == '4')
			{
			}
		}
		if (static_cast<int> (choose) == -32 && key_st == false) // if user typed key_down // key =  -32
		{
			key_st = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == LEFT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == UP && key_st == true) // second_key_down 72
		{
			if (move == '1')
			{
				key_st = false;
			}
			else if (move == '2')
			{
				key_st = false;
				move = '1';
			}
			else if (move == '3')
			{
				key_st = false;
				move = '2';
			}
			else if (move == '4')
			{
				key_st = false;
				move = '3';
			}
		}
		if (static_cast<int> (choose) == DOWN && key_st == true)  // second_key_down 80
		{
			if (move == '1')
			{
				key_st = false;
				move = '2';
			}
			else if (move == '2')
			{
				key_st = false;
				move = '3';
			}
			else if (move == '3')
			{
				key_st = false;
				move = '4';
			}
			else if (move == '4')
			{
				key_st = false;
			}
		}
		if (static_cast<int> (choose) == ESC)
		{
			return;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Admin_Setting::admin_settings(Admin& obj)
{
	// show admin data // /change admin data

	char choose;
	char move = '1';
	bool key_st = false;

	while (true)
	{
		switch (move)
		{
		case'1':
		{
			system("cls");
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\n\n\n\t\t\t\t\t\t     -----------------\n";
			cout << "\t\t\t\t\t\t     | \033[33mAdmin Setting \033[97m|  \n";
			cout << "\t\t\t\t\t\t   ---------------------\n";
			cout << "\t\t\t\t\t\t  \033[104m" << char(26) << "\033[0m\033[97m| \033[93mShow \033[94mAdmin Data  \033[97m |\n";
			cout << "\t\t\t\t\t\t   | \033[95mChange \033[94mAdmin Data \033[97m|\n";
			cout << "\t\t\t\t\t\t   ---------------------\n";
		}break;
		case '2':
		{
			system("cls");
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
			cout << "\t\t\t     ----------------------------------------------------------------\n";
			cout << "\n\n\n\t\t\t\t\t\t     -----------------\n";
			cout << "\t\t\t\t\t\t     | \033[33mAdmin Setting \033[97m|  \n";
			cout << "\t\t\t\t\t\t   ---------------------\n";
			cout << "\t\t\t\t\t\t   | \033[93mShow \033[94mAdmin Data  \033[97m |\n";
			cout << "\t\t\t\t\t\t  \033[104m" << char(26) << "\033[0m\033[97m| \033[95mChange \033[94mAdmin Data \033[97m|\n";
			cout << "\t\t\t\t\t\t   ---------------------\n";
		}break;
		default:;
		}

		choose = _getch();
		if (static_cast<int> (choose) == ENTER)
		{
			if (move == '1')
			{
				show_adm_data(obj);
			}
			else if (move == '2')
			{
				change_adm_data(obj);
			}
		}
		if (static_cast<int> (choose) == -32 && key_st == false) // if user typed key_down // key =  -32
		{
			key_st = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == LEFT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == UP && key_st == true) // second_key_down 72
		{
			if (move == '1')
			{
				key_st = false;
			}
			else if (move == '2')
			{
				key_st = false;
				move = '1';
			}
		}
		if (static_cast<int> (choose) == DOWN && key_st == true)  // second_key_down 80
		{
			if (move == '1')
			{
				key_st = false;
				move = '2';
			}
			else if (move == '2')
			{
				key_st = false;
			}
		}
		if (static_cast<int> (choose) == ESC)
		{
			return;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::user_management(set<string>& logins_)
{
	char choose;
	char move = '1';

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";
		cout << "\t\t\t\t\t            --------------------\n";
		cout << "\t\t\t\t\t            | \033[33mUser  \033[94mManagement\033[97m |\n";
		cout << "\t\t\t\t\t         --------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t        \033[104m" << char(26) << "\033[0m\033[97m|1| \033[93mShow    \033[94mall Users    \033[97m|\n";
			cout << "\t\t\t\t\t         |2| \033[92mChange  \033[94mUser details \033[97m|\n";
			cout << "\t\t\t\t\t         |3| \033[95mFind    \033[94ma User       \033[97m|\n";
			cout << "\t\t\t\t\t         |4| \033[91mDelete  \033[94mUser(s)      \033[97m|\n";
			cout << "\t\t\t\t\t         --------------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t         |1| \033[93mShow    \033[94mall Users    \033[97m|\n";
			cout << "\t\t\t\t\t        \033[104m" << char(26) << "\033[0m\033[97m|2| \033[92mChange  \033[94mUser details \033[97m|\n";
			cout << "\t\t\t\t\t         |3| \033[95mFind    \033[94ma User       \033[97m|\n";
			cout << "\t\t\t\t\t         |4| \033[91mDelete  \033[94mUser(s)      \033[97m|\n";
			cout << "\t\t\t\t\t         --------------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t         |1| \033[93mShow    \033[94mall Users    \033[97m|\n";
			cout << "\t\t\t\t\t         |2| \033[92mChange  \033[94mUser details \033[97m|\n";
			cout << "\t\t\t\t\t        \033[104m" << char(26) << "\033[0m\033[97m|3| \033[95mFind    \033[94ma User       \033[97m|\n";
			cout << "\t\t\t\t\t         |4| \033[91mDelete  \033[94mUser(s)      \033[97m|\n";
			cout << "\t\t\t\t\t         --------------------------\n";
		}break;
		case '4':
		{
			cout << "\t\t\t\t\t         |1| \033[93mShow    \033[94mall Users    \033[97m|\n";
			cout << "\t\t\t\t\t         |2| \033[92mChange  \033[94mUser details \033[97m|\n";
			cout << "\t\t\t\t\t         |3| \033[95mFind    \033[94ma User       \033[97m|\n";
			cout << "\t\t\t\t\t        \033[104m" << char(26) << "\033[0m\033[97m|4| \033[91mDelete  \033[94mUser(s)      \033[97m|\n";
			cout << "\t\t\t\t\t         --------------------------\n";
		}break;
		default:;
		}
		choose = _getch();
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				show_all_users(logins_);
			}
			else if (move == '2')
			{
				if (logins_.size() > 0)
				{
					find_user(logins_, true);
				}
				else
				{
					cout << "\n\t\t\t\t\t      \033[91mThere are no users in the database\033[97m!\n";
					this_thread::sleep_for(chrono::seconds(1));
				}
			}
			else if (move == '3')
			{
				if (logins_.size() > 0)
				{
					find_user(logins_, true);
				}
				else
				{
					cout << "\n\t\t\t\t\t      \033[91mThere are no users in the database\033[97m!\n";
					this_thread::sleep_for(chrono::seconds(1));
				}
			}
			else if (move == '4')
			{
				if (logins_.size() > 0)
				{
					move = '1';
					while (true)
					{
						system("cls");
						cout << "\t\t\t     ----------------------------------------------------------------\n";
						cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
						cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";
						cout << "\t\t\t\t\t\t  -------------------\n";
						cout << "\t\t\t\t\t\t  | \033[91mDelete  \033[92mUser(s)\033[97m |\n";
						switch (move)
						{
						case '1':
						{
							cout << "\t\t\t\t\t\t-----------------------\n";
							cout << "\t\t\t\t\t       \033[104m" << char(26) << "\033[0m\033[97m| \033[94mDelete \033[33mAccount \033[97m     |\n";
							cout << "\t\t\t\t\t\t| \033[94mDelete \033[31mAll \033[33mAccounts\033[97m |\n";
							cout << "\t\t\t\t\t\t-----------------------\n";
						}break;
						case '2':
						{
							cout << "\t\t\t\t\t\t-----------------------\n";
							cout << "\t\t\t\t\t\t| \033[94mDelete \033[33mAccount \033[97m     |\n";
							cout << "\t\t\t\t\t       \033[104m" << char(26) << "\033[0m\033[97m| \033[94mDelete \033[31mAll \033[33mAccounts\033[97m |\n";
							cout << "\t\t\t\t\t\t-----------------------\n";
						}break;
						default:;
						}
						choose = _getch();
						if (static_cast<int>(choose) == ESC)
						{
							move = '4';
							break;
						}
						if (static_cast<int>(choose) == DOWN)
						{
							move = '2';
						}
						if (static_cast<int>(choose) == UP)
						{
							move = '1';
						}
						if (static_cast<int>(choose) == ENTER)
						{
							if (move == '1')
							{
								find_user(logins_, false);
							}
							if (move == '2')
							{
								move = '2';
								while (true)
								{
									system("cls");
									cout << "\t\t\t    -------------------------------------------------------------------\n";
									cout << "\t\t\t    |\033[94mCONTROL\033[97m| \033[95mLeft   Right \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
									cout << "\t\t\t    -------------------------------------------------------------------\n\n\n\n\n";
									cout << "\t\t\t\t----------------------------------------------------------\n";
									cout << "\t\t\t\t|  \033[91mWarning    Warning    Warning     Warning    Warning  \033[97m|\n";
									cout << "\t\t\t\t----------------------------------------------------------\n";
									cout << "\t\t\t\t| \033[96mDo you really want to \033[31mdelete \033[93mall users without return\033[97m? |\n";
									cout << "\t\t\t\t==========================================================\n";
									switch (move)
									{
									case '1':
									{
										cout << "\t\t\t\t           |      \033[97m\033[102mYes\033[0m                 \033[91mNo      \033[97m|\n";
										cout << "\t\t\t\t           ------------------------------------\n";
									}break;
									case '2':
									{
										cout << "\t\t\t\t           |      \033[92mYes                 \033[97m\033[101mNo\033[0m      \033[97m|\n";
										cout << "\t\t\t\t           ------------------------------------\n";
									}break;
									default:;
									}
									choose = _getch();
									if (static_cast<int>(choose) == ESC)
									{
										break;
									}
									if (static_cast<int>(choose) == ENTER)
									{
										if (move == '2')
										{
											break;
										}
										if (move == '1')
										{
											DeleteFileA(dir_an_path::Path::User::path_list_logins().c_str());
											thread th_del([&logins_]
												{
													auto it = logins_.begin();
													for (int i = 0; i < logins_.size(); i++)
													{
														fs::remove_all(dir_an_path::Directories::User::save_user_folder(it->c_str()));
														it++;
													}
												});
											system("cls");
											cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t           --------------------------------------\n";
											cout << "\t\t\t\t           | \033[94mData has been Successfully \033[31mdeleted \033[97m| \n";
											cout << "\t\t\t\t           --------------------------------------\n";
											this_thread::sleep_for(chrono::seconds(2));
											th_del.join();
											logins_.clear();
											return;
										}
									}
									if (static_cast<int>(choose) == LEFT)
									{
										move = '1';
									}
									if (static_cast<int>(choose) == RIGHT)
									{
										move = '2';
									}
								}
							}
						}
					}
				}
				else
				{
					cout << "\n\t\t\t\t\t      \033[91mThere are no users in the database\033[97m!\n";
					this_thread::sleep_for(chrono::seconds(1));
				}
			}
		}
		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '4';
			}
			else
			{
				move = '4';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '4')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
			else
			{
				move = '1';
			}
		}
	}
}

bool Context_Menu::Admin_Context::Admin_Menu::User_Management::find_user(set<string>& logins_, bool type)
{
	char move = '1';
	char choose;
	while (true)
	{
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";

		cout << "\t\t\t\t\t\t      ---------------\n";
		cout << "\t\t\t\t\t\t      | \033[96mSearch \033[93mUser\033[97m |\n";
		cout << "\t\t\t\t\t\t      ---------------\n";
		cout << "\t\t\t\t\t\t      | \033[92mSearch \033[95mby\033[97m:  |\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t\t      ---------------\n";
			cout << "\t\t\t\t\t\t     \033[104m" << char(26) << "\033[0m\033[97m|    \033[94mLogin\033[97m    |\n";
			cout << "\t\t\t\t\t\t      |    \033[94mPhone\033[97m    |\n";
			cout << "\t\t\t\t\t\t      |    \033[94mEmail\033[97m    |\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t      ---------------\n";
			cout << "\t\t\t\t\t\t      |    \033[94mLogin\033[97m    |\n";
			cout << "\t\t\t\t\t\t     \033[104m" << char(26) << "\033[0m\033[97m|    \033[94mPhone\033[97m    |\n";
			cout << "\t\t\t\t\t\t      |    \033[94mEmail\033[97m    |\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t\t      ---------------\n";
			cout << "\t\t\t\t\t\t      |    \033[94mLogin\033[97m    |\n";
			cout << "\t\t\t\t\t\t      |    \033[94mPhone\033[97m    |\n";
			cout << "\t\t\t\t\t\t     \033[104m" << char(26) << "\033[0m\033[97m|    \033[94mEmail\033[97m    |\n";
			cout << "\t\t\t\t\t\t      ---------------\n";
		}break;
		}
		choose = _getch();

		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return false;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1') // Search by login
			{
				char* search_login = new char[login_len];
				search_login[0] = '\0';

				bool key_move = false;

				for (size_t i = strlen(search_login);;)
				{
					system("cls");
					cout << "\t\t\t\t   ----------------------------------------------------\n";
					cout << "\t\t\t\t   |\033[94mCONTROL\033[97m| \033[95mExit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t\t   ----------------------------------------------------\n\n\n\n\n";
					cout << "\t\t\t\t\t\t     -------------------\n";
					cout << "\t\t\t\t\t\t     |  \033[96mSearch   \033[93mUser\033[97m  |\n";
					cout << "\t\t\t\t\t\t     -------------------\n";
					cout << "\t\t\t\t\t\t     | \033[92mSearch \033[95mby Login\033[97m |\n";
					cout << "\t\t\t\t\t    -------------------------------------\n";
					cout << "\t\t\t\t\t    | \033[33mEnter \033[92mLogin\033[97m: " << search_login << setw(static_cast<streamsize>(login_len - strlen(search_login) + 2)) << " |\n";
					cout << "\t\t\t\t\t    -------------------------------------\n\n\n";

					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
						{
							if (i < login_len - 1)
							{
								search_login[i] = choose;
								++i;
								search_login[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								search_login[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								delete[] search_login;
								break;
							}
							if (static_cast<int>(choose) == ENTER && strlen(search_login) > 2)
							{
								if (found_user(search_login, logins_, '1') != "\0")
								{
									cout << "\t\t\t\t\t                --------------\n";
									cout << "\t\t\t\t\t                | \033[92mUser Found\033[97m |\n";
									cout << "\t\t\t\t\t                --------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									if (type == true) {
										Account_management::acc_management_menu(search_login, logins_);
									}
									else
									{
										Account_management::delete_account(search_login, logins_);
									}
									delete[] search_login;
									return false;
								}
								else
								{
									cout << "\t\t\t\t\t              ------------------\n";
									cout << "\t\t\t\t\t              | \033[92mUser \033[91mNot Found \033[97m|\n";
									cout << "\t\t\t\t\t              ------------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									delete[] search_login;
									break;
								}
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}
			if (move == '2') // Search by phone number
			{
				bool key_move = false;
				char* search_phone_number = new char[login_len];
				search_phone_number[0] = '\0';

				for (size_t i = strlen(search_phone_number);;)
				{
					system("cls");
					cout << "\t\t\t\t   ----------------------------------------------------\n";
					cout << "\t\t\t\t   |\033[94mCONTROL\033[97m| \033[95mExit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t\t   ----------------------------------------------------\n\n\n\n\n";
					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    |  \033[96mSearch   \033[93mUser\033[97m  |\n";
					cout << "\t\t\t\t\t\t   ---------------------\n";
					cout << "\t\t\t\t\t\t   | \033[92mSearch \033[95mby Phone-n\033[97m |\n";
					cout << "\t\t\t\t\t    -----------------------------------\n";
					cout << "\t\t\t\t\t    | \033[33mEnter \033[92mPhone-n\033[97m: " << search_phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(search_phone_number) + 2)) << " |\n";
					cout << "\t\t\t\t\t    -----------------------------------\n\n\n";

					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if (choose >= '0' && choose <= '9')
						{
							if (i < phone_n_length - 1)
							{
								search_phone_number[i] = choose;
								++i;
								search_phone_number[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								search_phone_number[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								delete[] search_phone_number;
								break;
							}
							if (static_cast<int>(choose) == ENTER && strlen(search_phone_number) > 6)
							{
								string tmp_login;
								tmp_login = found_user(search_phone_number, logins_, '2');
								if (tmp_login != "\0")
								{
									cout << "\t\t\t\t\t                --------------\n";
									cout << "\t\t\t\t\t                | \033[92mUser Found\033[97m |\n";
									cout << "\t\t\t\t\t                --------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									delete[] search_phone_number;
									if (type == true) {
										Account_management::acc_management_menu(tmp_login, logins_);
									}
									else
									{
										Account_management::delete_account(tmp_login, logins_);
									}
									return false;
								}
								else
								{
									cout << "\t\t\t\t\t              ------------------\n";
									cout << "\t\t\t\t\t              | \033[92mUser \033[91mNot Found \033[97m|\n";
									cout << "\t\t\t\t\t              ------------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									delete[] search_phone_number;
									break;
								}
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}
			if (move == '3') // Search by email
			{
				bool key_move = false;
				char* search_email = new char[email_length];
				search_email[0] = '\0';

				for (size_t i = strlen(search_email);;)
				{
					system("cls");
					cout << "\t\t\t\t   ----------------------------------------------------\n";
					cout << "\t\t\t\t   |\033[94mCONTROL\033[97m| \033[95mExit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t\t   ----------------------------------------------------\n\n\n\n\n";
					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    |  \033[96mSearch   \033[93mUser\033[97m  |\n";
					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    | \033[92mSearch \033[95mby Email\033[97m |\n";
					cout << "\t\t\t\t      ----------------------------------------------\n";
					cout << "\t\t\t\t      | \033[33mEnter \033[92mEmail\033[97m: " << search_email << setw(static_cast<streamsize>(email_length - strlen(search_email) + 2)) << " |\n";
					cout << "\t\t\t\t      ----------------------------------------------\n\n\n";

					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_' || choose == '@' || choose == '.')
						{
							if (i < email_length - 1)
							{
								search_email[i] = choose;
								++i;
								search_email[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								search_email[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								delete[] search_email;
								break;
							}
							if (static_cast<int>(choose) == ENTER && strlen(search_email) > 6)
							{
								string tmp_login;
								tmp_login = Local_Database::found_user(search_email, logins_, '3');
								if (tmp_login != "\0")
								{
									cout << "\t\t\t\t\t                --------------\n";
									cout << "\t\t\t\t\t                | \033[92mUser Found\033[97m |\n";
									cout << "\t\t\t\t\t                --------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									delete[] search_email;
									if (type == true) {
										Account_management::acc_management_menu(tmp_login, logins_);
									}
									else
									{
										Account_management::delete_account(tmp_login, logins_);
									}
									return false;
								}
								else
								{
									cout << "\t\t\t\t\t              ------------------\n";
									cout << "\t\t\t\t\t              | \033[92mUser \033[91mNot Found \033[97m|\n";
									cout << "\t\t\t\t\t              ------------------\n";
									this_thread::sleep_for(chrono::seconds(3));
									delete[] search_email;
									break;
								}
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::show_all_users(set<string>& logins_)
{
	if (logins_.size() > 0) {
		char choose;

		auto it = logins_.begin();

		string* login_s = new string[logins_.size()];

		for (int i = 0; i < logins_.size(); i++)
		{
			login_s[i] = it->c_str();
			it++;
		}

		int list_start = 0;
		int list_l_max;
		int select = 0;
		const int num_login_list = 15;    // the number of logins in the list on the screen

		if (logins_.size() < 10)
		{
			list_l_max = logins_.size();
		}
		else
		{
			list_l_max = num_login_list;
		}

		while (true)
		{
			this_thread::sleep_for(chrono::milliseconds(50));
			system("cls");
			cout << "\t\t\t    ----------------------------------------------------------------\n";
			cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
			cout << "\t\t\t    ----------------------------------------------------------------\n\n";
			cout << "\t\t\t\t\t\t ------------------------\n";
			cout << "\t\t\t\t\t\t |   \033[33mShow  \033[92mAll Logins   \033[97m|\n";
			cout << "\t\t\t\t\t\t ------------------------\n";

			for (int i = list_start; i < list_l_max; i++)
			{
				if (i == select)
				{
					cout << "\t\t\t\t\t\t | \033[104m" << login_s[i].c_str() << "\033[0m\033[97m" << setw(login_len - strlen(login_s[i].c_str()) + 2) << " |\n";
				}
				else
				{
					cout << "\t\t\t\t\t\t | " << login_s[i].c_str() << setw(login_len - strlen(login_s[i].c_str()) + 2) << " |\n";
				}
			}

			if ((list_l_max - list_start) < num_login_list)
			{
				for (int i = 0; i < num_login_list - (list_l_max - list_start); i++)
				{
					cout << "\t\t\t\t\t\t |                      |\n";
				}
			}

			cout << "\t\t\t\t\t\t ------------------------\n";
			cout << "\t\t\t\t\t\t US: " << select + 1 << " of " << logins_.size() << endl;
			cout << "\t\t\t\t\t\t ------------------------\n";
			cout << "\t\t\t\t\t\t PG: " << list_start / 10 + 1 << " of "; if (logins_.size() / 10 == 0) { cout << "1"; }
			else { logins_.size() / 10; }

			choose = _getch();

			if (static_cast<int>(choose) == ENTER)
			{
				Account_management::acc_management_menu(login_s[select], logins_);
				return;
			}
			if (static_cast<int>(choose) == ESC)
			{
				delete[] login_s;
				return;
			}
			if (static_cast<int>(choose) == RIGHT)
			{
				if (list_l_max != logins_.size())
				{
					if (list_l_max + num_login_list > logins_.size()) // If list length max + 10 is greater than the number of logins
					{
						list_l_max = logins_.size();
						list_start += num_login_list;
						select = list_start;
					}
					else
					{
						list_l_max += num_login_list;
						list_start += num_login_list;
						select = list_start;
					}
				}
			}
			if (static_cast<int>(choose) == LEFT)
			{
				if (list_start != 0)
				{
					if (list_l_max - num_login_list < num_login_list)
					{
						list_l_max -= list_l_max - list_start;
						list_start -= num_login_list;
						select = list_start;
					}
				}
			}

			if (static_cast<int> (choose) == DOWN)
			{
				if (select < list_l_max - 1)
				{
					select++;
				}
			}
			if (static_cast<int>(choose) == UP)
			{
				if (select > list_start)
				{
					select--;
				}
			}
		}
	}
	else
	{
		cout << "\n\t\t\t\t\t      \033[91mThere are no users in the database\033[97m!\n";
		this_thread::sleep_for(chrono::seconds(1));
		return;
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::view_details(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	system("cls");
	cout << "\t\t\t\t\t               \033[97m----------------\n";
	cout << "\t\t\t\t\t               | \033[32mView Details \033[97m|\n";
	cout << "\t\t\t\t\t       --------------------------------\n";
	cout << "\t\t\t\t\t       | \033[33mLogin \033[97m: " << acc.login << setw(static_cast<streamsize>(login_len - strlen(acc.login)) + 2) << " |\n";
	cout << "\t\t\t\t\t       --------------------------------\n";
	cout << "\t\t\t\t\t           | \033[96mPersonal Information \033[97m|      \n";
	cout << "\t\t\t\t\t    --------------------------------------\n";
	cout << "\t\t\t\t\t    | \033[92mName\033[97m: " << acc.Name << setw(static_cast<streamsize>(name_len - strlen(acc.Name)) + 10) << " |\n";
	cout << "\t\t\t\t\t    | \033[92mSurname\033[97m: " << acc.Surname << setw(static_cast<streamsize>(sur_len - strlen(acc.Surname)) + 2) << " |\n";
	cout << "\t\t\t\t\t    | \033[92mPatronymic\033[97m: " << acc.Patronymic << setw(static_cast<streamsize>(patron_len - strlen(acc.Patronymic) + 4)) << " |\n";
	cout << "\t\t\t\t\t    --------------------------------------\n";
	cout << "\t\t\t\t\t              | \033[95mDate  of Birth \033[97m|         \n";
	cout << "\t\t\t\t\t            ----------------------\n";
	cout << "\t\t\t\t\t            | \033[92mD.M.Y \033[97m:\033[93m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
	cout << "\t\t\t\t\t            ----------------------\n";
	cout << "\t\t\t\t\t            | \033[94mPlace of Residence \033[97m|\n";
	cout << "\t\t\t\t\t      ----------------------------------\n";
	cout << "\t\t\t\t\t      | \033[36mCity\033[97m: " << acc.City << setw(static_cast<streamsize>(city_length - strlen(acc.City)) + 6) << " |\n";
	cout << "\t\t\t\t\t      | \033[33mCountry\033[97m: " << acc.Country << setw(static_cast<streamsize>(country_length - strlen(acc.Country)) + 2) << " |\n";
	cout << "\t\t\t\t\t      ----------------------------------\n";
	cout << "\t\t\t\t\t           | \033[35mContact  Information \033[97m|\n";
	cout << "\t\t\t\t\t   ----------------------------------------\n";
	cout << "\t\t\t\t           | \033[96mEmail\033[97m: " << acc.email << setw(static_cast<streamsize>(email_length - strlen(acc.email)) + 2) << " |\n";
	cout << "\t\t\t\t           | \033[96mPhone-n\033[97m: " << acc.phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(acc.phone_number)) + 13) << " |\n";
	cout << "\t\t\t\t           ----------------------------------------\n\n";
	cout << "\t\t\t\t              ----------------------------------\n";
	cout << "\t\t\t\t              | \033[94mPress\033[97m,\033[92many\033[94m button \033[97m, \033[94mto go \033[91mBack \033[97m |\n";
	cout << "\t\t\t\t              ----------------------------------";
	_getch();
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_data(const string& login)
{
	char choose;
	char move = '1';
	while (true) {
		system("cls");
		cout << "\t\t\t\t   ---------------------------------------------------\n";
		cout << "\t\t\t\t   | \033[94mCONTROL \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t   ---------------------------------------------------\n\n\n";
		cout << "\t\t\t\t\t           \033[97m-------------------\n";
		cout << "\t\t\t\t\t           | \033[36mChange  Details \033[97m|\n";
		cout << "\t\t\t\t\t     -------------------------------\n";
		cout << "\t\t\t\t\t     | \033[33mUser\033[97m:  " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 2) << " |\n";
		cout << "\t\t\t\t\t     -------------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t    \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[92mPersonal Information \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[95mDate   of   birth    \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[96mPlace of residence   \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[34mContact Information  \033[97m|\n";
			cout << "\t\t\t\t\t     -------------------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t     | \033[94mChange \033[92mPersonal Information \033[97m|\n";
			cout << "\t\t\t\t\t    \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[95mDate   of   birth    \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[96mPlace of residence   \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[34mContact Information  \033[97m|\n";
			cout << "\t\t\t\t\t     -------------------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t     | \033[94mChange \033[92mPersonal Information \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[95mDate   of   birth    \033[97m|\n";
			cout << "\t\t\t\t\t    \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[96mPlace of residence   \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[34mContact Information  \033[97m|\n";
			cout << "\t\t\t\t\t     -------------------------------\n";
		}break;
		case '4':
		{
			cout << "\t\t\t\t\t     | \033[94mChange \033[92mPersonal Information \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[95mDate   of   birth    \033[97m|\n";
			cout << "\t\t\t\t\t     | \033[94mChange \033[96mPlace of residence   \033[97m|\n";
			cout << "\t\t\t\t\t    \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[34mContact Information  \033[97m|\n";
			cout << "\t\t\t\t\t     -------------------------------\n";
		}break;
		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '4';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '4')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				change_personal_Information(login);
			}if (move == '2')
			{
				change_date_of_birth(login);
			}if (move == '3')
			{
				change_place_of_residence(login);
			}if (move == '4')
			{
				change_contact_Information(login);
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::
change_personal_Information(const string& login)
{
	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t\t   ---------------------------------------------------\n";
		cout << "\t\t\t\t   | \033[94mCONTROL \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t   ---------------------------------------------------\n\n\n";
		cout << "\t\t\t\t             \033[97m-------------------------------\n";
		cout << "\t\t\t\t             | \033[94mChange \033[92mPersonal Information \033[97m|\n";
		cout << "\t\t\t\t             -------------------------------\n";
		cout << "\t\t\t\t             | \033[33mUser\033[97m:  " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t             -------------------------------\n\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t                  ---------------------\n";
			cout << "\t\t\t\t                 \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[93mName       \033[97m|\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mSurname    \033[97m|\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mPatronymic \033[97m|\n";
			cout << "\t\t\t\t                  ---------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t                  ---------------------\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mName       \033[97m|\n";
			cout << "\t\t\t\t                 \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[93mSurname    |\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mPatronymic \033[97m|\n";
			cout << "\t\t\t\t                  ---------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t                  ---------------------\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mName       \033[97m|\n";
			cout << "\t\t\t\t                  | \033[94mChange \033[93mSurname    \033[97m|\n";
			cout << "\t\t\t\t                 \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[93mPatronymic \033[97m|\n";
			cout << "\t\t\t\t                  ---------------------\n";
		}break;
		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				change_name(login);
			}
			else if (move == '2')
			{
				change_surname(login);
			}
			else if (move == '3')
			{
				change_patronymic(login);
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::
change_place_of_residence(const string& login)
{
	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t\t   ---------------------------------------------------\n";
		cout << "\t\t\t\t   | \033[94mCONTROL \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t   ---------------------------------------------------\n\n\n";
		cout << "\t\t\t\t              \033[97m-----------------------------\n";
		cout << "\t\t\t\t              | \033[94mChange \033[96mPlace of Residence \033[97m|\n";
		cout << "\t\t\t\t             -------------------------------\n";
		cout << "\t\t\t\t             | \033[33mUser\033[97m:  " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t             -------------------------------\n\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t            \033[97m------------------\n";
			cout << "\t\t\t\t\t           \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange  \033[93mCity   \033[97m|\n";
			cout << "\t\t\t\t\t            | \033[94mChange \033[93mCountry \033[97m|\n";
			cout << "\t\t\t\t\t            ------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t            \033[97m------------------\n";
			cout << "\t\t\t\t\t            | \033[94mChange  \033[93mCity   \033[97m|\n";
			cout << "\t\t\t\t\t           \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[93mCountry \033[97m|\n";
			cout << "\t\t\t\t\t            ------------------\n";
		}break;

		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				change_city(login);
			}
			else if (move == '2')
			{
				change_country(login);
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::
change_contact_Information(const string& login)
{
	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t\t   ---------------------------------------------------\n";
		cout << "\t\t\t\t   | \033[94mCONTROL \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t   ---------------------------------------------------\n\n\n";
		cout << "\t\t\t\t             \033[97m-------------------------------\n";
		cout << "\t\t\t\t             | \033[94mChange \033[34mContact  Information \033[97m|\n";
		cout << "\t\t\t\t             -------------------------------\n";
		cout << "\t\t\t\t             | \033[33mUser\033[97m:  " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t             -------------------------------\n\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t            \033[97m------------------\n";
			cout << "\t\t\t\t\t           \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[96mEmail \033[97m  |\n";
			cout << "\t\t\t\t\t            \033[97m| \033[94mChange \033[95mPhone-n \033[97m|\n";
			cout << "\t\t\t\t\t            ------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t            \033[97m------------------\n";
			cout << "\t\t\t\t\t            | \033[94mChange \033[96mEmail \033[97m  |\n";
			cout << "\t\t\t\t\t           \033[104m" << char(26) << "\033[0m\033[97m| \033[94mChange \033[95mPhone-n \033[97m|\n";
			cout << "\t\t\t\t\t            ------------------\n";
		}break;

		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				change_email(login);
			}
			else if (move == '2')
			{
				change_phone_n(login);
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_name(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_Name = new char[name_len];
	new_Name[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_Name);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t       \033[97m------------------\n";
		cout << "\t\t\t\t\t\t       |  \033[94mChange  \033[92mName  \033[97m|\n";
		cout << "\t\t\t\t\t\t ------------------------------\n";
		cout << "\t\t\t\t\t\t | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t       ----------------------------------\n";
		cout << "\t\t\t\t\t       | \033[95mOld \033[93mName\033[97m: " << acc.Name << setw(static_cast<streamsize>(name_len - strlen(acc.Name)) + 2) << " |\n";
		cout << "\t\t\t\t\t       ----------------------------------\n";
		cout << "\t\t\t\t\t       | \033[92mNew \033[93mName\033[97m: " << new_Name << setw(static_cast<streamsize>(name_len - strlen(new_Name)) + 2) << " |\n";
		cout << "\t\t\t\t\t       ----------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
			{
				if (i < name_len - 1)
				{
					new_Name[i] = choose;
					++i;
					new_Name[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_Name[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_Name;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_Name) > 2)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t       \033[97m------------------\n";
					cout << "\t\t\t\t\t\t       |  \033[94mChange  \033[92mName  \033[97m|\n";
					cout << "\t\t\t\t\t       ----------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 6) << " |\n";
					cout << "\t\t\t\t\t       | \033[95mOld \033[94mName\033[97m: " << acc.Name << setw(static_cast<streamsize>(name_len - strlen(acc.Name)) + 2) << " |\n";
					cout << "\t\t\t\t\t       | \033[92mNew \033[94mName\033[97m: " << new_Name << setw(static_cast<streamsize>(name_len - strlen(new_Name)) + 2) << " |\n";;;
					cout << "\t\t\t\t\t       ----------------------------------\n";
					cout << "\t\t\t\t\t         | \033[96mName  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t         ------------------------------\n";

					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.Name, new_Name);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();

					delete[] new_Name;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_surname(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_Surname = new char[sur_len];
	new_Surname[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_Surname);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t     \033[97m-------------------\n";
		cout << "\t\t\t\t\t\t     |  \033[94mSurname  \033[92mName  \033[97m|\n";
		cout << "\t\t\t\t\t       -------------------------------\n";
		cout << "\t\t\t\t\t       |  \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t -------------------------------------------\n";
		cout << "\t\t\t\t\t | \033[95mOld  \033[93mSurname\033[97m: " << acc.Surname << setw(static_cast<streamsize>(sur_len - strlen(acc.Surname)) + 2) << " |\n";
		cout << "\t\t\t\t\t -------------------------------------------\n";
		cout << "\t\t\t\t\t | \033[92mNew  \033[93mSurname\033[97m: " << new_Surname << setw(static_cast<streamsize>(sur_len - strlen(new_Surname)) + 2) << " |\n";
		cout << "\t\t\t\t\t -------------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
			{
				if (i < sur_len - 1)
				{
					new_Surname[i] = choose;
					++i;
					new_Surname[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_Surname[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_Surname;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_Surname) > 2)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t    \033[97m---------------------\n";
					cout << "\t\t\t\t\t\t    |  \033[94mChange  \033[92mSurname  \033[97m|\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 3) << " |\n";
					cout << "\t\t\t\t\t -------------------------------------------\n";
					cout << "\t\t\t\t\t | \033[95mOld \033[94mSurname\033[97m: " << acc.Surname << setw(static_cast<streamsize>(sur_len - strlen(acc.Surname)) + 3) << " |\n";
					cout << "\t\t\t\t\t | \033[92mNew \033[94mSurname\033[97m: " << new_Surname << setw(static_cast<streamsize>(sur_len - strlen(new_Surname)) + 3) << " |\n";
					cout << "\t\t\t\t\t -------------------------------------------\n";
					cout << "\t\t\t\t\t      | \033[96mSurname  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t      ---------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.Surname, new_Surname);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_Surname;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_patronymic(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_Patronymic = new char[patron_len];
	new_Patronymic[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_Patronymic);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t    \033[97m----------------------\n";
		cout << "\t\t\t\t\t\t    |  \033[94mPatronymic  \033[92mName  \033[97m|\n";
		cout << "\t\t\t\t\t        ------------------------------\n";
		cout << "\t\t\t\t\t        | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[95mOld  \033[93mPatronymic\033[97m: " << acc.Patronymic << setw(static_cast<streamsize>(patron_len - strlen(acc.Patronymic)) + 2) << " |\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[92mNew  \033[93mPatronymic\033[97m: " << new_Patronymic << setw(static_cast<streamsize>(patron_len - strlen(new_Patronymic)) + 2) << " |\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
			{
				if (i < patron_len - 1)
				{
					new_Patronymic[i] = choose;
					++i;
					new_Patronymic[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_Patronymic[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_Patronymic;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_Patronymic) > 2)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t   \033[97m-----------------------\n";
					cout << "\t\t\t\t\t\t   |  \033[94mChange \033[92mPatronymic  \033[97m|\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 3) << " |\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[95mOld \033[94mPatronymic\033[97m: " << acc.Patronymic << setw(static_cast<streamsize>(patron_len - strlen(acc.Patronymic)) + 3) << " |\n";
					cout << "\t\t\t\t\t  | \033[92mNew \033[94mPatronymic\033[97m: " << new_Patronymic << setw(static_cast<streamsize>(patron_len - strlen(new_Patronymic)) + 3) << " |\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t     | \033[96mPatronymic \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t     -----------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.Patronymic, new_Patronymic);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_Patronymic;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_city(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_city = new char[city_length];
	new_city[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_city);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t     \033[97m------------------\n";
		cout << "\t\t\t\t\t\t     |  \033[94mChange  \033[92mCity  \033[97m|\n";
		cout << "\t\t\t\t\t       ------------------------------\n";
		cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    | \033[95mOld  \033[93mCity\033[97m: " << acc.City << setw(static_cast<streamsize>(city_length - strlen(acc.City)) + 3) << " |\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    | \033[92mNew  \033[93mCity\033[97m: " << new_city << setw(static_cast<streamsize>(city_length - strlen(new_city)) + 3) << " |\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
			{
				if (i < city_length - 1)
				{
					new_city[i] = choose;
					++i;
					new_city[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_city[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_city;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_city) > 2)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t     \033[97m------------------\n";
					cout << "\t\t\t\t\t\t     |  \033[94mChange  \033[92mCity  \033[97m|\n";
					cout << "\t\t\t\t\t       ------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
					cout << "\t\t\t\t\t    ------------------------------------\n";
					cout << "\t\t\t\t\t    | \033[95mOld  \033[93mCity\033[97m: " << acc.City << setw(static_cast<streamsize>(city_length - strlen(acc.City)) + 3) << " |\n";
					cout << "\t\t\t\t\t    ------------------------------------\n";
					cout << "\t\t\t\t\t    | \033[92mNew  \033[93mCity\033[97m: " << new_city << setw(static_cast<streamsize>(city_length - strlen(new_city)) + 3) << " |\n";
					cout << "\t\t\t\t\t    ------------------------------------\n";
					cout << "\t\t\t\t\t       | \033[96mCity  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t       ------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.City, new_city);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_city;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_country(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_country = new char[country_length];
	new_country[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_country);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t   \033[97m---------------------\n";
		cout << "\t\t\t\t\t\t   |  \033[94mChange  \033[92mCountry  \033[97m|\n";
		cout << "\t\t\t\t\t       ------------------------------\n";
		cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t   ---------------------------------------\n";
		cout << "\t\t\t\t\t   | \033[95mOld  \033[93mCountry\033[97m: " << acc.Country << setw(static_cast<streamsize>(country_length - strlen(acc.Country)) + 2) << " |\n";
		cout << "\t\t\t\t\t   ---------------------------------------\n";
		cout << "\t\t\t\t\t   | \033[92mNew  \033[93mCountry\033[97m: " << new_country << setw(static_cast<streamsize>(country_length - strlen(new_country)) + 2) << " |\n";
		cout << "\t\t\t\t\t   ---------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
			{
				if (i < country_length - 1)
				{
					new_country[i] = choose;
					++i;
					new_country[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_country[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_country;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_country) > 2)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t   \033[97m---------------------\n";
					cout << "\t\t\t\t\t\t   |  \033[94mChange  \033[92mCountry  \033[97m|\n";
					cout << "\t\t\t\t\t       ------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[95mOld  \033[93mCountry\033[97m: " << acc.Country << setw(static_cast<streamsize>(country_length - strlen(acc.Country)) + 2) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[92mNew  \033[93mCountry\033[97m: " << new_country << setw(static_cast<streamsize>(country_length - strlen(new_country)) + 2) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t      | \033[96mCountry  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t      ---------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.Country, new_country);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_country;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_email(const string& login)
{
	Account acc;
	Local_Database::load_user_data(login, acc);

	char* new_email = new char[email_length];
	new_email[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_email);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t      \033[97m---------------------\n";
		cout << "\t\t\t\t\t\t      |  \033[94mChange  \033[92mCountry  \033[97m|\n";
		cout << "\t\t\t\t\t          ------------------------------\n";
		cout << "\t\t\t\t\t          | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t   ---------------------------------------------\n";
		cout << "\t\t\t\t\t   | \033[91mOld  \033[93mEmail\033[97m: " << acc.email << setw(static_cast<streamsize>(email_length - strlen(acc.email)) + 2) << " |\n";
		cout << "\t\t\t\t\t   ---------------------------------------------\n";
		cout << "\t\t\t\t\t   | \033[92mNew  \033[93mEmail\033[97m: " << new_email << setw(static_cast<streamsize>(email_length - strlen(new_email)) + 1) << " |";
		if (regex_match(new_email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) != 1)
		{
			cout << "\033[97m[\033[91mD\033[97m]";
		}
		else
		{
			cout << "\033[97m[\033[92mD\033[97m]\033[97m";
		}
		cout << "\n\t\t\t\t\t   ---------------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_' || choose == '@' || choose == '.')
			{
				if (i < email_length - 1)
				{
					new_email[i] = choose;
					++i;
					new_email[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_email[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_email;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_email) > 2 && regex_match(new_email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) == 1)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t      \033[97m---------------------\n";
					cout << "\t\t\t\t\t\t      |  \033[94mChange  \033[92mCountry  \033[97m|\n";
					cout << "\t\t\t\t\t          ------------------------------\n";
					cout << "\t\t\t\t\t          | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[91mOld  \033[93mEmail\033[97m: " << acc.email << setw(static_cast<streamsize>(email_length - strlen(acc.email)) + 2) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[92mNew  \033[93mEmail\033[97m: " << new_email << setw(static_cast<streamsize>(email_length - strlen(new_email)) + 2) << " |\n";
					cout << "\t\t\t\t\t   ---------------------------------------------\n";
					cout << "\t\t\t\t\t          | \033[96mEmail  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t          -------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.email, new_email);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_email;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_phone_n(const string& login)
{
	Account acc;
	load_user_data(login, acc);

	char* new_phone_number = new char[phone_n_length];
	new_phone_number[0] = '\0';

	char choose;
	bool key_move = false;

	for (size_t i = strlen(new_phone_number);;)
	{
		system("cls");
		cout << "\t\t\t\t\t  -----------------------------------------\n";
		cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t\t  -----------------------------------------\n\n";
		cout << "\t\t\t\t\t\t      \033[97m---------------------\n";
		cout << "\t\t\t\t\t\t      |  \033[94mChange  \033[92mPhone-n  \033[97m|\n";
		cout << "\t\t\t\t\t          ------------------------------\n";
		cout << "\t\t\t\t\t          | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
		cout << "\t\t\t\t\t        ----------------------------------\n";
		cout << "\t\t\t\t\t        | \033[91mOld  \033[93mPhone-n\033[97m: " << acc.phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(acc.phone_number)) + 2) << " |\n";
		cout << "\t\t\t\t\t        ----------------------------------\n";
		cout << "\t\t\t\t\t        | \033[92mNew  \033[93mPhone-n\033[97m: " << new_phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(new_phone_number)) + 2) << " |\n";
		cout << "\t\t\t\t\t        ----------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if (choose >= '0' && choose <= '9')
			{
				if (i < phone_n_length - 1)
				{
					new_phone_number[i] = choose;
					++i;
					new_phone_number[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					new_phone_number[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] new_phone_number;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(new_phone_number) > 6)
				{
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t      \033[97m---------------------\n";
					cout << "\t\t\t\t\t\t      |  \033[94mChange  \033[92mPhone-n  \033[97m|\n";
					cout << "\t\t\t\t\t          ------------------------------\n";
					cout << "\t\t\t\t\t          | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
					cout << "\t\t\t\t\t        ----------------------------------\n";
					cout << "\t\t\t\t\t        | \033[91mOld  \033[93mPhone-n\033[97m: " << acc.phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(acc.phone_number)) + 2) << " |\n";
					cout << "\t\t\t\t\t        ----------------------------------\n";
					cout << "\t\t\t\t\t        | \033[92mNew  \033[93mPhone-n\033[97m: " << new_phone_number << setw(static_cast<streamsize>(phone_n_length - strlen(new_phone_number)) + 2) << " |\n";
					cout << "\t\t\t\t\t        ----------------------------------\n";
					cout << "\t\t\t\t\t         | \033[96mPhone-n \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t         --------------------------------\n";

					this_thread::sleep_for(chrono::seconds(3));
					strcpy(acc.phone_number, new_phone_number);
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_phone_number;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
			break;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
		{
			key_move = false;
			break;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Test_Management::test_management_menu()
{
	char move = '1';
	char choose;
	while (true)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n";

		cout << "\n\n\n\t\t\t\t\t\t   --------------------\n";
		cout << "\t\t\t\t\t\t   | \033[96mTest  \033[94mManagement \033[97m|\n";
		cout << "\t\t\t\t\t\t   --------------------\n";
		switch (move)
		{
		case'1':
		{
			cout << "\t\t\t\t\t\t       |  \033[102mAssign\033[97m\033[0m  |\n";
			cout << "\t\t\t\t\t\t       |  \033[33mCreate\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |   \033[95mEdit\033[97m   |\n";
			cout << "\t\t\t\t\t\t       |  \033[91mDelete\033[97m  |\n";
			cout << "\t\t\t\t\t\t       ------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t       |  \033[92mAssign\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |  \033[43mCreate\033[0m\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |   \033[95mEdit\033[97m   |\n";
			cout << "\t\t\t\t\t\t       |  \033[91mDelete\033[97m  |\n";
			cout << "\t\t\t\t\t\t       ------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t\t       |  \033[92mAssign\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |  \033[33mCreate\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |   \033[105mEdit\033[0m\033[97m   |\n";
			cout << "\t\t\t\t\t\t       |  \033[91mDelete\033[97m  |\n";
			cout << "\t\t\t\t\t\t       ------------\n";
		}break;
		case '4':
		{
			cout << "\t\t\t\t\t\t       |  \033[92mAssign\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |  \033[33mCreate\033[97m  |\n";
			cout << "\t\t\t\t\t\t       |   \033[95mEdit\033[97m   |\n";
			cout << "\t\t\t\t\t\t       |  \033[101mDelete\033[0m\033[97m  |\n";
			cout << "\t\t\t\t\t\t       ------------\n";
		}break;
		default:;
		}

		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
			}
			if (move == '2')
			{
				Category create_test;
				create_test.category_initialization();
			}
			if (move == '3')
			{
				Category category;
				category.load_categories(category.categories);
				if (category.categories.size() > 0)
				{
					category.show_categories(false);
				}
				else
				{
					system("cls");
					cout << "\t\t\t     --------------------------------------------------------------\n";
					cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t     --------------------------------------------------------------\n";

					cout << "\n\n\n\t\t\t\t\t\t   --------------------\n";
					cout << "\t\t\t\t\t\t   | \033[96mTest  \033[94mManagement \033[97m|\n";
					cout << "\t\t\t\t\t\t   --------------------\n";
					cout << "\t\t\t\t\t\t       |  \033[92mAssign\033[97m  |\n";
					cout << "\t\t\t\t\t\t       |  \033[33mCreate\033[97m  |\n";
					cout << "\t\t\t\t\t\t       |   \033[105mEdit\033[0m\033[97m   |  \033[91mNo categories created\033[97m\n";
					cout << "\t\t\t\t\t\t       |  \033[91mDelete\033[97m  |\n";
					cout << "\t\t\t\t\t\t       ------------\n";
					this_thread::sleep_for(chrono::milliseconds(1500));
				}
			}
			if (move == '4')
			{
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '4';
			}
			else if (move == '4')
			{
				move = '4';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '4')
			{
				move = '3';
			}
			else if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
			else if (move == '1')
			{
				move = '1';
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Test_Management::edit_menu(const char* category, const char* section, string test_name)
{
	Test test(test_name.c_str()); // this tests

	test.load_test(category, section);

	char choose;
	char move = '1';

	while (true)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n\n";
		cout << "\t\t\t\t                    ------------------\n";
		cout << "\t\t\t\t                    | \033[96mTest \033[94mEdit Menu \033[97m|\n";
		cout << "\t\t\t\t                   --------------------\n";
		cout << "\t\t\t\t                   | \033[93mTest information \033[97m|\n";
		cout << "\t\t\t\t      ---------------------------------------------\n";
		cout << "\t\t\t\t      | \033[95mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << " |\n";
		cout << "\t\t\t\t      | \033[36mSection\033[97m: " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 4) << " |\n";
		cout << "\t\t\t\t      ---------------------------------------------\n";
		cout << "\t\t\t\t      | \033[33mTest Name\033[97m: " << test.test_name << setw(static_cast<streamsize>(test_name_length - strlen(test.test_name)) + 2) << " |\n";
		cout << "\t\t\t\t      ---------------------------------------------\n";
		cout << "\t\t\t\t                | \033[94mNumber Questions\033[97m: " << test.num_questions_;
		if (test.num_questions_ <= 9)
		{
			cout << "  |\n";
		}
		if (test.num_questions_ >= 10)
		{
			cout << " |\n";
		}
		cout << "\t\t\t\t                \033[97m------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t                |^|      \033[95mEdit \033[97m->:      |\n";
			cout << "\t\t\t\t                |\033[104m1\033[0m\033[97m|     \033[33mTest  \033[94mName\033[97m     |\n";
			cout << "\t\t\t\t                |2|  \033[96mNumber \033[92mQuestions\033[97m  |\n";
			cout << "\t\t\t\t                |3|      \033[92mQuestions\033[97m     |\n";
			cout << "\t\t\t\t                ------------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t                |^|      \033[95mEdit \033[97m->:      |\n";
			cout << "\t\t\t\t                |1|     \033[33mTest  \033[94mName\033[97m     |\n";
			cout << "\t\t\t\t                |\033[104m2\033[0m\033[97m|  \033[96mNumber \033[92mQuestions\033[97m  |\n";
			cout << "\t\t\t\t                |3|      \033[92mQuestions\033[97m     |\n";
			cout << "\t\t\t\t                ------------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t                |^|      \033[95mEdit \033[97m->:      |\n";
			cout << "\t\t\t\t                |1|     \033[33mTest  \033[94mName\033[97m     |\n";
			cout << "\t\t\t\t                |2|  \033[96mNumber \033[92mQuestions\033[97m  |\n";
			cout << "\t\t\t\t                |\033[104m3\033[0m\033[97m|      \033[92mQuestions\033[97m     |\n";
			cout << "\t\t\t\t                ------------------------\n";
		}break;
		default:;
		}
		choose = _getch();

		if (static_cast<int> (choose) == ESC)
		{
			return;
		}
		if (static_cast<int> (choose) == ENTER)
		{
			if (move == '1')
			{
				change_test_name(category, section, test);
			}
			if (move == '2')
			{
				change_number_questions(category, section, test);
			}
			if (move == '3')
			{
				change_question(category, section, test);
			}
		}
		if (static_cast<int> (choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
		}
		if (static_cast<int> (choose) == UP)
		{
			if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Test_Management::change_test_name(const char* category, const char* section, Test& obj)
{
	set<string> test_list;
	Test::load_list_tests(category, section, test_list);

	char* tmp_name = new char[test_name_length];
	tmp_name[0] = '\0';
	bool un = false;
	bool key_move = false;
	char choose;

	for (size_t i = strlen(tmp_name);;)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n\n";

		cout << "\t\t\t\t                  ---------------------\n";
		cout << "\t\t\t\t                  | \033[94mChange \033[92mTest  Name \033[97m|\n";
		cout << "\t\t\t\t  -----------------------------------------------------\n";
		cout << "\t\t\t\t  | \033[96mCurrent \033[92mTest Name\033[97m: " << obj.test_name << setw(static_cast<streamsize>(test_name_length - strlen(obj.test_name)) + 2) << " |\n";
		cout << "\t\t\t\t  -----------------------------------------------------\n";
		cout << "\t\t\t     \033[95mEnter  \033[97m| \033[93mNew \033[92mTest Name\033[97m: " << tmp_name << setw(static_cast<streamsize>(test_name_length - strlen(tmp_name)) + 2) << " |";;

		for (auto it : test_list)
		{
			if (strcmp(tmp_name, it.c_str()) == 0)
			{
				cout << "   \033[91mThe test name already exists\033[97m";
				un = true;
				break;
			}
			else
			{
				un = false;
			}
		}

		cout << "\n\t\t\t\t    --------------------------------------------------\n";
		choose = _getch();

		if (static_cast<int> (choose) == ENTER && strlen(tmp_name) > 3 && un == false)
		{
			fs::remove_all(dir_an_path::Directories::Test::folder_test(category, section, obj.test_name).c_str());

			test_list.erase(obj.test_name);

			Test::save_list_tests(category, section, test_list);

			strcpy(obj.test_name, tmp_name);

			obj.save_test(category, section);

			strcpy(obj.test_name, tmp_name);

			test_list.emplace(tmp_name);

			delete[] tmp_name;
			return;
		}
		if (static_cast<int> (choose) != -32 && key_move == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ' || choose == '!' || choose == '.' || choose == '_')
			{
				if (i < test_name_length - 1)
				{
					tmp_name[i] = choose;
					++i;
					tmp_name[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					tmp_name[i] = '\0';
					Sleep(30);
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] tmp_name;
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
		{
			key_move = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_move == true)
		{
			key_move = false;
		}
		if (static_cast<int> (choose) == LEFT && key_move == true)
		{
			key_move = false;
		}
		if (static_cast<int> (choose) == UP && key_move == true)
		{
			key_move = false;
		}
		if (static_cast<int> (choose) == DOWN && key_move == true)
		{
			key_move = false;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Test_Management::change_number_questions(const char* category, const char* section, Test& obj)
{
	while (true)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n\n";

		cout << "\t\t\t\t                  ---------------------\n";
		cout << "\t\t\t\t                  | \033[94mChange \033[92mTest  Name \033[97m|\n";
		cout << "\t\t\t\t  -----------------------------------------------------\n";
		_getch();
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::Change_Details::change_date_of_birth(const string& login)
{
	Account acc;
	load_user_data(login, acc);

	char* new_day = new char[day_l];
	new_day[0] = '\0';
	char* new_month = new char[month_l];
	new_month[0] = '\0';
	char* new_year = new char[year_l];
	new_year[0] = '\0';

	char choose;
	bool key_move = false;
	char move = '1';

	while (true)
	{
		switch (move)
		{
		case '1':
		{
			for (size_t i = strlen(new_day);;)
			{
				system("cls");
				cout << "\t\t\t\t\t  -----------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Accept - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t\t\t  -----------------------------------------\n\n";
				cout << "\t\t\t\t\t\t      \033[97m------------------\n";
				cout << "\t\t\t\t\t\t      |  \033[95mDate Of Birth \033[97m|\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[92mDate Of Birth \033[97m:\033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t       " << char(26) << "| Day:  " << new_day << setw(static_cast<streamsize>(day_l - strlen(new_day)) + 20) << " |\n";
				cout << "\t\t\t\t\t        | Month:  " << new_month << setw(static_cast<streamsize>(month_l - strlen(new_month)) + 18) << " |\n";
				cout << "\t\t\t\t\t        | Year:  " << new_year << setw(static_cast<streamsize>(year_l - strlen(new_year)) + 17) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_move == false)
				{
					if (choose >= '0' && choose <= '9')
					{
						if (i < day_l - 1)
						{
							new_day[i] = choose;
							++i;
							new_day[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							new_day[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							delete[] new_day;
							delete[] new_month;
							delete[] new_year;
							return;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
				{
					key_move = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == UP && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
				{
					key_move = false;
					move = '2';
					break;
				}
				if (static_cast<int> (choose) == ENTER && strlen(new_day) > 0 && strlen(new_month) > 0 && strlen(new_year) > 3)
				{
					strcpy(acc.day, new_day);
					strcpy(acc.month, new_month);
					strcpy(acc.year, new_year);
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t \033[97m---------------------------\n";
					cout << "\t\t\t\t\t\t |  \033[94mChange  \033[92mDate Of Birth  \033[97m|\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 3) << " |\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[92mDate Of Birth \033[97m: \033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[96mDate of birth  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_day;
					delete[] new_month;
					delete[] new_year;
					return;
				}
			}
		}break;
		case'2':
		{
			for (size_t i = strlen(new_month);;)
			{
				system("cls");
				cout << "\t\t\t\t\t  -----------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Accept - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t\t\t  -----------------------------------------\n\n";
				cout << "\t\t\t\t\t\t      \033[97m------------------\n";
				cout << "\t\t\t\t\t\t      |  \033[95mDate Of Birth \033[97m|\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[92mDate Of Birth \033[97m:\033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | Day:  " << new_day << setw(static_cast<streamsize>(day_l - strlen(new_day)) + 20) << " |\n";
				cout << "\t\t\t\t\t       " << char(26) << "| Month:  " << new_month << setw(static_cast<streamsize>(month_l - strlen(new_month)) + 18) << " |\n";
				cout << "\t\t\t\t\t        | Year:  " << new_year << setw(static_cast<streamsize>(year_l - strlen(new_year)) + 17) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_move == false)
				{
					if (choose >= '0' && choose <= '9')
					{
						if (i < month_l - 1)
						{
							new_month[i] = choose;
							++i;
							new_month[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							new_month[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							delete[] new_day;
							delete[] new_month;
							delete[] new_year;
							return;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
				{
					key_move = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == UP && key_move == true)
				{
					key_move = false;
					move = '1';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
				{
					key_move = false;
					move = '3';
					break;
				}
				if (static_cast<int> (choose) == ENTER && strlen(new_day) > 0 && strlen(new_month) > 0 && strlen(new_year) > 3)
				{
					strcpy(acc.day, new_day);
					strcpy(acc.month, new_month);
					strcpy(acc.year, new_year);
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t \033[97m---------------------------\n";
					cout << "\t\t\t\t\t\t |  \033[94mChange  \033[92mDate Of Birth  \033[97m|\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 3) << " |\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[92mDate Of Birth \033[97m: \033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[96mDate of birth  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_day;
					delete[] new_month;
					delete[] new_year;
					return;
				}
			}
		}break;
		case '3':
		{
			for (size_t i = strlen(new_year);;)
			{
				system("cls");
				cout << "\t\t\t\t\t  -----------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Accept - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t\t\t  -----------------------------------------\n\n";
				cout << "\t\t\t\t\t\t      \033[97m------------------\n";
				cout << "\t\t\t\t\t\t      |  \033[95mDate Of Birth \033[97m|\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str()) + 2)) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | \033[92mDate Of Birth \033[97m:\033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				cout << "\t\t\t\t\t        | Day:  " << new_day << setw(static_cast<streamsize>(day_l - strlen(new_day)) + 20) << " |\n";
				cout << "\t\t\t\t\t        | Month:  " << new_month << setw(static_cast<streamsize>(month_l - strlen(new_month)) + 18) << " |\n";
				cout << "\t\t\t\t\t       " << char(26) << "| Year:  " << new_year << setw(static_cast<streamsize>(year_l - strlen(new_year)) + 17) << " |\n";
				cout << "\t\t\t\t\t        ------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_move == false)
				{
					if (choose >= '0' && choose <= '9')
					{
						if (i < year_l - 1)
						{
							new_year[i] = choose;
							++i;
							new_year[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							new_year[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							delete[] new_day;
							delete[] new_month;
							delete[] new_year;
							return;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
				{
					key_move = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_move == true)
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == UP && key_move == true)
				{
					key_move = false;
					move = '2';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
				{
					key_move = false;
					break;
				}
				if (static_cast<int> (choose) == ENTER && strlen(new_day) > 0 && strlen(new_month) > 0 && strlen(new_year) > 3)
				{
					strcpy(acc.day, new_day);
					strcpy(acc.month, new_month);
					strcpy(acc.year, new_year);
					system("cls");
					cout << "\t\t\t\t\t  -----------------------------------------\n";
					cout << "\t\t\t\t\t  | \033[94mCONTROL \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t\t\t  -----------------------------------------\n\n";
					cout << "\t\t\t\t\t\t \033[97m---------------------------\n";
					cout << "\t\t\t\t\t\t |  \033[94mChange  \033[92mDate Of Birth  \033[97m|\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[33mUser\033[97m: " << login << setw(static_cast<streamsize>(login_len - strlen(login.c_str())) + 3) << " |\n";
					cout << "\t\t\t\t\t       -------------------------------\n";
					cout << "\t\t\t\t\t       | \033[92mDate Of Birth \033[97m: \033[96m " << acc.day << '.' << acc.month << '.' << acc.year << setw(static_cast<streamsize>((day_l + month_l + year_l + 2) - (strlen(acc.day) + strlen(acc.month) + strlen(acc.year)))) << "\033[97m |\n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					cout << "\t\t\t\t\t   | \033[96mDate of birth  \033[92mSuccessfully changed \033[97m|  \n";
					cout << "\t\t\t\t\t   ---------------------------------------\n";
					this_thread::sleep_for(chrono::seconds(3));
					fs::remove_all(dir_an_path::Directories::User::save_user_folder(acc.login));

					thread sv(save_user_acc, acc);
					sv.detach();
					delete[] new_day;
					delete[] new_month;
					delete[] new_year;
					return;
				}
			}
		}break;
		default:;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::acc_management_menu(const string& login, set<string>& logins)
{
	char move = '1';
	char choose = ' ';
	while (true) {
		system("cls");
		cout << "\t\t\t\t  ---------------------------------------------------\n";
		cout << "\t\t\t\t  | \033[94mCONTROL \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t\t  ---------------------------------------------------\n\n\n\n";

		cout << "\t\t\t\t\t        -----------------------\n";
		cout << "\t\t\t\t\t        | \033[95mAccount  \033[36mManagement \033[97m|\n";
		cout << "\t\t\t\t\t    -------------------------------\n";
		cout << "\t\t\t\t\t    | \033[96mUser\033[97m:  " << login << setw(23 - strlen(login.c_str())) << " |\n";
		cout << "\t\t\t\t\t    -------------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t         \033[104m" << char(26) << "\033[0m\033[97m| \033[93mView    \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t          | \033[92mChange  \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t          | \033[91mDelete  \033[94mAccount\033[97m |\n";
			cout << "\t\t\t\t\t          -------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t          | \033[93mView    \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t         \033[104m" << char(26) << "\033[0m\033[97m| \033[92mChange  \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t          | \033[91mDelete  \033[94mAccount\033[97m |\n";
			cout << "\t\t\t\t\t          -------------------\n";
		}break;
		case '3':
		{
			cout << "\t\t\t\t\t          | \033[93mView    \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t          | \033[92mChange  \033[94mDetails \033[97m|\n";
			cout << "\t\t\t\t\t         \033[104m" << char(26) << "\033[0m\033[97m| \033[91mDelete  \033[94mAccount\033[97m |\n";
			cout << "\t\t\t\t\t          -------------------\n";
		}break;
		default:;
		}

		choose = _getch();
		if (static_cast<int>(choose) == DOWN)
		{
			if (move == '1')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '3';
			}
		}
		if (static_cast<int>(choose) == UP)
		{
			if (move == '3')
			{
				move = '2';
			}
			else if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1') // view
			{
				view_details(login);
			}
			if (move == '2') // change
			{
				Change_Details::change_data(login);
			}
			if (move == '3') // delete
			{
				if (delete_account(login, logins) == true)
				{
					return;
				}
			}
		}
	}
}

bool Context_Menu::Admin_Context::Admin_Menu::User_Management::Account_management::delete_account(const string& login, set<string>& logins)
{
	char move = '2';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t   -------------------------------------------------------------------\n";
		cout << "\t\t\t   |\033[94mCONTROL\033[97m| \033[95mLeft   Right \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t   -------------------------------------------------------------------\n";
		cout << "\n\n\n\n\t\t\t\t\t         \033[97m-----------------------\n";
		cout << "\t\t\t\t\t         | \033[91mDeleting \033[92man account\033[97m |\n";
		cout << "\t\t\t\t\t    ---------------------------------\n";
		cout << "\t\t\t\t\t    | \033[33mAccount\033[97m: " << login << setw(static_cast<streamsize>(login_len - login.size()) + 2) << " |\n";
		cout << "\t\t\t\t\t    ---------------------------------\n";
		cout << "\t\t\t\t\t    |   \033[95mAre you sure you want to    \033[97m|\n";
		cout << "\t\t\t\t\t    | \033[31mirretrievably \033[91mdelete \033[96mthe data \033[97m|\n";
		cout << "\t\t\t\t\t    ---------------------------------\n";

		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t    |      \033[97m\033[102mYes\033[0m              \033[91mNo\033[97m      |\n";
			cout << "\t\t\t\t\t    ---------------------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t    |      \033[92mYes              \033[97m\033[101mNo\033[0m\033[97m      |\n";
			cout << "\t\t\t\t\t    ---------------------------------\n";
		}break;
		default:;
		}

		choose = _getch();
		if (static_cast<int>(choose) == RIGHT)
		{
			if (move == '1')
			{
				move = '2';
			}
		}
		if (static_cast<int>(choose) == LEFT)
		{
			if (move == '2')
			{
				move = '1';
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return false;
		}
		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '2')
			{
				return false;
			}
			if (move == '1')
			{
				logins.erase(login);
				Local_Database::save_logins(logins);
				fs::remove_all(dir_an_path::Directories::User::save_user_folder(login.c_str()));

				system("cls");
				cout << "\t\t\t   -------------------------------------------------------------------\n";
				cout << "\t\t\t   |\033[94mCONTROL\033[97m| \033[95mLeft   Right \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
				cout << "\t\t\t   -------------------------------------------------------------------\n";
				cout << "\n\n\n\t\t\t\t\t         \033[97m-----------------------\n";
				cout << "\t\t\t\t\t         | \033[91mDeleting \033[92man account\033[97m |\n";
				cout << "\t\t\t\t\t    ---------------------------------\n";
				cout << "\t\t\t\t\t    | \033[33mAccount\033[97m: " << login << setw(static_cast<streamsize>(login_len - login.size()) + 2) << " |\n";
				cout << "\t\t\t\t\t    ---------------------------------\n";
				cout << "\t\t\t\t\t    | \033[96mAccount  \033[92mSuccessfully \033[31mDeleted\033[97m |\n";
				cout << "\t\t\t\t\t    ---------------------------------\n";
				this_thread::sleep_for(chrono::seconds(2));
				return true;
			}
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Admin_Setting::show_adm_data(const Admin& obj)
{
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t\t            -------------------\n";
	cout << "\t\t\t\t\t            | \033[33mShow Admin Data \033[97m|\n";
	cout << "\t\t\t\t\t------------------------------------------\n";
	cout << "\t\t\t\t\t| \033[94mLogin\033[97m: " << obj.login << setw(34 - strlen(obj.login)) << " |\n";
	cout << "\t\t\t\t\t| \033[94mPassword\033[97m: " << obj.password << setw(31 - strlen(obj.password)) << " |\n";
	cout << "\t\t\t\t\t| \033[95mKey Recovery\033[97m: " << obj.rec_key << setw(27 - strlen(obj.rec_key)) << " |\n";
	cout << "\t\t\t\t\t------------------------------------------\n";
	cout << "\t\t\t\t\t        | \033[91mExit \033[96m, press any button\033[97m |\n";
	cout << "\t\t\t\t\t        ---------------------------\n";

	_getch();
}

void Context_Menu::Admin_Context::Admin_Menu::Admin_Setting::change_adm_data(Admin& obj)
{
	char move = '1';
	char choose;
	bool key_st = false;
	while (true)
	{
		system("cls");
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     ----------------------------------------------------------------\n";
		cout << "\n\n\n\t\t\t\t\t\t     ---------------------\n";
		cout << "\t\t\t\t\t\t     | \033[33mChange Admin Data \033[97m|  \n";
		cout << "\t\t\t\t\t\t    -----------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t\t   \033[104m" << char(26) << "\033[0m\033[97m| \033[92mChange \033[94mPassword     \033[97m|\n";
			cout << "\t\t\t\t\t\t    | \033[92mChange \033[95mKey Recovery \033[97m|\n";
			cout << "\t\t\t\t\t\t    -----------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t    | \033[92mChange \033[94mPassword     \033[97m|\n";
			cout << "\t\t\t\t\t\t   \033[104m" << char(26) << "\033[0m\033[97m| \033[92mChange \033[95mKey Recovery \033[97m|\n";
			cout << "\t\t\t\t\t\t    -----------------------\n";
		}break;
		default:;
		}
		choose = _getch();
		if (static_cast<int> (choose) == ENTER)
		{
			if (move == '1')
			{
				change_password(obj);
			}
			else if (move == '2')
			{
				change_key_recovery(obj);
			}
		}
		if (static_cast<int> (choose) == -32 && key_st == false) // if user typed key_down // key =  -32
		{
			key_st = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == LEFT && key_st == true)
		{
			key_st = false;
		}
		if (static_cast<int> (choose) == UP && key_st == true) // second_key_down 72
		{
			if (move == '1')
			{
				key_st = false;
			}
			else if (move == '2')
			{
				key_st = false;
				move = '1';
			}
		}
		if (static_cast<int> (choose) == DOWN && key_st == true)  // second_key_down 80
		{
			if (move == '1')
			{
				key_st = false;
				move = '2';
			}
			else if (move == '2')
			{
				key_st = false;
			}
		}
		if (static_cast<int> (choose) == ESC)
		{
			return;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Admin_Setting::change_password(Admin& obj)
{
	char* new_password = new char[pass_len];
	new_password[0] = '\0';
	char choose;

	for (size_t i = strlen(new_password);;)
	{
		// Show
		system("cls");
		cout << "\t\t\t\t    ----------------------------------------------------\n";
		cout << "\t\t\t\t    |\033[94mCONTROL\033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t\t    ----------------------------------------------------\n";
		cout << "\n\n\n\n\t\t\t\t\t\t   -------------------------\n";
		cout << "\t\t\t\t\t           | \033[93mChange \033[94mAdmin \033[33mPassword \033[97m|\n";
		cout << "\t\t\t\t\t-----------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[36mCurr Password\033[97m: " << obj.password << setw(31 - strlen(obj.password)) << " |\n";
		cout << "\t\t\t\t\t-----------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[92mNew \033[94mPassword\033[97m: " << new_password << setw(32 - strlen(new_password)) << " |\n";
		cout << "\t\t\t\t\t-----------------------------------------------\n";
		if (strcmp(new_password, obj.login) == 0)
		{
			cout << "\t\t\t\t\t     \033[91mPassword and login cannot be the same!\033[97m\n";
		}
		else if (strcmp(new_password, obj.rec_key) == 0)
		{
			cout << "\t\t\t\t\t\033[91m Password and Key Recovery cannot be the same!\033[97m\n";
		}
		else if (strcmp(new_password, obj.password) == 0)
		{
			cout << "\t\t\t\t\t \033[91mPassword is similar to the previous password!\033[97m\n";
		}
		choose = _getch();

		if (static_cast<int>(choose) == ENTER && strlen(new_password) > 4 && strcmp(new_password, obj.login) != 0 && strcmp(new_password, obj.rec_key) != 0 && strcmp(new_password, obj.password) != 0)
		{
			cout << "\n\n\t\t\t\t\t     \033[92mThe password was successfully changed!\033[97m";
			strcpy(obj.password, new_password);
			delete[] new_password;
			this_thread::sleep_for(chrono::seconds(2));

			fs::remove(dir_an_path::Path::Admin::path_adm_enc_key());
			fs::remove(dir_an_path::Path::Admin::path_sv_adm_data());

			thread sv(save_admin_acc, obj);
			sv.detach();
			return;
		}
		if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '!' || choose == '@' || choose == '#' || choose == '%')
		{
			if (i < pass_len - 1)
			{
				new_password[i] = choose;
				++i;
				new_password[i] = '\0';
			}
		}
		if (choose == '\b' && i > 0) // if user typed backspace
		{
			--i;
			new_password[i] = '\0';
			Sleep(30);
		}
		if (static_cast<int>(choose) == ESC)
		{
			delete[] new_password;
			return;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Admin_Setting::change_key_recovery(Admin& obj)
{
	char* new_key_rec = new char[rec_key_length];
	new_key_rec[0] = '\0';
	char choose;

	for (size_t i = strlen(new_key_rec);;)
	{
		// Show
		system("cls");
		cout << "\t\t\t\t    ----------------------------------------------------\n";
		cout << "\t\t\t\t    |\033[94mCONTROL\033[97m| Exit to Main Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t\t    ----------------------------------------------------\n";
		cout << "\n\n\n\n\t\t\t\t\t\t  -----------------------\n";
		cout << "\t\t\t\t\t\t  | \033[93mChange \033[94mKey \033[33mRecovery \033[97m|\n";
		cout << "\t\t\t\t\t\t---------------------------\n";
		cout << "\t\t\t\t\t\t| \033[36mCurrent Key\033[97m: " << obj.rec_key << setw(13 - strlen(obj.rec_key)) << " |\n";
		cout << "\t\t\t\t\t\t---------------------------\n";
		cout << "\t\t\t\t\t\t| \033[92mNew \033[94mKey\033[97m: " << new_key_rec << setw(17 - strlen(new_key_rec)) << " |\n";
		cout << "\t\t\t\t\t\t---------------------------\n";
		if (strcmp(new_key_rec, obj.login) == 0)
		{
			cout << "\t\t\t\t\t \033[91mKey Recovery and login cannot be the same!\033[97m\n";
		}
		else if (strcmp(new_key_rec, obj.password) == 0)
		{
			cout << "\t\t\t\t\t\033[91mPassword and Key Recovery cannot be the same!\033[97m\n";
		}
		else if (strcmp(new_key_rec, obj.rec_key) == 0)
		{
			cout << "\t\t\t\t\t\033[91mKey Recovery is similar to the previous Key Recovery!\033[97m\n";
		}
		choose = _getch();

		if (static_cast<int>(choose) == ENTER && strlen(new_key_rec) > 4 && strcmp(new_key_rec, obj.login) != 0 && strcmp(new_key_rec, obj.rec_key) != 0 && strcmp(new_key_rec, obj.password) != 0)
		{
			cout << "\n\n\t\t\t\t\t    .  \033[92mThe Key was successfully changed!\033[97m";
			strcpy(obj.rec_key, new_key_rec);
			delete[] new_key_rec;
			this_thread::sleep_for(chrono::seconds(2));

			fs::remove(dir_an_path::Path::Admin::path_adm_enc_key());
			fs::remove(dir_an_path::Path::Admin::path_sv_adm_data());

			thread sv(save_admin_acc, obj);
			sv.detach();

			return;
		}
		if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
		{
			if (i < rec_key_length - 1)
			{
				new_key_rec[i] = choose;
				++i;
				new_key_rec[i] = '\0';
			}
		}
		if (choose == '\b' && i > 0) // if user typed backspace
		{
			--i;
			new_key_rec[i] = '\0';
			Sleep(30);
		}
		if (static_cast<int>(choose) == ESC)
		{
			delete[] new_key_rec;
			return;
		}
	}
}

void Context_Menu::Admin_Context::Admin_Menu::Test_Management::change_question(const char* category, const char* section, Test& obj)
{
}

Context_Menu::Admin_Context::~Admin_Context()
= default;

void Context_Menu::show_time_an_date()
{
	srand(0);
	time_t now = time(nullptr);
	tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "\033[92mD\033[97m: %d \033[92mM\033[97m: %m \033[92mY\033[97m: %Y", &tstruct);
	cout << "\033[0m\t\t\t\t\t\t\t\t\t\t\t\t|  " << buf;
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	cout << "\033[0m\n\t\t\t\t\t\t\t\t\t\t\t\t\033[97m|  \033[93mTime\033[97m:   " << buf << "\033[97m";
	cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t------------------------";
}

Context_Menu::~Context_Menu()
= default;

bool Context_Menu::Creating_Menu::create_adm_acc(Admin& admin_)
{
	system("cls");
	cout << "\n\n\n\n\t\t\t                      ---------------------------------\n";
	cout << "\t\t\t                      | \033[92mWelcome to the \033[95mTesting \033[96mSystem\033[97m |\n";
	cout << "\t\t\t    ---------------------------------------------------------------------\n";
	cout << "\t\t\t    |               \033[94mRunning the program for the first time\033[97m              |\n";
	cout << "\t\t\t    | \033[31mPlease \033[94mcreate an \033[95mAdministrator account\033[94m to have his access rights.\033[97m |\n";
	cout << "\t\t\t    |                   \033[36mAnd enable all functionality         \033[97m           |\n";
	cout << "\t\t\t    ---------------------------------------------------------------------\n\n\n";
	cout << "\t\t\t                      ---------------------------------\n";
	cout << "\t\t\t                      | \033[33mPress \033[91many \033[92m button to continue \033[97m|\n";
	cout << "\t\t\t                      ---------------------------------\n"; _getch();

	///

	char choose;  // pressed button
	char move = '1';
	bool correct = false;
	while (true)
	{
		switch (move)
		{
		case'1':
		{
			for (size_t i = strlen(admin_.login);;)
			{
				// Show
				system("cls");
				cout << "\033[97m\n\n\n\n\t\t\t\t\t    -------------------------------------\n";
				cout << "\t\t\t\t\t    | \033[36mCreating an \033[96mAdministrator\033[36m account\033[97m |\n";
				cout << "\t\t\t\t\t --------------------------------------------\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[93mlogin \033[97m(\033[33mlength\033[97m 4 to 20)        |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[94mpassword \033[97m(\033[33mlength\033[97m 6 to 28)     |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[95mrecovery key \033[97m(\033[33mlength\033[97m 4 to 10) |\n";
				cout << "\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t     \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[95mLogin\033[97m: " << admin_.login << setw(34 - strlen(admin_.login)) << " |";
				if (strlen(admin_.login) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.login, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }
				cout << "\n\t\t\t\t      | \033[94mPassword\033[97m: "; for (int i = 0; i < strlen(admin_.password); i++) { cout << '*'; }; cout << setw(31 - strlen(admin_.password)) << " |";
				if (strlen(admin_.password) < 6 || strcmp(admin_.login, admin_.password) == 0 || strcmp(admin_.password, admin_.rec_key) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }

				cout << "\n\t\t\t\t      | \033[96mKey Recovery\033[97m: " << admin_.rec_key << setw(27 - strlen(admin_.rec_key)) << " |";
				if (strlen(admin_.rec_key) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.rec_key, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }
				cout << "\n\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t\t           | \033[94mAccept and continue \033[97m|              \n";
				cout << "\t\t\t\t\t           -----------------------\n";
				if (strlen(admin_.login) > 0)
				{
					if (strcmp(admin_.login, admin_.password) == 0)
					{
						cout << "\t\t\t\t           \033[91mLogin and password must be different!\n";
					}
					if (strcmp(admin_.login, admin_.rec_key) == 0)
					{
						cout << "\t\t\t\t           \033[91mLogin and key recovery must be different!\n";
					}
				}

				choose = _getch();

				if (static_cast<int> (choose) != -32 && correct == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
					{
						if (i < login_len - 1)
						{
							admin_.login[i] = choose;
							++i;
							admin_.login[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							admin_.login[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							return false;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && correct == false) // if user typed key_down // key =  -32
				{
					correct = true;
				}
				if (static_cast<int> (choose) == RIGHT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == UP && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == LEFT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == DOWN && correct == true)  // second_key_down 80
				{
					correct = false;
					move = '2';
					break;
				}
			}
		}break;
		case'2':
		{
			for (size_t i = strlen(admin_.password);;)
			{
				// Show
				system("cls");
				cout << "\033[97m\n\n\n\n\t\t\t\t\t    -------------------------------------\n";
				cout << "\t\t\t\t\t    | \033[36mCreating an \033[96mAdministrator\033[36m account\033[97m |\n";
				cout << "\t\t\t\t\t --------------------------------------------\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[93mlogin \033[97m(\033[33mlength\033[97m 4 to 20)        |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[94mpassword \033[97m(\033[33mlength\033[97m 6 to 28)     |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[95mrecovery key \033[97m(\033[33mlength\033[97m 4 to 10) |\n";
				cout << "\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t      | \033[95mLogin\033[97m: " << admin_.login << setw(34 - strlen(admin_.login)) << " |";
				if (strlen(admin_.login) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.login, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }
				cout << "\n\t\t\t\t     \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[94mPassword\033[97m: ";
				for (int e = 0; e < strlen(admin_.password); e++)
				{
					cout << "*";
				}
				if (strlen(admin_.password) > 0)
				{
					cout << "\b \b";
					cout << admin_.password[strlen(admin_.password) - 1];
				}
				cout << setw(31 - strlen(admin_.password)) << " |";
				if (strlen(admin_.password) < 6 || strcmp(admin_.login, admin_.password) == 0 || strcmp(admin_.password, admin_.rec_key) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }

				cout << "\n\t\t\t\t      | \033[96mKey Recovery\033[97m: " << admin_.rec_key << setw(27 - strlen(admin_.rec_key)) << " |";
				if (strlen(admin_.rec_key) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.rec_key, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }

				cout << "\n\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t\t           | \033[94mAccept and continue \033[97m|              \n";
				cout << "\t\t\t\t\t           -----------------------\n";
				if (strlen(admin_.password) > 0)
				{
					if (strcmp(admin_.login, admin_.password) == 0)
					{
						cout << "\t\t\t\t           \033[91mLogin and password must be different!\n";
					}
					if (strcmp(admin_.password, admin_.rec_key) == 0)
					{
						cout << "\t\t\t\t           \033[91mPassword and key recovery must be different!\n";
					}
				}

				choose = _getch();

				if (static_cast<int> (choose) != -32 && correct == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '!' || choose == '@' || choose == '#' || choose == '%')
					{
						if (i < pass_len - 1)
						{
							admin_.password[i] = choose;
							++i;
							admin_.password[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							admin_.password[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							return false;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && correct == false) // if user typed key_down // key =  -32
				{
					correct = true;
				}
				if (static_cast<int> (choose) == RIGHT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == LEFT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == UP && correct == true) // second_key_down 72
				{
					correct = false;
					move = '1';
					break;
				}
				if (static_cast<int> (choose) == DOWN && correct == true)  // second_key_down 80
				{
					correct = false;
					move = '3';
					break;
				}
			}
		}break;
		case '3':
		{
			for (size_t i = strlen(admin_.rec_key);;)
			{
				// Show
				system("cls");
				cout << "\033[97m\n\n\n\n\t\t\t\t\t    -------------------------------------\n";
				cout << "\t\t\t\t\t    | \033[36mCreating an \033[96mAdministrator\033[36m account\033[97m |\n";
				cout << "\t\t\t\t\t --------------------------------------------\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[93mlogin \033[97m(\033[33mlength\033[97m 4 to 20)        |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[94mpassword \033[97m(\033[33mlength\033[97m 6 to 28)     |\n";
				cout << "\t\t\t\t\t | \033[92mThink of a \033[95mrecovery key \033[97m(\033[33mlength\033[97m 4 to 10) |\n";
				cout << "\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t      | \033[95mLogin\033[97m: " << admin_.login << setw(34 - strlen(admin_.login)) << " |";
				if (strlen(admin_.login) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.login, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }
				cout << "\n\t\t\t\t      | \033[94mPassword\033[97m: ";
				for (int e = 0; e < strlen(admin_.password); e++)
				{
					cout << "*";
				}
				cout << setw(31 - strlen(admin_.password)) << " |";
				if (strlen(admin_.password) < 6 || strcmp(admin_.login, admin_.password) == 0 || strcmp(admin_.password, admin_.rec_key) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }

				cout << "\n\t\t\t\t     \033[97m\033[104m" << char(26) << "\033[0m\033[97m| \033[96mKey Recovery\033[97m: " << admin_.rec_key << setw(27 - strlen(admin_.rec_key)) << " |";
				if (strlen(admin_.rec_key) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.rec_key, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
				else { cout << " \033[92mDONE\033[97m |"; }

				cout << "\n\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t\t           | \033[94mAccept and continue \033[97m|              \n";
				cout << "\t\t\t\t\t           -----------------------\n";

				if (strlen(admin_.rec_key) > 0)
				{
					if (strcmp(admin_.login, admin_.rec_key) == 0)
					{
						cout << "\t\t\t\t           \033[91mkey recovery and Login must be different!\n";
					}
					if (strcmp(admin_.rec_key, admin_.password) == 0)
					{
						cout << "\t\t\t\t           \033[91mkey recovery and password must be different!\n";
					}
				}

				choose = _getch();

				if (static_cast<int> (choose) != -32 && correct == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
					{
						if (i < rec_key_length - 1)
						{
							admin_.rec_key[i] = choose;
							++i;
							admin_.rec_key[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							admin_.rec_key[i] = '\0';
							Sleep(30);
						}
						if (static_cast<int>(choose) == ESC)
						{
							return false;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && correct == false) // if user typed key_down // key =  -32
				{
					correct = true;
				}
				if (static_cast<int> (choose) == RIGHT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == LEFT && correct == true)
				{
					correct = false;
				}
				if (static_cast<int> (choose) == UP && correct == true) // second_key_down 72
				{
					correct = false;
					move = '2';
					break;
				}
				if (static_cast<int> (choose) == DOWN && correct == true)  // second_key_down 80
				{
					correct = false;
					move = '4';
					break;
				}
			}
		}break;
		case '4':
		{
			system("cls");
			cout << "\033[97m\n\n\n\n\t\t\t\t\t    -------------------------------------\n";
			cout << "\t\t\t\t\t    | \033[36mCreating an \033[96mAdministrator\033[36m account\033[97m |\n";
			cout << "\t\t\t\t\t --------------------------------------------\n";
			cout << "\t\t\t\t\t | \033[92mThink of a \033[93mlogin \033[97m(\033[33mlength\033[97m 4 to 20)        |\n";
			cout << "\t\t\t\t\t | \033[92mThink of a \033[94mpassword \033[97m(\033[33mlength\033[97m 6 to 28)     |\n";
			cout << "\t\t\t\t\t | \033[92mThink of a \033[95mrecovery key \033[97m(\033[33mlength\033[97m 4 to 10) |\n";
			cout << "\t\t\t\t      --------------------------------------------------\n";
			cout << "\t\t\t\t      | \033[95mLogin\033[97m: " << admin_.login << setw(34 - strlen(admin_.login)) << " |";
			if (strlen(admin_.login) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.login, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
			else { cout << " \033[92mDONE\033[97m |"; }
			cout << "\n\t\t\t\t      | \033[94mPassword\033[97m: ";
			for (int e = 0; e < strlen(admin_.password); e++)
			{
				cout << "*";
			}
			cout << setw(31 - strlen(admin_.password)) << " |";
			if (strlen(admin_.password) < 6 || strcmp(admin_.login, admin_.password) == 0 || strcmp(admin_.password, admin_.rec_key) == 0) { cout << " \033[91mDONE\033[97m |"; }
			else { cout << " \033[92mDONE\033[97m |"; }

			cout << "\n\t\t\t\t      | \033[96mKey Recovery\033[97m: " << admin_.rec_key << setw(27 - strlen(admin_.rec_key)) << " |";
			if (strlen(admin_.rec_key) < 4 || strcmp(admin_.login, admin_.rec_key) == 0 || strcmp(admin_.rec_key, admin_.password) == 0) { cout << " \033[91mDONE\033[97m |"; }
			else { cout << " \033[92mDONE\033[97m |"; }
			if (strlen(admin_.login) >= 4 && strlen(admin_.password) >= 6 && strlen(admin_.rec_key) >= 4 && strcmp(admin_.login, admin_.password) != 0 && strcmp(admin_.login, admin_.rec_key) != 0 && strcmp(admin_.password, admin_.rec_key) != 0)
			{
				cout << "\n\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t\t           | \033[102mAccept and continue\033[0m\033[97m |              \n";
				cout << "\t\t\t\t\t           -----------------------\n";
			}
			else
			{
				cout << "\n\t\t\t\t      --------------------------------------------------\n";
				cout << "\t\t\t\t\t           | \033[101mAccept and continue\033[0m\033[97m |              \n";
				cout << "\t\t\t\t\t           -----------------------\n";
			}
			if (strlen(admin_.rec_key) > 0)
			{
				if (strcmp(admin_.login, admin_.rec_key) == 0)
				{
					cout << "\t\t\t\t\t           \033[91mkey recovery and Login must be different!\n";
				}
				if (strcmp(admin_.rec_key, admin_.password) == 0)
				{
					cout << "\t\t\t\t\t           \033[91mkey recovery and password must be different!\n";
				}
			}
			choose = _getch();
			if (static_cast<int> (choose) == UP)
			{
				move = '3';
				break;
			}
			if (static_cast<int> (choose) == ESC)
			{
				return false;
			}
			if (static_cast<int> (choose) == DOWN)
			{
				correct = false;
				break;
			}
			if (static_cast<int> (choose) == ENTER)
			{
				if (strlen(admin_.login) >= 4 && strlen(admin_.password) >= 6 && strlen(admin_.rec_key) >= 4 && strcmp(admin_.login, admin_.password) != 0 && strcmp(admin_.login, admin_.rec_key) != 0 && strcmp(admin_.password, admin_.rec_key) != 0)
				{
					system("cls");
					cout << "\n\n\n\n\t\t\t\t\t-------------------------------------------\n";
					cout << "\t\t\t\t\t|     \033[94mYou are successfully registered\033[97m     |\n";
					cout << "\t\t\t\t\t|            \033[93mLogin information\033[97m            |\n";
					cout << "\t\t\t\t\t-------------------------------------------\n";
					cout << "\t\t\t\t\t| \033[94mLogin\033[97m: " << admin_.login << setw(35 - strlen(admin_.login)) << " |\n";
					cout << "\t\t\t\t\t| \033[94mPassword\033[97m: " << admin_.password << setw(32 - strlen(admin_.password)) << " |\n";
					cout << "\t\t\t\t\t| \033[92mRecovery Key\033[97m: " << admin_.rec_key << setw(28 - strlen(admin_.rec_key)) << " |\n";
					cout << "\t\t\t\t --------------------------------------------------------\n";
					cout << "\t\t\t\t | \033[96mTo log in to the \033[32mAdmin\033[96m account you need \033[97m:            |\n";
					cout << "\t\t\t\t --------------------------------------------------------\n";
					cout << "\t\t\t\t | 1. \033[94mPress \033[35many button\033[94m to go to the user reg/login menu \033[97m|\n";
					cout << "\t\t\t\t | 2. \033[94mSelect \033[91mSign in                                    \033[97m|\n";
					cout << "\t\t\t\t | 3. \033[36mEnter \033[92mLogin \033[36mand \033[92mPassword \033[36mfrom Admin               \033[97m|\n";
					cout << "\t\t\t\t --------------------------------------------------------\n";
					save_admin_acc(admin_);
					_getch();
					return true;
				}
			}
		}break;
		default:;
		}
	}
}

void Context_Menu::Creating_Menu::creating_user_account(Context_Menu& lc_database)
{
	char page = '1';
	char move = '1';
	char choose;
	bool un = false;
	bool key_move = false;

	Account acc;

	while (true)
	{
		switch (page)
		{
			/* Login information */
		case '1':
		{
			switch (move)
			{
			case '1': // Entering Login
			{
				for (size_t i = strlen(acc.login);;)
				{
					// Show
					system("cls");
					cout << "\n\n \t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       -----------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration  \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       -----------------------------\n";
					cout << " \t\t       Login        ( 4 - 20 ) | \033[93mThink of a login password \033[97m|\n";
					cout << " \t\t       Password     ( 6 - 28 ) | \033[93mto log in to your account\033[97m |\n";
					cout << " \t\t\t                 ------------------------------------------\n";
					cout << " \t\t\t                \033[104m" << char(26) << "\033[0m\033[97m| \033[33mLogin\033[97m: " << acc.login << setw(33 - strlen(acc.login)) << " |";

					if (strlen(acc.login) < 4)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]";
					}

					if (strcmp(acc.login, lc_database.admin_.login) == 0)
					{
						cout << "\033[91m The login already exists\033[97m";
						un = true;
					}
					else
					{
						un = false;
					}
					if (un == false) {
						for (auto tmp_login : lc_database.logins_)
						{
							if (strcmp(tmp_login.c_str(), acc.login) == 0)
							{
								cout << "\033[91m The login already exists\033[97m";
								un = true;
								break;
							}
							else
							{
								un = false;
							}
						}
					}

					cout << "\n";
					cout << " \t\t\t                 | \033[94mPassword\033[97m: "; for (int i = 0; i < strlen(acc.password); i++) { cout << "*"; } cout << setw(30 - strlen(acc.password)) << " |";
					if (strlen(acc.password) < 6)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]";
					}
					if (strcmp(acc.login, acc.password) == 0 && strlen(acc.login) > 0)
					{
						cout << "\033[91m Password and login match\033[97m";
					}
					cout << "\n";
					cout << " \t\t\t                 ------------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
						{
							if (i < login_len - 1)
							{
								acc.login[i] = choose;
								++i;
								acc.login[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.login[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						if (un == false && strlen(acc.login) > 3 && strlen(acc.password) > 5 && strcmp(acc.password, acc.login) != 0)
						{
							key_move = false;
							page = '2';
							move = '1';
							break;
						}
						else
						{
							key_move = false;
						}
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '2';
						break;
					}
				}
			}break;
			case '2': // Entering Password
			{
				for (size_t i = strlen(acc.password);;)
				{
					// Show
					system("cls");
					cout << "\n\n \t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       -----------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration  \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       -----------------------------\n";
					cout << " \t\t       Login        ( 4 - 20 ) | \033[93mThink of a login password \033[97m|\n";
					cout << " \t\t       Password     ( 6 - 28 ) | \033[93mto log in to your account\033[97m |\n";
					cout << " \t\t\t                 ------------------------------------------\n";
					cout << " \t\t\t                 | \033[33mLogin\033[97m: " << acc.login << setw(33 - strlen(acc.login)) << " |";
					if (strlen(acc.login) < 4)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]";
					}
					if (un == true)
					{
						cout << "\033[91m The login already exists\033[97m";
					}
					cout << "\n";
					cout << " \t\t\t                \033[104m" << char(26) << "\033[0m\033[97m| \033[94mPassword\033[97m: ";
					for (int e = 0; e < strlen(acc.password); e++)
					{
						cout << "*";
					}
					if (strlen(acc.password) > 0)
					{
						cout << "\b \b";
						cout << acc.password[strlen(acc.password) - 1];
					}
					cout << setw(30 - strlen(acc.password)) << " |";

					if (strlen(acc.password) < 6)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]";
					}
					if (strcmp(acc.login, acc.password) == 0 && strlen(acc.password) > 1)
					{
						cout << "\033[91m Password and login match";
					}
					cout << "\n";
					cout << " \t\t\t                 \033[97m------------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";

					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '!' || choose == '@' || choose == '#' || choose == '%')
						{
							if (i < pass_len - 1)
							{
								acc.password[i] = choose;
								++i;
								acc.password[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.password[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						if (un == false && strlen(acc.login) > 3 && strlen(acc.password) > 5 && strcmp(acc.password, acc.login) != 0)
						{
							key_move = false;
							page = '2';
							move = '1';
							break;
						}
						else
						{
							key_move = false;
						}
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '1';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}break;
			default:;
			}
		}break;
		/* Personal Information */
		case '2':
		{
			switch (move)
			{
			case '1': /* Entering Name*/
			{
				for (size_t i = strlen(acc.Name);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter  your\033[97m:              |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                  \033[104m" << char(26) << "\033[0m\033[97m| \033[93mName\033[97m: " << acc.Name << setw(31 - strlen(acc.Name)) << " |\n";
					cout << " \t\t\t                   | \033[93mSurname\033[97m: " << acc.Surname << setw(28 - strlen(acc.Surname)) << " |\n";
					cout << " \t\t\t                   | \033[93mPatronymic\033[97m: " << acc.Patronymic << setw(25 - strlen(acc.Patronymic)) << " |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
						{
							if (i < name_len - 1)
							{
								acc.Name[i] = choose;
								++i;
								acc.Name[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.Name[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '3';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '1';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '2';
						break;
					}
				}
			}break;
			case '2': /* Entering Surname*/
			{
				for (size_t i = strlen(acc.Surname);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter  your\033[97m:              |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                   | \033[93mName\033[97m: " << acc.Name << setw(31 - strlen(acc.Name)) << " |\n";
					cout << " \t\t\t                  \033[104m" << char(26) << "\033[0m\033[97m| \033[93mSurname\033[97m: " << acc.Surname << setw(28 - strlen(acc.Surname)) << " |\n";
					cout << " \t\t\t                   | \033[93mPatronymic\033[97m: " << acc.Patronymic << setw(25 - strlen(acc.Patronymic)) << " |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
						{
							if (i < sur_len - 1)
							{
								acc.Surname[i] = choose;
								++i;
								acc.Surname[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.Surname[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '3';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '1';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '1';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '3';
						break;
					}
				}
			}break;
			case '3':/* Entering Patronymic*/
			{
				for (size_t i = strlen(acc.Patronymic);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter  your\033[97m:              |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                   | \033[93mName\033[97m: " << acc.Name << setw(31 - strlen(acc.Name)) << " |\n";
					cout << " \t\t\t                   | \033[93mSurname\033[97m: " << acc.Surname << setw(28 - strlen(acc.Surname)) << " |\n";
					cout << " \t\t\t                  \033[104m" << char(26) << "\033[0m\033[97m| \033[93mPatronymic\033[97m: " << acc.Patronymic << setw(25 - strlen(acc.Patronymic)) << " |\n";
					cout << " \t\t\t                   --------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_')
						{
							if (i < patron_len - 1)
							{
								acc.Patronymic[i] = choose;
								++i;
								acc.Patronymic[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.Patronymic[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '3';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '1';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '2';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}break;
			default:;
			}
		}break;
		/* Date of birth */
		case '3':
		{
			switch (move)
			{
			case '1': /* Entering Day */
			{
				for (size_t i = strlen(acc.day);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter your \033[96mdate of birth \033[97m |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                      \033[104m" << char(26) << "\033[0m\033[97m| \033[33mDay\033[97m: " << acc.day << setw(24 - strlen(acc.day)) << " |\n";
					cout << " \t\t\t                       | \033[33mMonth\033[97m: " << acc.month << setw(22 - strlen(acc.month)) << " |\n";
					cout << " \t\t\t                       | \033[95mYear\033[97m: " << acc.year << setw(23 - strlen(acc.year)) << " |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if (choose >= '0' && choose <= '9')
						{
							if (i < day_l - 1)
							{
								acc.day[i] = choose;
								++i;
								acc.day[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.day[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '4';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '2';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '2';
						break;
					}
				}
			}break;
			case '2': /* Entering Month */
			{
				for (size_t i = strlen(acc.month);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter your \033[96mdate of birth \033[97m |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[33mDay\033[97m: " << acc.day << setw(24 - strlen(acc.day)) << " |\n";
					cout << " \t\t\t                      \033[104m" << char(26) << "\033[0m\033[97m| \033[33mMonth\033[97m: " << acc.month << setw(22 - strlen(acc.month)) << " |\n";
					cout << " \t\t\t                       | \033[95mYear\033[97m: " << acc.year << setw(23 - strlen(acc.year)) << " |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if (choose >= '0' && choose <= '9')
						{
							if (i < month_l - 1)
							{
								acc.month[i] = choose;
								++i;
								acc.month[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.month[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '4';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '2';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '1';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '3';
						break;
					}
				}
			}break;
			case '3': /* Entering Year */
			{
				for (size_t i = strlen(acc.year);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter your \033[96mdate of birth \033[97m |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[33mDay\033[97m: " << acc.day << setw(24 - strlen(acc.day)) << " |\n";
					cout << " \t\t\t                       | \033[33mMonth\033[97m: " << acc.month << setw(22 - strlen(acc.month)) << " |\n";
					cout << " \t\t\t                      \033[104m" << char(26) << "\033[0m\033[97m| \033[95mYear\033[97m: " << acc.year << setw(23 - strlen(acc.year)) << " |\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if (choose >= '0' && choose <= '9')
						{
							if (i < year_l - 1)
							{
								acc.year[i] = choose;
								++i;
								acc.year[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.year[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '4';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '2';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '2';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}break;
			}
		}break;
		/* Place of residence */
		case '4':
		{
			switch (move)
			{
			case '1': /* Entering City */
			{
				for (size_t i = strlen(acc.City);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter \033[96mPlace of residence  \033[97m|\n";
					cout << " \t\t\t                     ----------------------------------\n";
					cout << " \t\t\t                    \033[104m" << char(26) << "\033[0m\033[97m| \033[95mCity\033[97m: " << acc.City << setw(27 - strlen(acc.City)) << " |\n";
					cout << " \t\t\t                     | \033[92mCountry\033[97m: " << acc.Country << setw(24 - strlen(acc.Country)) << " |\n";
					cout << " \t\t\t                     ----------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
						{
							if (i < city_length - 1)
							{
								acc.City[i] = choose;
								++i;
								acc.City[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.City[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '5';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '3';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '2';
						break;
					}
				}
			}break;
			case '2': /* Entering Country */
			{
				for (size_t i = strlen(acc.Country);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       |  \033[94mEnter \033[96mPlace of residence  \033[97m|\n";
					cout << " \t\t\t                     ----------------------------------\n";
					cout << " \t\t\t                     | \033[95mCity\033[97m: " << acc.City << setw(27 - strlen(acc.City)) << " |\n";
					cout << " \t\t\t                    \033[104m" << char(26) << "\033[0m\033[97m| \033[92mCountry\033[97m: " << acc.Country << setw(24 - strlen(acc.Country)) << " |\n";
					cout << " \t\t\t                     ----------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ')
						{
							if (i < country_length - 1)
							{
								acc.Country[i] = choose;
								++i;
								acc.Country[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.Country[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '5';
						break;
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '3';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '1';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}break;
			default:;
			}
		}break;
		/* Contact Information */
		case'5':
		{
			switch (move)
			{
			case '1': /* Entering email */
			{
				for (size_t i = strlen(acc.email);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[94mEnter  \033[96mContact Information \033[97m|\n";
					cout << " \t\t\t                  ----------------------------------------\n";
					cout << " \t\t\t                 \033[104m" << char(26) << "\033[0m\033[97m| \033[95mEmail\033[97m: " << acc.email << setw(31 - strlen(acc.email)) << " |";
					if (regex_match(acc.email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) != 1)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]\033[97m";
					}
					cout << "\n";
					cout << " \t\t\t                  | \033[96mPhone-n\033[97m: " << acc.phone_number << setw(29 - strlen(acc.phone_number)) << " |";
					if (strlen(acc.phone_number) < 8)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]\033[97m";
					}
					cout << '\n';
					cout << " \t\t\t                  ----------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == '_' || choose == '@' || choose == '.')
						{
							if (i < email_length - 1)
							{
								acc.email[i] = choose;
								++i;
								acc.email[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.email[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						if (regex_match(acc.email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) == 1 && strlen(acc.Name) > 1 && strlen(acc.Surname) > 1 && strlen(acc.Patronymic) > 1 && strlen(acc.phone_number) > 6 && strlen(acc.Country) > 1 && strlen(acc.City) > 1 && strlen(acc.day) > 1 && strlen(acc.month) > 1 && strlen(acc.year) > 1 && strlen(acc.email) > 1)
						{
							key_move = false;
							page = '6';
							move = '1';
							break;
						}
						else
						{
							cout << " \t\t\t\t               \033[91mNot all the data is specified\033[97m\n";
							this_thread::sleep_for(chrono::seconds(1));
							key_move = false;
							page = '5';
							move = '1';
							break;
						}
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '4';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						move = '2';
						break;
					}
				}
			}break;
			case '2':  /* Entering phone number */
			{
				for (size_t i = strlen(acc.phone_number);;)
				{
					// Show
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[92mRegistration   \033[36mNew Account \033[97m|\n";
					cout << " \t\t\t                       ------------------------------\n";
					cout << " \t\t\t                       | \033[94mEnter  \033[96mContact Information \033[97m|\n";
					cout << " \t\t\t                  ----------------------------------------\n";
					cout << " \t\t\t                  | \033[95mEmail\033[97m: " << acc.email << setw(31 - strlen(acc.email)) << " |";
					if (regex_match(acc.email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) != 1)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]\033[97m";
					}
					cout << "\n";
					cout << " \t\t\t                 \033[104m" << char(26) << "\033[0m\033[97m| \033[96mPhone-n\033[97m: " << acc.phone_number << setw(29 - strlen(acc.phone_number)) << " |";
					if (strlen(acc.phone_number) < 8)
					{
						cout << "\033[97m[\033[91mD\033[97m]";
					}
					else
					{
						cout << "\033[97m[\033[92mD\033[97m]\033[97m";
					}
					cout << '\n';
					cout << " \t\t\t                  ----------------------------------------\n";
					cout << " \t\t\t                         | \033[37mPage\033[97m:   " << page << "  of   6     |\n";
					cout << " \t\t\t                         -------------------------\n";
					choose = _getch();

					if (static_cast<int> (choose) != -32 && key_move == false)
					{
						if ((choose >= '0' && choose <= '9') || choose == '+')
						{
							if (i < phone_n_length - 1)
							{
								acc.phone_number[i] = choose;
								++i;
								acc.phone_number[i] = '\0';
							}
						}
						else
						{
							if (choose == '\b' && i > 0) // if user typed backspace
							{
								--i;
								acc.phone_number[i] = '\0';
								Sleep(30);
							}
							if (static_cast<int>(choose) == ESC)
							{
								return;
							}
						}
					}
					if (static_cast<int> (choose) == -32 && key_move == false) // if user typed key_down // first_key_down -32
					{
						key_move = true;
					}
					if (static_cast<int> (choose) == RIGHT && key_move == true)
					{
						if (regex_match(acc.email, regex(R"(([\w-\.]+)@((?:\w+\.)+)([a-zA-Z]{2,4}))")) == 1 && strlen(acc.Name) > 1 && strlen(acc.Surname) > 1 && strlen(acc.Patronymic) > 1 && strlen(acc.phone_number) > 6 && strlen(acc.Country) > 1 && strlen(acc.City) > 1 && strlen(acc.day) > 1 && strlen(acc.month) > 1 && strlen(acc.year) > 1 && strlen(acc.email) > 1)
						{
							key_move = false;
							page = '6';
							move = '1';
							break;
						}
						else
						{
							cout << " \t\t\t\t               \033[91mNot all the data is specified\033[97m\n";
							this_thread::sleep_for(chrono::seconds(1));
							key_move = false;
							page = '5';
							move = '1';
							break;
						}
					}
					if (static_cast<int> (choose) == LEFT && key_move == true)
					{
						key_move = false;
						move = '1';
						page = '4';
						break;
					}
					if (static_cast<int> (choose) == UP && key_move == true)
					{
						key_move = false;
						move = '1';
						break;
					}
					if (static_cast<int> (choose) == DOWN && key_move == true)  // second_key_down 80
					{
						key_move = false;
						break;
					}
				}
			}break;
			default:;
			}
		}break;
		/* Completing Registration */
		case '6':
		{
			while (true)
			{
				switch (move)
				{
				case '1':
				{
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n\n";
					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    | \033[94mTesting  System \033[97m|\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t| \033[95mCompleting \033[92mRegistration \033[97m|\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t| \033[36m Confirm registration\033[97m?  |\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t|           \033[102mYES\033[0m\033[97m           |\n";
					cout << "\t\t\t\t\t\t|           \033[91mNo\033[97m            |\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
				}break;
				case '2':
				{
					system("cls");
					cout << "\n\n\t\t\t     \033[97m----------------------------------------------------------------\n";
					cout << " \t\t\t     | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << " \t\t\t     ----------------------------------------------------------------\n\n\n";
					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    | \033[94mTesting  System \033[97m|\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t| \033[95mCompleting \033[92mRegistration \033[97m|\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t| \033[36m Confirm registration\033[97m?  |\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
					cout << "\t\t\t\t\t\t|           \033[92mYes\033[97m           |\n";
					cout << "\t\t\t\t\t\t|           \033[101mNo\033[0m\033[97m            |\n";
					cout << "\t\t\t\t\t\t---------------------------\n";
				}break;
				default:;
				}
				choose = _getch();
				if (static_cast<int> (choose) == ENTER)
				{
					if (move == '1')
					{
						lc_database.logins_.emplace(acc.login);
						save_user_login(acc.login);
						thread sv(save_user_acc, acc);
						sv.detach();
						system("cls");
						cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t   \033[97m\033[102mCongratulations, you have registered a new account\033[0m";
						this_thread::sleep_for(chrono::seconds(1));
						return;
					}
					else if (move == '2')
					{
						return;
					}
				}
				else if (static_cast<int> (choose) == ESC)
				{
					return;
				}
				else if (static_cast<int> (choose) == UP)
				{
					move = '1';
					break;
				}
				else if (static_cast<int> (choose) == DOWN)
				{
					move = '2';
				}
				else if (static_cast<int> (choose) == LEFT)
				{
					page = '5';
					move = '1';
					break;
				}
			}
		}break;
		default:;
		}
	}
}