#include "Admin.h"
#include <cstring>
#include "array_size.h"

Admin::Admin() : login(new char[login_len]), password(new char[pass_len]), rec_key(new char[rec_key_length])
{
	this->login[0] = '\0';

	this->password[0] = '\0';

	this->rec_key[0] = '\0';
}

Admin::Admin(const Admin& obj)
{
	if (this->login != nullptr)
	{
		delete[] login;
		this->login = nullptr;
	}

	this->login = new char[strlen(obj.login) + 1];

	strcpy(this->login, obj.login);

	if (this->password != nullptr)
	{
		delete[] password;
		this->password = nullptr;
	}

	this->password = new char[strlen(obj.password) + 1];

	strcpy(this->password, obj.password);

	if (this->rec_key != nullptr)
	{
		delete[] rec_key;
		this->rec_key = nullptr;
	}

	this->rec_key = new char[strlen(obj.rec_key) + 1];

	strcpy(this->rec_key, obj.rec_key);
}

Admin::~Admin()
{
	delete[] login;
	delete[] password;
	delete[] rec_key;
}