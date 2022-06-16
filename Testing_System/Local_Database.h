#pragma once
#include <set>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include "dir_an_path.h"
#include "Admin.h"
#include "Account.h"
#include "array_size.h"
#include "Test.h"

using namespace std;

class Data
{
public:
	Admin admin_; // object Admin (composition)
	std::set<std::string> logins_; // login list

	Data(); // default constructor

	~Data(); // default destructor
};

class Local_Database : public Data
{
public:

	Local_Database(); // Constructor - Initialization: Admin admin_ , set<string> logins_;

	void load_data(); // upload data (Admin data) + (Users Logins)

	static void save_admin_acc(Admin admin); // save admin account (data)

	static void save_user_acc(const Account& user); // save user account (data)

	static void decryption(Admin& admin); // decryption (admin data)

	static void decryption(const string& login, Account& account); // decryption (user data)

	static void encryption(Admin& account); // encryption (admin data)

	static void encryption(const Account& account); // encryption (User data)

	static bool save_user_login(const string& login);  // save user login(for login list)

	static auto save_logins(const set<string>& logins_) -> bool; // save login list

	static bool load_user_data(const string& login, Account& acc); // load user data

	bool recovery_admin_account();  // recovery(reset) admin account

	static string found_user(char* buffer, const set<string>& logins_, char type_found);  // type: 1 - Login , 2 - email , 3 - phone number

	friend bool operator< (const Account& left, const Account& right); // Predicate , for set<Account> , map<Account>

	~Local_Database(); // Destructor
};