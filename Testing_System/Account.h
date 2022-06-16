#pragma once

class Account
{
public:
	/* Login information */
	char* login;
	char* password;

	/* Personal Information */
	char* Name;
	char* Surname;
	char* Patronymic;

	/* Date of birth */
	char* day;
	char* month;
	char* year;

	/* Place of residence */

	char* Country;
	char* City;

	/* Contact Information */

	char* email;
	char* phone_number;

	Account(const Account& obj);

	~Account();

	Account();
};
