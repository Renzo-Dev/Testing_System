#include "Local_Database.h"

Data::Data()
= default;

Data::~Data()
= default;

Local_Database::Local_Database()
{
	load_data();
}

void Local_Database::load_data()
{
	try
	{
		ifstream load;
		load.open(dir_an_path::Path::Admin::path_sv_adm_data());
		if (load.is_open()) {
			load >> this->admin_.login >> this->admin_.password >> this->admin_.rec_key;
			this->admin_.login[strlen(this->admin_.login) + 1] = '\0';
			this->admin_.password[strlen(this->admin_.password) + 1] = '\0';
			this->admin_.rec_key[strlen(this->admin_.rec_key) + 1] = '\0';
			load.close();
			decryption(this->admin_);
		}
	}
	catch (...)
	{
		string error_text = "Load Admin Data Error!\nPath";
		error_text += dir_an_path::Path::Admin::path_sv_adm_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}

	SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_NORMAL);
	ifstream load;
	try
	{
		load.open(dir_an_path::Path::User::path_list_logins().c_str());
		if (load.is_open())
		{
			string tmp_login;
			while (!load.eof())
			{
				load >> tmp_login;
				logins_.emplace(tmp_login);
			}
			load.close();
			SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
		}
		else
		{
			load.close();
			SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
		}
	}
	catch (...)
	{
		string error_text = "Loading Logins list Error!\nPath";
		error_text += dir_an_path::Path::User::path_list_logins();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}
}

