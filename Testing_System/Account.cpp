#include "Account.h"
#include <cstring>
#include "array_size.h"

Account::~Account()
{
	delete[] this->login;
	delete[] this->password;
	delete[] this->Name;
	delete[] this->Surname;
	delete[] this->Patronymic;
	delete[] this->City;
	delete[] this->Country;
	delete[] this->phone_number;
	delete[] this->email;
	delete[] this->day;
	delete[] this->year;
	delete[] this->month;
}

Account::Account() : login(new char[login_len]), password(new char[pass_len]), Name(new char[name_len]),
Surname(new char[sur_len]), Patronymic(new char[patron_len]),
day(new char[day_l]), month(new char[month_l]), year(new char[year_l]), Country(new char[country_length]), City(new char[city_length]), email(new char[email_length]),
phone_number(new char[phone_n_length])
{
	login[0] = '\0';

	password[0] = '\0';

	Name[0] = '\0';

	Surname[0] = '\0';

	Patronymic[0] = '\0';

	Country[0] = '\0';

	City[0] = '\0';

	email[0] = '\0';

	phone_number[0] = '\0';

	day[0] = '\0';

	month[0] = '\0';

	year[0] = '\0';
}

Account::Account(const Account& obj) : login(nullptr), password(nullptr), Name(nullptr), Surname(nullptr),
Patronymic(nullptr), day(nullptr), month(nullptr), year(nullptr),
Country(nullptr), City(nullptr), email(nullptr), phone_number(nullptr)
{
	if (this->login != nullptr)
	{
		delete[] login;
		this->login = nullptr;
	}

	this->login = new char[strlen(obj.login) + 1];

	strcpy(this->login, obj.login);

	//

	if (this->password != nullptr)
	{
		delete[] password;
		this->password = nullptr;
	}

	this->password = new char[strlen(obj.password) + 1];

	strcpy(this->password, obj.password);

	//

	if (this->Name != nullptr)
	{
		delete[] Name;
		this->Name = nullptr;
	}

	this->Name = new char[strlen(obj.Name) + 1];

	strcpy(this->Name, obj.Name);

	if (this->Surname != nullptr)
	{
		delete[] Surname;
		this->Surname = nullptr;
	}

	this->Surname = new char[strlen(obj.Surname) + 1];

	strcpy(this->Surname, obj.Surname);

	if (this->Patronymic != nullptr)
	{
		delete[] Patronymic;
		this->Patronymic = nullptr;
	}

	this->Patronymic = new char[strlen(obj.Patronymic) + 1];

	strcpy(this->Patronymic, obj.Patronymic);

	if (this->City != nullptr)
	{
		delete[] City;
		this->City = nullptr;
	}

	this->City = new char[strlen(obj.City) + 1];

	strcpy(this->City, obj.City);

	if (this->Country != nullptr)
	{
		delete[] Country;
		this->Country = nullptr;
	}

	this->Country = new char[strlen(obj.Country) + 1];

	strcpy(this->Country, obj.Country);

	if (this->day != nullptr)
	{
		delete[] day;
		this->day = nullptr;
	}

	this->day = new char[strlen(obj.day) + 1];

	strcpy(this->day, obj.day);

	if (this->month != nullptr)
	{
		delete[] month;
		this->month = nullptr;
	}

	this->month = new char[strlen(obj.month) + 1];

	strcpy(this->month, obj.month);

	if (this->year != nullptr)
	{
		delete[] year;
		this->year = nullptr;
	}

	this->year = new char[strlen(obj.year) + 1];

	strcpy(this->year, obj.year);

	if (this->email != nullptr)
	{
		delete[] email;
		this->email = nullptr;
	}

	this->email = new char[strlen(obj.email) + 1];

	strcpy(this->email, obj.email);

	if (this->phone_number != nullptr)
	{
		delete[] phone_number;
		this->phone_number = nullptr;
	}

	this->phone_number = new char[strlen(obj.phone_number) + 1];

	strcpy(this->phone_number, obj.phone_number);
}