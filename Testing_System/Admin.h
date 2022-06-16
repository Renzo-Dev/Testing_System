#pragma once

class Admin
{
public:
	char* login = nullptr;      // Admin login
	char* password = nullptr;   // Admin password
	char* rec_key = nullptr;    // buffer for encryption key (for Admin Account)

	Admin(const Admin& obj);  // Constructor copying

	~Admin();                 // Destructor

	Admin();                  // Constructor
};