void Local_Database::save_admin_acc(Admin admin)
{
	mutex mtx;
	mtx.lock();
	try
	{
		ofstream save;
		save.open(dir_an_path::Path::Admin::path_sv_adm_data(), ios::trunc);
		if (save.is_open())
		{
			// encryption
			encryption(admin);

			save << admin.login << endl << admin.password << endl << admin.rec_key << endl;
			save.close();
			mtx.unlock();
		}
		else
		{
			save.close();
			mtx.unlock();
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save Admin Data Error!\nPath";
		error_text += dir_an_path::Path::Admin::path_sv_adm_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}
}

void Local_Database::save_user_acc(const Account& user)
{
	mutex mtx;
	mtx.lock();
	try
	{
		ofstream save;
		fs::create_directories(dir_an_path::Directories::User::save_user_folder(user.login));
		save.open(dir_an_path::Path::User::path_sv_user_acc(user.login));
		if (save.is_open())
		{
			encryption(user);
			for (size_t i = 0; i < strlen(user.Country); i++)
			{
				if (user.Country[i] == ' ')
				{
					user.Country[i] = '#';
				}
			}
			save << user.login << endl << user.password << endl << user.Name << endl << user.Surname << endl << user.Patronymic << endl << user.day << endl << user.month << endl << user.year << endl << user.City << endl << user.Country << endl << user.email << endl << user.phone_number << endl;
			save.close();
			mtx.unlock();
		}
		else
		{
			fs::remove_all(dir_an_path::Directories::User::save_user_folder(user.login));
			save.close();
			mtx.unlock();
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save User Data Error!\nPath";
		error_text += dir_an_path::Directories::User::save_user_folder(user.login);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}
}

Local_Database::~Local_Database()
= default;

void Local_Database::decryption(Admin& admin)
{
	SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_NORMAL);

	size_t size = strlen(admin.login);

	auto dec_key = new char[size + 1];

	try
	{
		ifstream load_dec_key;
		load_dec_key.open(dir_an_path::Path::Admin::path_adm_enc_key().c_str());
		if (load_dec_key.is_open())
		{
			load_dec_key >> dec_key;
			for (size_t i = 0; i < size; i++)
			{
				admin.login[i] = admin.login[i] - dec_key[i];
			}
			load_dec_key.close();
			delete[] dec_key;
		}
		else
		{
			SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
			load_dec_key.close();
			delete[] dec_key;
		}
	}
	catch (...)
	{
		string error_text = "Load Admin Decryption Key Error!\nPath";
		error_text += dir_an_path::Path::Admin::path_sv_adm_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
		return;
	}

	try
	{
		ifstream load_dec_key;
		load_dec_key.open(dir_an_path::Path::Admin::path_adm_enc_key().c_str());
		if (load_dec_key.is_open())
		{
			load_dec_key.seekg(static_cast<streamoff>(size));
			size = strlen(admin.password);
			dec_key = new char[size + 1];
			dec_key[0] = '\0';
			load_dec_key >> dec_key;
			for (size_t i = 0; i < size; i++)
			{
				admin.password[i] = admin.password[i] - dec_key[i];
			}
			SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
			load_dec_key.close();
			delete[] dec_key;
		}
		else
		{
			string error_text = "Load Admin Decryption Key Error!\nPath";
			error_text += dir_an_path::Path::Admin::path_sv_adm_data();
			MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
			SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
			load_dec_key.close();
			delete[] dec_key;
		}
	}
	catch (...)
	{
		SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
		return;
	}
}

void Local_Database::decryption(const string& login, Account& account)
{
	SetFileAttributesA(dir_an_path::Path::User::path_acc_enc_key(login.c_str()).c_str(), FILE_ATTRIBUTE_NORMAL);

	size_t size = strlen(account.login);

	auto dec_key = new char[size + 1];

	try
	{
		ifstream load_dec_key;
		load_dec_key.open(dir_an_path::Path::User::path_acc_enc_key(login.c_str()).c_str());
		if (load_dec_key.is_open())
		{
			load_dec_key >> dec_key;
			for (size_t i = 0; i < size; i++)
			{
				account.login[i] = account.login[i] - dec_key[i];
			}
			load_dec_key.close();
			delete[] dec_key;
		}
		else
		{
			load_dec_key.close();
			delete[] dec_key;
		}
	}
	catch (...)
	{
		string error_text = "Load User encryption Key Error!\nPath";
		error_text += dir_an_path::Path::User::path_acc_enc_key(login.c_str());
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}

	try
	{
		ifstream load_dec_key;
		load_dec_key.open(dir_an_path::Path::User::path_acc_enc_key(login.c_str()).c_str());
		if (load_dec_key.is_open())
		{
			load_dec_key.seekg(static_cast<streamoff>(size));
			size = strlen(account.password);
			dec_key = new char[size + 1];
			dec_key[0] = '\0';
			load_dec_key >> dec_key;
			for (size_t i = 0; i < size; i++)
			{
				account.password[i] = account.password[i] - dec_key[i];
			}
			load_dec_key.close();
			SetFileAttributesA(dir_an_path::Path::User::path_acc_enc_key(login.c_str()).c_str(), FILE_ATTRIBUTE_HIDDEN);
			delete[] dec_key;
			return;
		}
		else
		{
			load_dec_key.close();
			SetFileAttributesA(dir_an_path::Path::User::path_acc_enc_key(login.c_str()).c_str(), FILE_ATTRIBUTE_HIDDEN);
			delete[] dec_key;
			return;
		}
	}
	catch (...)
	{
		return;
	}
}

void Local_Database::encryption(const Account& account)
{
	srand(time(0));

	string tmp_login = account.login;

	size_t size = strlen(account.login); // Login Length

	auto* enc_key = new char[size + 1];  // key of encryption

	enc_key[0] = '\0';
	char result = ' '; // result acc.login + enc_key -> (char)

	// Encrypting login
	for (size_t i = 0; i < size; i++)
	{
		enc_key[i] = rand() % 200 + 50;
		result = account.login[i] + enc_key[i];
		if ((result >= 'a' && result <= 'z') || (result >= 'A' && result <= 'Z'))
		{
			account.login[i] = account.login[i] + enc_key[i];
			enc_key[i + 1] = '\0';
		}
		else
		{
			i--;
		}
	}

	/*
	 * Saving enc key for login
	 */

	ofstream save_enc_key;
	try
	{
		save_enc_key.open(dir_an_path::Path::User::path_acc_enc_key(tmp_login.c_str()), ios::trunc);
		if (save_enc_key.is_open())
		{
			for (size_t i = 0; i < size; i++)
			{
				save_enc_key << enc_key[i];
			}
			save_enc_key << endl;
			save_enc_key.close();
		}
		else
		{
			save_enc_key.close();
			delete[] enc_key;
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save User encryption Key Error!\nPath";
		error_text += dir_an_path::Path::User::path_acc_enc_key(tmp_login.c_str());
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}

	delete[] enc_key; // delete the old login key, for the password key
	enc_key = nullptr;

	size = strlen(account.password);  // Password length

	enc_key = new char[size + 1];
	enc_key[0] = '\0';

	// Encrypting password
	for (size_t i = 0; i < size; i++)
	{
		enc_key[i] = rand() % 200 + 50;
		result = account.password[i] + enc_key[i];
		if ((result >= 'a' && result <= 'z') || (result >= 'A' && result <= 'Z'))
		{
			account.password[i] = account.password[i] + enc_key[i];
			enc_key[i + 1] = '\0';
		}
		else
		{
			i--;
		}
	}

	/*
	 * Saving enc key for password
	 */

	try
	{
		save_enc_key.open(dir_an_path::Path::User::path_acc_enc_key(tmp_login.c_str()), ios::app);
		if (save_enc_key.is_open())
		{
			for (size_t i = 0; i < size; i++)
			{
				save_enc_key << enc_key[i];
			}
			save_enc_key.close();
		}
		else
		{
			delete[] enc_key;
			save_enc_key.close();
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save User encryption Key Error!\nPath";
		error_text += dir_an_path::Path::User::path_acc_enc_key(tmp_login.c_str());
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}

	delete[] enc_key;

	SetFileAttributesA(dir_an_path::Path::User::path_acc_enc_key(tmp_login.c_str()).c_str(), FILE_ATTRIBUTE_HIDDEN);
}

bool Local_Database::save_user_login(const string& login)
{
	SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_NORMAL);
	std::ofstream save;
	try
	{
		save.open(dir_an_path::Path::User::path_list_logins().c_str(), ios::app);
		if (save.is_open())
		{
			save << login << endl;
			save.close();
			SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
			return true;
		}
		else
		{
			save.close();
			SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save login list Error!\nPath";
		error_text += dir_an_path::Path::User::path_list_logins();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return false;
	}
}

auto Local_Database::save_logins(const set<string>& logins_) -> bool
{
	SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_NORMAL);
	if (logins_.size() > 0) {
		ofstream save;
		try
		{
			save.open(dir_an_path::Path::User::path_list_logins().c_str(), ios::trunc);
			if (save.is_open())
			{
				for (auto i : logins_)
				{
					save << i << endl;
				}
				save.close();
				SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
				return true;
			}
			else
			{
				save.close();
				SetFileAttributesA(dir_an_path::Path::User::path_list_logins().c_str(), FILE_ATTRIBUTE_HIDDEN);
				throw 1;
			}
		}
		catch (...)
		{
			string error_text = "Save login list Error!\nPath";
			error_text += dir_an_path::Path::User::path_list_logins();
			MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
			return false;
		}
	}
	else
	{
		fs::remove(dir_an_path::Path::User::path_list_logins().c_str());
	}
}

bool Local_Database::load_user_data(const string& login, Account& acc)
{
	try
	{
		ifstream load;
		load.open(dir_an_path::Path::User::path_sv_user_acc(login.c_str()));
		if (load.is_open())
		{
			load >> acc.login >> acc.password >> acc.Name >> acc.Surname >> acc.Patronymic >> acc.day >> acc.month >> acc.year >> acc.City >> acc.Country >> acc.email >> acc.phone_number;
			decryption(login, acc);
			for (size_t i = 0; i < strlen(acc.Country); i++)
			{
				if (acc.Country[i] == '#')
				{
					acc.Country[i] = ' ';
				}
			}
			load.close();
			return true;
		}
		else
		{
			load.close();
			return false;
		}
	}
	catch (...)
	{
		string error_text = "load user data Error!\nPath";
		error_text += dir_an_path::Path::User::path_sv_user_acc(login.c_str());
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return false;
	}
}

bool Local_Database::recovery_admin_account()
{
	// char key_rec-tmp
	char* key_rec_tmp = new char[rec_key_length];
	key_rec_tmp[0] = '\0';

	char choose;

	for (size_t i = strlen(key_rec_tmp);;)
	{
		// Show
		system("cls");
		cout << "\n\t\t\t\t-----------------------------------------------------------\n";
		cout << "\t\t\t\t|\033[94mCONTROL\033[97m| \033[91mESC\033[97m - Exit to Main Menu | \033[92mEnter\033[97m - Confirm entry |\n";
		cout << "\t\t\t\t-----------------------------------------------------------\n";
		cout << "\n\n\n\n\t\t\t\t\t            ------------------\n";
		cout << "\t\t\t\t\t            | \033[96mTesting System \033[97m|\n";
		cout << "\t\t\t\t\t        --------------------------\n";
		cout << "\t\t\t\t\t        | \033[95mRestore Admin  Account \033[97m|\n";
		cout << "\t\t\t\t\t      ------------------------------\n";
		cout << "\t\t\t\t\t      |   \033[93mEnter the recovery key  \033[97m |\n";
		cout << "\t\t\t\t\t      ------------------------------\n";
		cout << "\t\t\t\t\t           | \033[94mKey\033[97m: " << key_rec_tmp << setw(rec_key_length + 3 - strlen(key_rec_tmp)) << " |\n";
		cout << "\t\t\t\t\t           --------------------\n";
		choose = _getch();

		if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9'))
		{
			if (i < rec_key_length - 1)
			{
				key_rec_tmp[i] = choose;
				++i;
				key_rec_tmp[i] = '\0';
			}
		}
		else
		{
			if (choose == '\b' && i > 0) // if user typed backspace
			{
				--i;
				key_rec_tmp[i] = '\0';
				Sleep(30);
			}
			if (static_cast<int>(choose) == ESC)
			{
				delete[] key_rec_tmp;
				return false;
			}
			if (static_cast<int>(choose) == ENTER)
			{
				if (strcmp(admin_.rec_key, key_rec_tmp) == 0)
				{
					char move = '2';
					while (true)
					{
						switch (move)
						{
						case '2':
						{
							system("cls");
							cout << "\n\n\n\n\n\t\t\t\t--------------------------------------------------------\n";
							cout << "\t\t\t\t|      \033[96mDo you really want to restore your \033[93maccount\033[97m?   \033[97m  |\n";
							cout << "\t\t\t\t| \033[94mWhen restoring an account. \033[91mAll data will be deleted!\033[97m |\n";
							cout << "\t\t\t\t--------------------------------------------------------\n";
							cout << "\t\t\t\t\t\t      | \033[94mConfirm\033[97m: |\n";
							cout << "\t\t\t\t\t\t      ------------\n";
							cout << "\t\t\t\t\t\t      | \033[92mYes   \033[97m\033[101mNo\033[0m\033[97m |\n";
							cout << "\t\t\t\t\t\t      ------------\n";
						}break;
						case '1':
						{
							system("cls");
							cout << "\n\n\n\n\n\t\t\t\t--------------------------------------------------------\n";
							cout << "\t\t\t\t|      \033[96mDo you really want to restore your \033[93maccount\033[97m?   \033[97m  |\n";
							cout << "\t\t\t\t| \033[94mWhen restoring an account. \033[91mAll data will be deleted!\033[97m |\n";
							cout << "\t\t\t\t--------------------------------------------------------\n";
							cout << "\t\t\t\t\t\t      | \033[94mConfirm\033[97m: |\n";
							cout << "\t\t\t\t\t\t      ------------\n";
							cout << "\t\t\t\t\t\t      | \033[102mYes\033[0m\033[97m   \033[91mNo\033[97m |\n";
							cout << "\t\t\t\t\t\t      ------------\n";
						}break;
						default:;
						}
						choose = _getch();
						if (static_cast<int>(choose) == LEFT)
						{
							move = '1';
						}
						if (static_cast<int>(choose) == RIGHT)
						{
							move = '2';
						}
						if (static_cast<int>(choose) == ENTER)
						{
							if (move == '2')
							{
								return false;
							}
							if (move == '1')
							{
								for (int i = 5; i > 0; i--)
								{
									system("cls");
									cout << "\n\n\n\n\t\t\t       -----------------------------------------------------------\n";
									cout << "\t\t\t       | \033[36mYou have \033[92msuccessfully deleted the \033[96mAdministrator account\033[97m |\n";
									cout << "\t\t\t       |         \033[95mTo create it again, \033[93mrestart\033[95m the program        \033[97m |\n";
									cout << "\t\t\t       -----------------------------------------------------------\n";
									cout << "\t\t\t             " << i;
									this_thread::sleep_for(chrono::seconds(1));
								}
								filesystem::remove(dir_an_path::Path::Admin::path_adm_enc_key().c_str());
								filesystem::remove(dir_an_path::Path::Admin::path_sv_adm_data().c_str());
								delete[] this->admin_.login;
								this->admin_.login = new char[login_len];
								this->admin_.login[0] = '\0';
								delete[] this->admin_.password;
								this->admin_.password = new char[pass_len];
								this->admin_.password[0] = '\0';
								delete[] this->admin_.rec_key;
								this->admin_.rec_key = new char[rec_key_length];
								this->admin_.rec_key[0] = '\0';
								return true;
							}
						}
					}
				}
				else
				{
					cout << "\t\t\t\t\t             \033[91mRecovery key wrong!\033[97m\n";
					cout << "\t\t\t\t\t          \033[32mPress Any button,to \033[91mexit\033[96m !\033[97m\n";
					_getch();
					return false;
				}
			}
		}
	}
}

string Local_Database::found_user(char* buffer, const set<string>& logins_, char type_found)
{
	if (type_found == '1')  // Search by Login
	{
		for (const auto& it : logins_)
		{
			if (strcmp(it.c_str(), buffer) == 0)
			{
				return it;
			}
		}
		return "\0";
	}
	if (type_found == '2') // Search by Phone-number
	{
		Account temp;
		for (auto& it : logins_)
		{
			load_user_data(it.c_str(), temp);
			if (strcmp(temp.phone_number, buffer) == 0)
			{
				return it.c_str();
			}
		}
		return "\0";
	}
	if (type_found == '3') // Search by Email
	{
		Account temp;
		for (auto& it : logins_)
		{
			load_user_data(it.c_str(), temp);
			if (strcmp(temp.email, buffer) == 0)
			{
				return it.c_str();
			}
		}
		return "\0";
	}
	return "\0";
}

void Local_Database::encryption(Admin& admin)
{
	srand(time(0));

	size_t size = strlen(admin.login); // Login Length

	auto* enc_key = new char[size + 1];  // key of encryption

	enc_key[0] = '\0';
	char result = ' '; // result adm.login + enc_key -> (char)

	// Encrypting administrator login
	for (size_t i = 0; i < size; i++)
	{
		enc_key[i] = rand() % 200 + 50;
		result = admin.login[i] + enc_key[i];
		if ((result >= 'a' && result <= 'z') || (result >= 'A' && result <= 'Z'))
		{
			admin.login[i] = admin.login[i] + enc_key[i];
			enc_key[i + 1] = '\0';
		}
		else
		{
			i--;
		}
	}

	/*
	 * Saving enc key for login
	 */

	ofstream save_enc_key;
	try
	{
		save_enc_key.open(dir_an_path::Path::Admin::path_adm_enc_key(), ios::trunc);
		if (save_enc_key.is_open())
		{
			for (size_t i = 0; i < size; i++)
			{
				save_enc_key << enc_key[i];
			}
			save_enc_key << endl;
			save_enc_key.close();
		}
		else
		{
			save_enc_key.close();
			delete[] enc_key;
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save User encryption Key Error!\nPath";
		error_text += dir_an_path::Path::Admin::path_sv_adm_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
		return;
	}

	delete[] enc_key; // delete the old login key, for the password key
	enc_key = nullptr;

	size = strlen(admin.password);  // Password length

	enc_key = new char[size + 1];
	enc_key[0] = '\0';

	// Encrypting administrator password
	for (size_t i = 0; i < size; i++)
	{
		enc_key[i] = rand() % 200 + 50;
		result = admin.password[i] + enc_key[i];
		if ((result >= 'a' && result <= 'z') || (result >= 'A' && result <= 'Z'))
		{
			admin.password[i] = admin.password[i] + enc_key[i];
			enc_key[i + 1] = '\0';
		}
		else
		{
			i--;
		}
	}

	/*
	 * Saving enc key for password
	 */

	try
	{
		save_enc_key.open(dir_an_path::Path::Admin::path_adm_enc_key(), ios::app);
		if (save_enc_key.is_open())
		{
			for (size_t i = 0; i < size; i++)
			{
				save_enc_key << enc_key[i];
			}
			save_enc_key.close();
		}
		else
		{
			delete[] enc_key;
			save_enc_key.close();
			throw 1;
		}
	}
	catch (...)
	{
		string error_text = "Save Admin encryption Key Error!\nPath";
		error_text += dir_an_path::Path::Admin::path_sv_adm_data();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
	}

	delete[] enc_key;

	SetFileAttributesA(dir_an_path::Path::Admin::path_adm_enc_key().c_str(), FILE_ATTRIBUTE_HIDDEN);
}

bool operator<(const Account& left, const Account& right)
{
	return left.login < right.login;
}