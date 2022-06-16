#pragma once
// User and Admin parameters
constexpr size_t login_len = 21;		    // login length (Admin,User)
constexpr size_t pass_len = 29;				// password length (Admin,User)
constexpr size_t name_len = 21;			    // name length                 --       User
constexpr size_t sur_len = 26;				// surname length
constexpr size_t patron_len = 21;           // patronymic (Father's name)
constexpr size_t country_length = 22;       // Country Name length
constexpr size_t city_length = 21;          // City Name length
constexpr size_t email_length = 30;         // email length
constexpr size_t phone_n_length = 17;       // phone number length
constexpr size_t day_l = 3;                 // number character day[]
constexpr size_t month_l = 3;               // number character month[]
constexpr size_t year_l = 5;                // number character year[]

constexpr size_t rec_key_length = 11;       // key recovery length (Admin account) -- Admin

// Test parameters

constexpr size_t cat_an_sec_len = 31;       // category(name), section(name) length

enum { ENTER = 13, ESC = 27, UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77 }; // to identify the keys