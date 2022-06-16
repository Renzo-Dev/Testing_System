#include "Test.h"

#include "Context_Menu.h"

Category::Category()
{
	load_categories(categories);
}

void Category::load_categories(set<string>& categories)
{
	try
	{
		SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_NORMAL);
		ifstream load_categories;
		load_categories.open(dir_an_path::Path::Test::Category::path_category_list());
		if (load_categories.is_open())
		{
			string tmp_category;
			while (!load_categories.eof())
			{
				load_categories >> tmp_category;
				for (int i = 0; i < tmp_category.size(); i++)
				{
					if (tmp_category[i] == '#')
					{
						tmp_category[i] = ' ';
					}
				}
				categories.emplace(tmp_category);
			}
		}
		SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
	catch (...)
	{
		system("cls");
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[91mFile Load error \033[97m|\n";
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[92mPath\033[97m: \033[102m\033[97m" << dir_an_path::Path::Test::Category::path_category_list() << "\033[0m";
		std::cout << "\n\033[97m---------------------------------";
		std::cout << "\n\033[97m| \033[93mPress any button for continue \033[97m|";
		std::cout << "\n\033[97m---------------------------------\n";
		SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_HIDDEN);
		_getch();
		return;
	}
}

void Category::save_category(char* name_category)
{
	SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_NORMAL);
	try
	{
		fs::create_directory(dir_an_path::Directories::Test::Category::folder_category(name_category));
		ofstream save_category;
		save_category.open(dir_an_path::Path::Test::Category::path_category_list(), ios::app);
		if (save_category.is_open())
		{
			for (auto i = 0; i < strlen(name_category); i++)
			{
				if (name_category[i] == ' ')
				{
					name_category[i] = '#';
				}
			}
			save_category << name_category << endl;
		}
		delete[] name_category;
		save_category.close();
		SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_HIDDEN);
		return;
	}
	catch (...)
	{
		delete[] name_category;
		system("cls");
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[91mFile save error \033[97m|\n";
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[92mPath\033[97m: \033[102m\033[97m" << dir_an_path::Path::Test::Category::path_category_list() << "\033[0m";
		std::cout << "\n\033[97m---------------------------------";
		std::cout << "\n\033[97m| \033[93mPress any button for continue \033[97m|";
		std::cout << "\n\033[97m---------------------------------\n";
		SetFileAttributesA(dir_an_path::Path::Test::Category::path_category_list().c_str(), FILE_ATTRIBUTE_HIDDEN);
		_getch();
		return;
	}
}

bool Category::show_categories(bool type)
{
	char choose;

	vector tmp_categories(categories.begin(), categories.end());

	int list_start = 0;
	int list_c_max;
	int select = 0;
	constexpr int num_categories_list = 15;    // the number of categories in the list on the screen

	if (categories.size() < 10)
	{
		list_c_max = categories.size();
	}
	else
	{
		list_c_max = num_categories_list;
	}

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		system("cls");
		cout << "\t\t\t    ----------------------------------------------------------------\n";
		cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
		cout << "\t\t\t    ----------------------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t--------------------------\n";
		cout << "\t\t\t\t\t\t|   \033[33mSelect   \033[92m Category   \033[97m|\n";
		cout << "\t\t\t\t\t    ----------------------------------\n";

		for (int i = list_start; i < list_c_max; i++)
		{
			if (i == select)
			{
				cout << "\t\t\t\t\t    | \033[104m" << tmp_categories[i] << "\033[0m\033[97m" << setw(static_cast<streamsize>(cat_an_sec_len - tmp_categories[i].size()) + 2) << " |\n";
			}
			else
			{
				cout << "\t\t\t\t\t    | " << tmp_categories[i] << setw(static_cast<streamsize>(cat_an_sec_len - tmp_categories[i].size()) + 2) << " |\n";
			}
		}

		if ((list_c_max - list_start) < num_categories_list)
		{
			for (int i = 0; i < num_categories_list - (list_c_max - list_start); i++)
			{
				cout << "\t\t\t\t\t    |                                |\n";
			}
		}

		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    CT: " << select + 1 << " of " << categories.size() << endl;
		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    PG: " << list_start / 10 + 1 << " of "; if (categories.size() / 10 == 0) { cout << "1"; }
		else { categories.size() / 10; }

		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (type == true) {
				if (this->section_initialization(tmp_categories[select]) == false)
				{
				}
				else
				{
					return true;
				}
			}
			else
			{
				load_sections(tmp_categories[select], sections);
				if (sections.size() > 0)
				{
					show_sections(tmp_categories[select], false);
				}
				else
				{
					system("cls");
					cout << "\t\t\t    ----------------------------------------------------------------\n";
					cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
					cout << "\t\t\t    ----------------------------------------------------------------\n\n";
					cout << "\t\t\t\t\t\t--------------------------\n";
					cout << "\t\t\t\t\t\t|   \033[33mSelect   \033[92m Category   \033[97m|\n";
					cout << "\t\t\t\t\t    ----------------------------------\n";

					for (int i = list_start; i < list_c_max; i++)
					{
						if (i == select)
						{
							cout << "\t\t\t\t\t    | \033[104m" << tmp_categories[i] << "\033[0m\033[97m" << setw(static_cast<streamsize>(cat_an_sec_len - tmp_categories[i].size()) + 2) << " | " << " \033[91mThere are no sections (tests)\033[97m\n";;
						}
						else
						{
							cout << "\t\t\t\t\t    | " << tmp_categories[i] << setw(static_cast<streamsize>(cat_an_sec_len - tmp_categories[i].size()) + 2) << " |\n";
						}
					}

					if ((list_c_max - list_start) < num_categories_list)
					{
						for (int i = 0; i < num_categories_list - (list_c_max - list_start); i++)
						{
							cout << "\t\t\t\t\t    |                                |\n";
						}
					}

					cout << "\t\t\t\t\t    ----------------------------------\n";
					cout << "\t\t\t\t\t    CT: " << select + 1 << " of " << categories.size() << endl;
					cout << "\t\t\t\t\t    ----------------------------------\n";
					cout << "\t\t\t\t\t    PG: " << list_start / 10 + 1 << " of "; if (categories.size() / 10 == 0) { cout << "1"; }
					else { categories.size() / 10; }
					this_thread::sleep_for(chrono::milliseconds(1500));
				}
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return false;
		}
		if (static_cast<int>(choose) == RIGHT)
		{
			if (list_c_max != categories.size())
			{
				if (list_c_max + num_categories_list > categories.size()) // If list length max + 10 is greater than the number of logins
				{
					list_c_max = categories.size();
					list_start += num_categories_list;
					select = list_start;
				}
				else
				{
					list_c_max += num_categories_list;
					list_start += num_categories_list;
					select = list_start;
				}
			}
		}
		if (static_cast<int>(choose) == LEFT)
		{
			if (list_start != 0)
			{
				if (list_c_max - num_categories_list < num_categories_list)
				{
					list_c_max -= list_c_max - list_start;
					list_start -= num_categories_list;
					select = list_start;
				}
			}
		}

		if (static_cast<int> (choose) == DOWN)
		{
			if (select < list_c_max - 1)
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

void Category::add_category()
{
	char* name_category = new char[cat_an_sec_len];
	name_category[0] = '\0';

	char choose;
	bool no_unique = false;
	bool key_down = false;

	for (size_t i = strlen(name_category);;)
	{
		// Show
		system("cls");
		cout << "\t\t\t\t    --------------------------------------------------\n";
		cout << "\t\t\t\t    |\033[94mCONTROL\033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t\t    --------------------------------------------------\n\n\n\n\n";
		cout << "\t\t\t\t\t\t      ----------------\n";
		cout << "\t\t\t\t\t\t      | \033[96mAdd \033[93mCategory \033[97m|\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    |  \033[94mEnter the name of the \033[93mcategory  \033[97m|\n";
		cout << "\t\t\t\t\t    |         \033[94myou  want to add\033[97m         |\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    |>: " << name_category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(name_category)) + 1) << " |";
		for (auto it : categories)
		{
			if (strcmp(name_category, it.c_str()) == 0)
			{
				cout << "\033[91m a category by that name exists\033[97m";
				no_unique = true;
				break;
			}
			else
			{
				no_unique = false;
			}
		}

		cout << "\n\t\t\t\t\t    ------------------------------------\n";

		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_down == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ' || choose == '!' || choose == '_')
			{
				if (i < cat_an_sec_len - 1)
				{
					name_category[i] = choose;
					++i;
					name_category[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					name_category[i] = '\0';
					this_thread::sleep_for(chrono::milliseconds(30));
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] name_category;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(name_category) > 3 && no_unique == false)
				{
					cout << "\t\t\t\t\t      | \033[92mCategory  successfully added\033[97m |";
					cout << "\n\t\t\t\t\t      --------------------------------\n";
					this_thread::sleep_for(chrono::seconds(2));
					categories.emplace(name_category);
					thread save(save_category, name_category);
					save.detach();
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
		{
			key_down = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == LEFT && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == UP && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
		{
			key_down = false;
		}
	}
}

void Category::category_initialization()
{
	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n\n\n\n\n";

		cout << "\t\t\t\t\t\t    -------------------\n";
		cout << "\t\t\t\t\t\t    | \033[33mCreating a \033[94mTest \033[97m|\n";
		cout << "\t\t\t\t\t       -----------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t       |\033[104m1\033[0m\033[97m| \033[92mSelect \033[95mScience \033[93mCategory \033[97m|\n";
			cout << "\t\t\t\t\t       |2| \033[96mAdd \033[95mScience \033[93mCategory    \033[97m|\n";
			cout << "\t\t\t\t\t       -----------------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t       |1| \033[92mSelect \033[95mScience \033[93mCategory \033[97m|\n";
			cout << "\t\t\t\t\t       |\033[104m2\033[0m\033[97m| \033[96mAdd \033[95mScience \033[93mCategory    \033[97m|\n";
			cout << "\t\t\t\t\t       -----------------------------\n";
		}break;
		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				if (!categories.empty())
				{
					if (show_categories(true) == false)
					{
					}
					else
					{
						return;
					}
				}
				else
				{
					system("cls");
					cout << "\t\t\t     --------------------------------------------------------------\n";
					cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t     --------------------------------------------------------------\n\n\n\n\n";

					cout << "\t\t\t\t\t\t    -------------------\n";
					cout << "\t\t\t\t\t\t    | \033[33mCreating a \033[94mTest \033[97m|\n";
					cout << "\t\t\t\t\t       -----------------------------\n";
					cout << "\t\t\t\t\t       |\033[104m1\033[0m\033[97m| \033[92mSelect \033[95mScience \033[93mCategory \033[97m| \033[91mThere is no category!\n";
					cout << "\t\t\t\t\t       \033[97m|2| \033[96mAdd \033[95mScience \033[93mCategory    \033[97m|\n";
					cout << "\t\t\t\t\t       -----------------------------\n";
					this_thread::sleep_for(chrono::seconds(1));
				}
			}
			if (move == '2')
			{
				add_category();
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
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
	}
}

Category::~Category()
= default;

void Test::operator()(size_t new_n_q)
{
	if (this->quest != nullptr)
	{
		delete[] this->quest;
		this->quest = nullptr;
	}
	num_questions_ = new_n_q;
	this->quest = new Question[new_n_q];
}

void Test::add_new_test_name(const char* category, const char* section)
{
	SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_NORMAL);
	try
	{
		ofstream save;
		save.open(dir_an_path::Path::Test::path_test_list(category, section), ios::app);
		if (save.is_open())
		{
			for (auto i = 0; i < strlen(test_name); i++)
			{
				if (test_name[i] == ' ')
				{
					test_name[i] = '#';
				}
			}
			save << test_name << endl;
		}

		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		save.close();
	}
	catch (...)
	{
		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		system("cls");
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[91mFile save error \033[97m|\n";
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[92mPath\033[97m: \033[102m\033[97m" << dir_an_path::Path::Test::path_test_list(category, section) << "\033[0m";
		std::cout << "\n\033[97m---------------------------------";
		std::cout << "\n\033[97m| \033[93mPress any button for continue \033[97m|";
		std::cout << "\n\033[97m---------------------------------\n";
		_getch();
		return;
	}
}

void Test::save_list_tests(const char* category, const char* section, set<string>& test_list)
{
	SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_NORMAL);
	try
	{
		remove(dir_an_path::Path::Test::path_test_list(category, section).c_str());
		ofstream save;
		save.open(dir_an_path::Path::Test::path_test_list(category, section), ios::app);
		if (save.is_open())
		{
			for (auto it : test_list)
			{
				for (int i = 0; i < it.length(); i++)
				{
					if (it[i] == ' ')
					{
						it[i] = '#';
					}
				}
				save << it.c_str() << endl;
			}
		}

		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		save.close();
	}
	catch (...)
	{
		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		system("cls");
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[91mFile save error \033[97m|\n";
		std::cout << "\033[97m-------------------\n";
		std::cout << "\033[97m| \033[92mPath\033[97m: \033[102m\033[97m" << dir_an_path::Path::Test::path_test_list(category, section) << "\033[0m";
		std::cout << "\n\033[97m---------------------------------";
		std::cout << "\n\033[97m| \033[93mPress any button for continue \033[97m|";
		std::cout << "\n\033[97m---------------------------------\n";
		_getch();
		return;
	}
}

void Test::load_test(const char* category, const char* section)
{
	mutex mtx;
	mtx.lock();
	load_number_questions(category, section, test_name);
	this->operator()(this->num_questions_);
	int i = 0;
	try
	{
		ifstream load;
		for (; i < num_questions_; i++)
		{
			load.open(dir_an_path::Path::Test::path_sv_questions(category, section, test_name, i));
			if (load.is_open())
			{
				load >> quest[i].text >> quest[i].answer >> quest[i].n_points;

				for (int e = 0; e < quest->length(); e++)
				{
					if (quest[i].text[e] == '#')
					{
						quest[i].text[e] = ' ';
					}
				}
			}
			load.close();
		}
		mtx.unlock();
	}
	catch (...)
	{
		string error_text = "File load Error!\nPath";
		error_text += dir_an_path::Path::Test::path_sv_questions(category, section, test_name, i);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		mtx.unlock();
	}
}

Test::Test() : test_name(new char[test_name_length])
{
	test_name[0] = '\0';
}

Test::Test(const char* test_name) :Test()
{
	int len = strlen(test_name);
	for (int i = 0; i < len; i++)
	{
		this->test_name[i] = test_name[i];
	}
	this->test_name[len] = '\0';
}

void Test::quest_initialization(const char* category, const char* section)
{
	this->operator()(num_questions_);

	int current_question = 0;

	char move = '1';
	char choose;
	bool key_down = false;

	while (true)
	{
		switch (move)
		{
		case '1':
		{
			for (size_t e = quest[current_question].length();;)
			{
				// Show

				system("cls");
				cout << "\t\t\t    ----------------------------------------------------------------\n";
				cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Save  -  \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t    ----------------------------------------------------------------\n\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[96mTest Name\033[97m: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << "|\n";
				cout << "\t\t\t\t     | \033[94mSection\033[97m:  " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 3) << "|\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t\t \033[104m" << char(26) << "\033[0m\033[97m| \033[93mQuestion\033[97m: " << current_question + 1 << " / " << num_questions_;
				if (current_question <= 9 && num_questions_ <= 9) // 1 9
				{
					cout << "                |\n";
				}
				if (current_question < 9 && num_questions_ > 9 && num_questions_ <= 99) // 6 23
				{
					cout << "               |\n";
				}
				if (current_question >= 9 && num_questions_ <= 99)
				{
					cout << "              |\n";
				}

				cout << "\t\t\t\t\t  ----------------------------------\n";
				int length = 30;

				cout << "\t\t\t\t\t  | ";
				for (int i = 0; i < quest->length_text; i++)
				{
					if (i == length)
					{
						cout << " | \n\t\t\t\t\t ";

						if (length < quest->length_text - 1)
						{
							cout << " | ";
						}

						length += 30;
					}

					cout << quest[current_question].text[i];
				}
				cout << "----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[36mAnswer\033[97m: ";
				if (quest[current_question].answer == true)
				{
					cout << "\033[92mCorrect\033[97m                |\n";
				}
				else
				{
					cout << "\033[91mWrong\033[97m                  |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[96mPoints\033[97m: ";
				cout << quest[current_question].n_points;
				if (quest[current_question].n_points <= 9)
				{
					cout << "                      |\n";
				}
				if (quest[current_question].n_points >= 10)
				{
					cout << "                     |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";

				choose = _getch();

				if (static_cast<int>(choose) == ESC)
				{
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(test_name) > 3 && num_questions_ > 0)
				{
					for (int j = 0; j < num_questions_; j++)
					{
						if (quest[j].length() == 0)
						{
							cout << "\t\t\t\t\t     \033[91mNot all tests are filled out\033[97m\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '2';
							goto ENTER_QUESTION_TEXT;
						}
						if (quest[j].n_points == 0)
						{
							cout << "\t\t\t\t\t     \033[91mIncorrect number of points\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '4';
							goto ENTER_NUMBER_POINTS;
						}
					}
					test_save_finish(category, section);
					return;
				}

				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
					if (current_question < num_questions_ - 1)
					{
						current_question++;
					}
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
					if (current_question > 0)
					{
						current_question--;
					}
					break;
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
					move = '2';
					break;
				}
			}
		}break;
		case '2':
		{
		ENTER_QUESTION_TEXT:
			for (size_t e = quest[current_question].length();;)
			{
				// Show

				system("cls");
				cout << "\t\t\t    ----------------------------------------------------------------\n";
				cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Save  -  \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t    ----------------------------------------------------------------\n\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[96mTest Name\033[97m: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << "|\n";
				cout << "\t\t\t\t     | \033[94mSection\033[97m:  " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 3) << "|\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[93mQuestion\033[97m: " << current_question + 1 << " / " << num_questions_;
				if (current_question <= 9 && num_questions_ <= 9) // 1 9
				{
					cout << "                |\n";
				}
				if (current_question < 9 && num_questions_ > 9 && num_questions_ <= 99) // 6 23
				{
					cout << "               |\n";
				}
				if (current_question >= 9 && num_questions_ <= 99)
				{
					cout << "              |\n";
				}

				cout << "\t\t\t\t\t  ----------------------------------\n";
				int length = 30;

				cout << "\t\t\t\t   Enter \033[104m" << char(26) << "\033[0m\033[97m| ";
				for (int i = 0; i < quest->length_text; i++)
				{
					if (i == length)
					{
						cout << " | \n\t\t\t\t\t ";

						if (length < quest->length_text - 1)
						{
							cout << " | ";
						}

						length += 30;
					}

					cout << quest[current_question].text[i];
				}
				cout << "----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[36mAnswer\033[97m: ";
				if (quest[current_question].answer == true)
				{
					cout << "\033[92mCorrect\033[97m                |\n";
				}
				else
				{
					cout << "\033[91mWrong\033[97m                  |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[96mPoints\033[97m: ";
				cout << quest[current_question].n_points;
				if (quest[current_question].n_points <= 9)
				{
					cout << "                      |\n";
				}
				if (quest[current_question].n_points >= 10)
				{
					cout << "                     |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_down == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ' || choose == '!' || choose == '.' || choose == '_' || choose == '?' || choose == '+' || choose == '-' || choose == '=' || choose == '*' || choose == '/' || choose == '#' || choose == '@' || choose == '%' || choose == '(' || choose == ')' || choose == '{' || choose == '}')
					{
						if (e < quest->length_text - 1)
						{
							quest[current_question].text[e] = choose;
							++e;
							quest[current_question].text[e] = ' ';
						}
					}
					else
					{
						if (choose == '\b' && e > 0) // if user typed backspace
						{
							--e;
							quest[current_question].text[e] = ' ';
							this_thread::sleep_for(chrono::milliseconds(30));
						}
						if (static_cast<int>(choose) == ESC)
						{
							return;
						}
						if (static_cast<int>(choose) == ENTER && strlen(test_name) > 3 && num_questions_ > 0 /*&& no_unique == false*/)
						{
							for (int j = 0; j < num_questions_; j++)
							{
								if (quest[j].length() == 0)
								{
									cout << "\t\t\t\t\t     \033[91mNot all tests are filled out\033[97m\n";
									cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
									this_thread::sleep_for(chrono::seconds(2));
									current_question = j;
									move = '2';
									goto ENTER_QUESTION_TEXT;
								}
								if (quest[j].n_points == 0)
								{
									cout << "\t\t\t\t\t     \033[91mIncorrect number of points\n";
									cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
									this_thread::sleep_for(chrono::seconds(2));
									current_question = j;
									move = '4';
									goto ENTER_NUMBER_POINTS;
								}
							}
							test_save_finish(category, section);
							return;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
					move = '1';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
					move = '3';
					break;
				}
			}
		}break;
		case '3':
		{
			for (size_t e = quest[current_question].length();;)
			{
				// Show

				system("cls");
				cout << "\t\t\t    ----------------------------------------------------------------\n";
				cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Save  -  \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t    ----------------------------------------------------------------\n\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[96mTest Name\033[97m: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << "|\n";
				cout << "\t\t\t\t     | \033[94mSection\033[97m:  " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 3) << "|\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[93mQuestion\033[97m: " << current_question + 1 << " / " << num_questions_;
				if (current_question <= 9 && num_questions_ <= 9) // 1 9
				{
					cout << "                |\n";
				}
				if (current_question < 9 && num_questions_ > 9 && num_questions_ <= 99) // 6 23
				{
					cout << "               |\n";
				}
				if (current_question >= 9 && num_questions_ <= 99)
				{
					cout << "              |\n";
				}

				cout << "\t\t\t\t\t  ----------------------------------\n";
				int length = 30;

				cout << "\t\t\t\t\t  | ";
				for (int i = 0; i < quest->length_text; i++)
				{
					if (i == length)
					{
						cout << " | \n\t\t\t\t\t ";

						if (length < quest->length_text - 1)
						{
							cout << " | ";
						}

						length += 30;
					}
					cout << quest[current_question].text[i];
				}
				cout << "----------------------------------\n";
				cout << "\t\t\t\t   Enter \033[104m" << char(26) << "\033[0m\033[97m| \033[36mAnswer\033[97m: ";
				if (quest[current_question].answer == true)
				{
					cout << "\033[102mCorrect\033[0m\033[97m      \033[91mWrong     \033[97m|\n";
				}
				else
				{
					cout << "\033[92mCorrect      \033[97m\033[101mWrong\033[0m     \033[97m|\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[96mPoints\033[97m: ";
				cout << quest[current_question].n_points;
				if (quest[current_question].n_points <= 9)
				{
					cout << "                      |\n";
				}
				if (quest[current_question].n_points >= 10)
				{
					cout << "                     |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				choose = _getch();

				if (static_cast<int>(choose) == ESC)
				{
					return;
				}
				if (static_cast<int>(choose) == ENTER)
				{
					for (int j = 0; j < num_questions_; j++)
					{
						if (quest[j].length() == 0)
						{
							cout << "\t\t\t\t\t     \033[91mNot all tests are filled out\033[97m\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '2';
							goto ENTER_QUESTION_TEXT;
						}
						if (quest[j].n_points == 0)
						{
							cout << "\t\t\t\t\t     \033[91mIncorrect number of points\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '4';
							goto ENTER_NUMBER_POINTS;
						}
					}
					test_save_finish(category, section);
					return;
				}

				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
					quest[current_question].answer = false;
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
					quest[current_question].answer = true;
					break;
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
					move = '2';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
					move = '4';
					break;
				}
			}
		}break;
		case '4':
		{
		ENTER_NUMBER_POINTS:
			for (size_t e = quest[current_question].length();;)
			{
				// Show

				system("cls");
				cout << "\t\t\t    ----------------------------------------------------------------\n";
				cout << "\t\t\t    | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Save  -  \033[92mENTER\033[97m | Exit - \033[91mESC \033[97m|\n";
				cout << "\t\t\t    ----------------------------------------------------------------\n\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[96mTest Name\033[97m: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t     | \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << "|\n";
				cout << "\t\t\t\t     | \033[94mSection\033[97m:  " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 3) << "|\n";
				cout << "\t\t\t\t     ---------------------------------------------\n";
				cout << "\t\t\t\t\t  | \033[93mQuestion\033[97m: " << current_question + 1 << " / " << num_questions_;
				if (current_question <= 9 && num_questions_ <= 9) // 1 9
				{
					cout << "                |\n";
				}
				if (current_question < 9 && num_questions_ > 9 && num_questions_ <= 99) // 6 23
				{
					cout << "               |\n";
				}
				if (current_question >= 9 && num_questions_ <= 99)
				{
					cout << "              |\n";
				}

				cout << "\t\t\t\t\t  ----------------------------------\n";
				int length = 30;

				cout << "\t\t\t\t\t  \033[97m| ";
				for (int i = 0; i < quest->length_text; i++)
				{
					if (i == length)
					{
						cout << " | \n\t\t\t\t\t ";

						if (length < quest->length_text - 1)
						{
							cout << " | ";
						}

						length += 30;
					}

					cout << quest[current_question].text[i];
				}
				cout << "----------------------------------\n";
				cout << "\t\t\t\t\t  | \033[36mAnswer\033[97m: ";
				if (quest[current_question].answer == true)
				{
					cout << "\033[92mCorrect\033[97m                |\n";
				}
				else
				{
					cout << "\033[91mWrong\033[97m                  |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				cout << "\t\t\t\t\t \033[104m" << char(26) << "\033[0m\033[97m| \033[96mPoints\033[97m: ";
				cout << quest[current_question].n_points;
				if (quest[current_question].n_points <= 9)
				{
					cout << "                      |\n";
				}
				if (quest[current_question].n_points >= 10)
				{
					cout << "                     |\n";
				}
				cout << "\t\t\t\t\t  ----------------------------------\n";
				choose = _getch();

				if (static_cast<int>(choose) == ESC)
				{
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(test_name) > 3 && num_questions_ > 0 /*&& no_unique == false*/)
				{
					for (int j = 0; j < num_questions_; j++)
					{
						if (quest[j].length() == 0)
						{
							cout << "\t\t\t\t\t     \033[91mNot all tests are filled out\033[97m\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '2';
							goto ENTER_QUESTION_TEXT;
						}
						if (quest[j].n_points == 0)
						{
							cout << "\t\t\t\t\t     \033[91mIncorrect number of points\n";
							cout << "\t\t\t\t\t               \033[91mTest N " << j + 1 << "\033[97m\n";
							this_thread::sleep_for(chrono::seconds(2));
							current_question = j;
							move = '4';
							goto ENTER_NUMBER_POINTS;
						}
					}
					test_save_finish(category, section);
					return;
				}

				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
					if (quest[current_question].n_points < 50)
					{
						quest[current_question].n_points++;
					}
					break;
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
					if (quest[current_question].n_points > 0)
					{
						quest[current_question].n_points--;
					}
					break;
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
					move = '3';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
				}
			}
		}break;
		}
	}
}

void Test::test_initialization(const char* category, const char* section)
{
	char move = '1';
	char choose;
	bool key_down = false;

	while (true) {
		switch (move)
		{
		case '1':
		{
			for (size_t i = strlen(test_name);;)
			{
				// Show
				system("cls");
				cout << "\t\t\t      --------------------------------------------------------------\n";
				cout << "\t\t\t      |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
				cout << "\t\t\t      --------------------------------------------------------------\n\n\n\n\n";
				cout << "\t\t\t\t\t             -----------------\n";
				cout << "\t\t\t\t\t             | \033[36mTest \033[33mCreating \033[97m|\n";
				cout << "\t\t\t\t\t--------------------------------------------\n";
				cout << "\t\t\t\t\t| \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 2) << " |\n";
				cout << "\t\t\t\t\t| \033[93mSection\033[97m : " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 2) << " |\n";
				cout << "\t\t\t\t\t--------------------------------------------\n\n";
				cout << "\t\t\t\t\t            -------------------\n";
				cout << "\t\t\t\t\t            | \033[35mEnter \033[36mTest \033[93mName\033[97m |\n";
				cout << "\t\t\t\t\t    ------------------------------------\n";
				cout << "\t\t\t\t\t   \033[104m" << char(26) << "\033[0m\033[97m|>: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t\t    ------------------------------------\n";
				cout << "\t\t\t\t\t    | \033[96mNumber of Questions\033[97m: " << num_questions_;
				if (num_questions_ <= 9)
				{
					cout << "           |\n";
				}
				else if (num_questions_ > 9)
				{
					cout << "          |\n";
				}
				cout << "\t\t\t\t\t    ------------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_down == false)
				{
					if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ' || choose == '!' || choose == '.' || choose == '_')
					{
						if (i < test_name_length - 1)
						{
							test_name[i] = choose;
							++i;
							test_name[i] = '\0';
						}
					}
					else
					{
						if (choose == '\b' && i > 0) // if user typed backspace
						{
							--i;
							test_name[i] = '\0';
							this_thread::sleep_for(chrono::milliseconds(30));
						}
						if (static_cast<int>(choose) == ESC)
						{
							return;
						}
						if (static_cast<int>(choose) == ENTER && strlen(test_name) > 3 && num_questions_ > 0 /*&& no_unique == false*/)
						{
							quest_initialization(category, section);
							return;
						}
					}
				}
				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
					move = '2';
					break;
				}
			}
		}break;
		case '2':
		{
			for (size_t i = strlen(test_name);;)
			{
				// Show
				system("cls");
				cout << "\t\t\t     ----------------------------------------------------------------\n";
				cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
				cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";
				cout << "\t\t\t\t\t             -----------------\n";
				cout << "\t\t\t\t\t             | \033[36mTest \033[33mCreating \033[97m|\n";
				cout << "\t\t\t\t\t--------------------------------------------\n";
				cout << "\t\t\t\t\t| \033[92mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 2) << " |\n";
				cout << "\t\t\t\t\t| \033[93mSection\033[97m : " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 2) << " |\n";
				cout << "\t\t\t\t\t--------------------------------------------\n\n";
				cout << "\t\t\t\t\t            -------------------\n";
				cout << "\t\t\t\t\t            | \033[35mEnter \033[36mTest \033[93mName\033[97m |\n";
				cout << "\t\t\t\t\t    ------------------------------------\n";
				cout << "\t\t\t\t\t    |>: " << test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
				cout << "\t\t\t\t\t    ------------------------------------\n";
				cout << "\t\t\t\t\t   \033[104m" << char(26) << "\033[0m\033[97m| \033[96mNumber of Questions\033[97m: " << num_questions_;
				if (num_questions_ <= 9)
				{
					cout << "           | \033[92mLeft\033[97m - \\ \033[94mRight\033[97m +\n";
				}
				else if (num_questions_ > 9)
				{
					cout << "          | \033[92mLeft\033[97m - \\ \033[94mRight\033[97m +\n";
				}
				cout << "\t\t\t\t\t    ------------------------------------\n";
				choose = _getch();

				if (static_cast<int> (choose) != -32 && key_down == false)
				{
					if (choose == '\b' && i > 0) // if user typed backspace
					{
						--i;
						test_name[i] = '\0';
						this_thread::sleep_for(chrono::milliseconds(30));
					}
					if (static_cast<int>(choose) == ESC)
					{
						return;
					}
					if (static_cast<int>(choose) == ENTER && strlen(test_name) > 3 && num_questions_ > 0 /*&& no_unique == false*/)
					{
						quest_initialization(category, section);
						return;
					}
				}
				if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
				{
					key_down = true;
				}
				if (static_cast<int> (choose) == RIGHT && key_down == true)
				{
					key_down = false;
					if (num_questions_ < 50)
					{
						num_questions_++;
					}
				}
				if (static_cast<int> (choose) == LEFT && key_down == true)
				{
					key_down = false;
					if (num_questions_ > 0)
					{
						num_questions_--;
					}
				}
				if (static_cast<int> (choose) == UP && key_down == true)
				{
					key_down = false;
					move = '1';
					break;
				}
				if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
				{
					key_down = false;
				}
			}
		}break;
		}
	}
}

void Test::test_save_finish(const char* category, const char* section)
{
	char choose;
	int max_score = 0;
	for (int i = 0; i < num_questions_; i++)
	{
		max_score += quest[i].n_points;
	}
	while (true)
	{
		system("cls");
		cout << "\t\t\t       ----------------------------------------------------------------\n";
		cout << "\t\t\t       |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Continue - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t       ----------------------------------------------------------------\n\n\n\n\n";
		cout << "\t\t\t\t\t\t     -------------------\n";
		cout << "\t\t\t\t\t\t     | Creating a Test |\n";
		cout << "\t\t\t\t\t---------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[94mTest Name\033[97m: " << this->test_name << setw(static_cast<streamsize>(test_name_length - strlen(test_name)) + 2) << " |\n";
		cout << "\t\t\t\t\t---------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[93mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - strlen(category)) + 3) << " |\n";
		cout << "\t\t\t\t\t---------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[95mSection\033[97m: " << section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(section)) + 4) << " |\n";
		cout << "\t\t\t\t\t---------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[92mMaximum score for the test\033[97m: " << max_score;
		if (max_score <= 9)
		{
			cout << "             |\n";
		}
		if (max_score >= 10)
		{
			cout << "            |\n";
		}
		cout << "\t\t\t\t\t---------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[92mNumber of questions\033[97m: " << num_questions_;
		if (num_questions_ <= 9)
		{
			cout << "                    |\n";
		}
		if (num_questions_ >= 10)
		{
			cout << "                   |\n";
		}
		cout << "\t\t\t\t\t---------------------------------------------\n";
		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			save_test(category, section);
			return;
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
	}
}

Test::Test(size_t num_q) : num_questions_(num_q), quest(new Question[num_q]) {}

Test::~Test()
{
	delete[] quest;
	delete[] test_name;
}

void Test::show_tests(const char* category, const char* section, set<string>::const_iterator s_beg, set<string>::const_iterator s_end)
{
	char choose;

	vector tests_list(s_beg, s_end);

	int list_start = 0;
	int list_t_max;
	int select = 0;
	constexpr int num_tests_list = 15;    // the number of tests in the list on the screen

	if (tests_list.size() < 10)
	{
		list_t_max = tests_list.size();
	}
	else
	{
		list_t_max = num_tests_list;
	}

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		system("cls");
		cout << "\t\t\t   -------------------------------------------------------------------\n";
		cout << "\t\t\t   | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Go Back - \033[91mESC \033[97m|\n";
		cout << "\t\t\t   -------------------------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t--------------------------\n";
		cout << "\t\t\t\t\t\t|    \033[33mSelect    \033[92m Tests    \033[97m|\n";
		cout << "\t\t\t\t            ----------------------------------\n";

		for (int i = list_start; i < list_t_max; i++)
		{
			if (i == select)
			{
				cout << "\t\t\t\t\t    | \033[104m" << tests_list[i] << "\033[0m\033[97m" << setw(static_cast<streamsize>(test_name_length - tests_list[i].length()) + 2) << " |\n";
			}
			else
			{
				cout << "\t\t\t\t\t    | " << tests_list[i].c_str() << setw(static_cast<streamsize>(test_name_length - tests_list[i].length()) + 2) << " |\n";
			}
		}

		if ((list_t_max - list_start) < num_tests_list)
		{
			for (int i = 0; i < num_tests_list - (list_t_max - list_start); i++)
			{
				cout << "\t\t\t\t\t    |                                |\n";
			}
		}

		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    TS: " << select + 1 << " of " << tests_list.size() << endl;
		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    PG: " << list_start / 10 + 1 << " of ";
		if (tests_list.size() / 10 == 0)
		{
			cout << "1";
		}
		else
		{
			tests_list.size() / 10;
		}

		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			Context_Menu::Admin_Context::Admin_Menu::Test_Management::edit_menu(category, section, tests_list[select]);
			return;
		}
		if (static_cast<int>(choose) == ESC)
		{
			return;
		}
		if (static_cast<int>(choose) == RIGHT)
		{
			if (list_t_max != tests_list.size())
			{
				if (list_t_max + num_tests_list > tests_list.size()) // If list length max + 10 is greater than the number of logins
				{
					list_t_max = tests_list.size();
					list_start += num_tests_list;
					select = list_start;
				}
				else
				{
					list_t_max += num_tests_list;
					list_start += num_tests_list;
					select = list_start;
				}
			}
		}
		if (static_cast<int>(choose) == LEFT)
		{
			if (list_start != 0)
			{
				if (list_t_max - num_tests_list < num_tests_list)
				{
					list_t_max -= list_t_max - list_start;
					list_start -= num_tests_list;
					select = list_start;
				}
			}
		}

		if (static_cast<int> (choose) == DOWN)
		{
			if (select < list_t_max - 1)
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

void Test::save_test(const char* category, const char* section)
{
	fs::create_directories(dir_an_path::Directories::Test::folder_test(category, section, test_name));

	save_num_questions(category, section);

	int i = 0;
	int len = 0;
	try
	{
		ofstream save;
		for (; i < this->num_questions_; i++)
		{
			save.open(dir_an_path::Path::Test::path_sv_questions(category, section, test_name, i));
			if (save.is_open())
			{
				len = quest[i].length();
				for (int e = 0; e < len; e++)
				{
					if (quest[i].text[e] == ' ')
					{
						quest[i].text[e] = '#';
					}
				}

				save << this->quest[i].text << endl << this->quest[i].answer << endl << this->quest[i].n_points << endl;
			}
			save.close();
		}
	}
	catch (...)
	{
		string error_text = "File save Error!\nPath";
		error_text += dir_an_path::Path::Test::path_sv_questions(category, section, test_name, i);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
	}

	add_new_test_name(category, section);
}

void Test::save_num_questions(const char* category, const char* section) const
{
	try
	{
		ofstream save_n_quests;
		save_n_quests.open(dir_an_path::Path::Test::path_sv_n_questions(category, section, test_name));
		if (save_n_quests.is_open())
		{
			save_n_quests << num_questions_ << endl;
		}
		save_n_quests.close();
	}
	catch (...)
	{
		string error_text = "File save Error!\nPath";
		error_text += dir_an_path::Path::Test::path_sv_n_questions(category, section, test_name);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

void Test::load_list_tests(const char* category, const char* section, set<string>& tests_list)
{
	SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_NORMAL);
	try
	{
		ifstream load;
		load.open(dir_an_path::Path::Test::path_test_list(category, section).c_str());
		if (load.is_open())
		{
			string tmp;
			while (!load.eof())
			{
				load >> tmp;
				for (int i = 0; i < tmp.size(); i++)
				{
					if (tmp[i] == '#')
					{
						tmp[i] = ' ';
					}
				}
				tests_list.emplace(tmp);
			}
		}
		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		load.close();
	}
	catch (...)
	{
		SetFileAttributesA(dir_an_path::Path::Test::path_test_list(category, section).c_str(), FILE_ATTRIBUTE_HIDDEN);
		string error_text = "File load Error!\nPath";
		error_text += dir_an_path::Path::Test::path_test_list(category, section);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

void Test::load_number_questions(const char* category, const char* section, const char* test_name)
{
	try
	{
		ifstream load_n_quests;
		load_n_quests.open(dir_an_path::Path::Test::path_sv_n_questions(category, section, test_name));
		if (load_n_quests.is_open())
		{
			load_n_quests >> num_questions_;
		}
		load_n_quests.close();
	}
	catch (...)
	{
		string error_text = "File Load Error!\nPath";
		error_text += dir_an_path::Path::Test::path_sv_n_questions(category, section, test_name);
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

Section::Section()
= default;

void Section::load_sections(const string& category, set<string>& sections)
{
	try
	{
		SetFileAttributesA(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str(), FILE_ATTRIBUTE_NORMAL);
		ifstream load_categories;
		load_categories.open(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str());
		if (load_categories.is_open())
		{
			string tmp_category;
			while (!load_categories.eof())
			{
				load_categories >> tmp_category;
				for (int i = 0; i < tmp_category.size(); i++)
				{
					if (tmp_category[i] == '#')
					{
						tmp_category[i] = ' ';
					}
				}
				sections.emplace(tmp_category);
			}
		}
		SetFileAttributesA(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str(), FILE_ATTRIBUTE_HIDDEN);
	}
	catch (...)
	{
		string error_text = "File Load Error!\nPath";
		error_text += dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

void Section::save_section(const string& category, char* name_section)
{
	SetFileAttributesA(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str(), FILE_ATTRIBUTE_NORMAL);
	try
	{
		fs::create_directory(dir_an_path::Directories::Test::Section::folder_section(category.c_str(), name_section));  // creating directory for sections
		ofstream save_section;
		save_section.open(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str(), ios::app);
		if (save_section.is_open())
		{
			for (auto i = 0; i < strlen(name_section); i++)
			{
				if (name_section[i] == ' ')
				{
					name_section[i] = '#';
				}
			}
			save_section << name_section << endl;
		}
		delete[] name_section;
		save_section.close();
		SetFileAttributesA(dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str(), FILE_ATTRIBUTE_HIDDEN);
		return;
	}
	catch (...)
	{
		delete[] name_section;
		string error_text = "File Load Error!\nPath";
		error_text += dir_an_path::Path::Test::Section::path_section_list(category.c_str()).c_str();
		MessageBoxA(GetActiveWindow(), error_text.c_str(), "Testing System", MB_ICONERROR);
		return;
	}
}

bool Section::show_sections(const string& category, bool type)
{
	char choose;

	vector tmp_sections(sections.begin(), sections.end());

	int list_start = 0;
	int list_c_max;
	int select = 0;
	constexpr int num_sections_list = 15;    // the number of categories in the list on the screen

	if (sections.size() < 10)
	{
		list_c_max = sections.size();
	}
	else
	{
		list_c_max = num_sections_list;
	}

	while (true)
	{
		this_thread::sleep_for(chrono::milliseconds(50));
		system("cls");
		cout << "\t\t\t   -------------------------------------------------------------------\n";
		cout << "\t\t\t   | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Go Back - \033[91mESC \033[97m|\n";
		cout << "\t\t\t   -------------------------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t--------------------------\n";
		cout << "\t\t\t\t\t\t|   \033[33mSelect    \033[92m Section   \033[97m|\n";
		cout << "\t\t\t\t       --------------------------------------------\n";
		cout << "\t\t\t\t       | \033[36mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - category.size()) + 2) << " |\n";
		cout << "\t\t\t\t       --------------------------------------------\n";

		for (int i = list_start; i < list_c_max; i++)
		{
			if (i == select)
			{
				cout << "\t\t\t\t\t    | \033[104m" << tmp_sections[i] << "\033[0m\033[97m" << setw(static_cast<streamsize>(cat_an_sec_len - tmp_sections[i].size()) + 2) << " |\n";
			}
			else
			{
				cout << "\t\t\t\t\t    | " << tmp_sections[i] << setw(static_cast<streamsize>(cat_an_sec_len - tmp_sections[i].size()) + 2) << " |\n";
			}
		}

		if ((list_c_max - list_start) < num_sections_list)
		{
			for (int i = 0; i < num_sections_list - (list_c_max - list_start); i++)
			{
				cout << "\t\t\t\t\t    |                                |\n";
			}
		}

		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    SC: " << select + 1 << " of " << sections.size() << endl;
		cout << "\t\t\t\t\t    ----------------------------------\n";
		cout << "\t\t\t\t\t    PG: " << list_start / 10 + 1 << " of "; if (sections.size() / 10 == 0) { cout << "1"; }
		else { sections.size() / 10; }

		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (type == true)
			{
				Test test;
				test.test_initialization(category.c_str(), tmp_sections[select].c_str());
				return true;
			}
			else
			{
				set<string> tests_list;
				Test::load_list_tests(category.c_str(), tmp_sections[select].c_str(), tests_list);
				if (tests_list.size() > 0)
				{
					Test::show_tests(category.c_str(), tmp_sections[select].c_str(), tests_list.begin(), tests_list.end());
					return true;
				}
				else
				{
					system("cls");
					cout << "\t\t\t   -------------------------------------------------------------------\n";
					cout << "\t\t\t   | \033[94mCONTROL \033[97m| \033[95mLEFT RIGHT \033[97m| \033[96mUP DOWN \033[97m| Select - \033[92mENTER\033[97m | Go Back - \033[91mESC \033[97m|\n";
					cout << "\t\t\t   -------------------------------------------------------------------\n\n";
					cout << "\t\t\t\t\t\t--------------------------\n";
					cout << "\t\t\t\t\t\t|   \033[33mSelect    \033[92m Section   \033[97m|\n";
					cout << "\t\t\t\t       --------------------------------------------\n";
					cout << "\t\t\t\t       | \033[36mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - category.size()) + 2) << " |\n";
					cout << "\t\t\t\t       --------------------------------------------\n";

					for (int i = list_start; i < list_c_max; i++)
					{
						if (i == select)
						{
							cout << "\t\t\t\t\t    | \033[104m" << tmp_sections[i] << "\033[0m\033[97m" << setw(static_cast<streamsize>(cat_an_sec_len - tmp_sections[i].size()) + 2) << " | " << " \033[91mNo tests created\033[97m\n";
						}
						else
						{
							cout << "\t\t\t\t\t    | " << tmp_sections[i] << setw(static_cast<streamsize>(cat_an_sec_len - tmp_sections[i].size()) + 2) << " |\n";
						}
					}

					if ((list_c_max - list_start) < num_sections_list)
					{
						for (int i = 0; i < num_sections_list - (list_c_max - list_start); i++)
						{
							cout << "\t\t\t\t\t    |                                |\n";
						}
					}

					cout << "\t\t\t\t\t    ----------------------------------\n";
					cout << "\t\t\t\t\t    SC: " << select + 1 << " of " << sections.size() << endl;
					cout << "\t\t\t\t\t    ----------------------------------\n";
					cout << "\t\t\t\t\t    PG: " << list_start / 10 + 1 << " of "; if (sections.size() / 10 == 0) { cout << "1"; }
					else { sections.size() / 10; }
					this_thread::sleep_for(chrono::milliseconds(1500));
				}
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return false;
		}
		if (static_cast<int>(choose) == RIGHT)
		{
			if (list_c_max != sections.size())
			{
				if (list_c_max + num_sections_list > sections.size()) // If list length max + 10 is greater than the number of logins
				{
					list_c_max = sections.size();
					list_start += num_sections_list;
					select = list_start;
				}
				else
				{
					list_c_max += num_sections_list;
					list_start += num_sections_list;
					select = list_start;
				}
			}
		}
		if (static_cast<int>(choose) == LEFT)
		{
			if (list_start != 0)
			{
				if (list_c_max - num_sections_list < num_sections_list)
				{
					list_c_max -= list_c_max - list_start;
					list_start -= num_sections_list;
					select = list_start;
				}
			}
		}

		if (static_cast<int> (choose) == DOWN)
		{
			if (select < list_c_max - 1)
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

void Section::add_section(const string& category)
{
	char* name_section = new char[cat_an_sec_len];
	name_section[0] = '\0';

	char choose;
	bool no_unique = false;
	bool key_down = false;

	for (size_t i = strlen(name_section);;)
	{
		// Show
		system("cls");
		cout << "\t\t\t\t    --------------------------------------------------\n";
		cout << "\t\t\t\t    |\033[94mCONTROL\033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t\t    --------------------------------------------------\n\n\n\n\n";
		cout << "\t\t\t\t\t\t      ----------------\n";
		cout << "\t\t\t\t\t\t      | \033[96mAdd  \033[95mSection \033[97m|\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    |  \033[94mEnter the name of the  \033[95mSection  \033[97m|\n";
		cout << "\t\t\t\t\t    |         \033[94myou  want to add\033[97m         |\n";
		cout << "\t\t\t\t\t    ------------------------------------\n";
		cout << "\t\t\t\t\t    |>: " << name_section << setw(static_cast<streamsize>(cat_an_sec_len - strlen(name_section)) + 1) << " |";
		for (auto it : sections)
		{
			if (strcmp(name_section, it.c_str()) == 0)
			{
				cout << "\033[91m a section by that name exists\033[97m";
				no_unique = true;
				break;
			}
			else
			{
				no_unique = false;
			}
		}

		cout << "\n\t\t\t\t\t    ------------------------------------\n";

		choose = _getch();

		if (static_cast<int> (choose) != -32 && key_down == false)
		{
			if ((choose >= 'a' && choose <= 'z') || (choose >= 'A' && choose <= 'Z') || (choose >= '0' && choose <= '9') || choose == ' ' || choose == '!' || choose == '_')
			{
				if (i < cat_an_sec_len - 1)
				{
					name_section[i] = choose;
					++i;
					name_section[i] = '\0';
				}
			}
			else
			{
				if (choose == '\b' && i > 0) // if user typed backspace
				{
					--i;
					name_section[i] = '\0';
					this_thread::sleep_for(chrono::milliseconds(30));
				}
				if (static_cast<int>(choose) == ESC)
				{
					delete[] name_section;
					return;
				}
				if (static_cast<int>(choose) == ENTER && strlen(name_section) > 3 && no_unique == false)
				{
					cout << "\t\t\t\t\t      | \033[92mCategory  successfully added\033[97m |";
					cout << "\n\t\t\t\t\t      --------------------------------\n";
					this_thread::sleep_for(chrono::seconds(2));
					sections.emplace(name_section);
					thread save(save_section, category, name_section);
					save.detach();
					return;
				}
			}
		}
		if (static_cast<int> (choose) == -32 && key_down == false) // if user typed key_down // first_key_down -32
		{
			key_down = true;
		}
		if (static_cast<int> (choose) == RIGHT && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == LEFT && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == UP && key_down == true)
		{
			key_down = false;
		}
		if (static_cast<int> (choose) == DOWN && key_down == true)  // second_key_down 80
		{
			key_down = false;
		}
	}
}

bool Section::section_initialization(const string& category)
{
	load_sections(category, sections);

	char move = '1';
	char choose;

	while (true)
	{
		system("cls");
		cout << "\t\t\t     --------------------------------------------------------------\n";
		cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
		cout << "\t\t\t     --------------------------------------------------------------\n\n\n\n\n";

		cout << "\t\t\t\t\t\t    --------------------\n";
		cout << "\t\t\t\t\t\t    | \033[33mCreating  a \033[94mTest \033[97m|\n";
		cout << "\t\t\t\t\t--------------------------------------------\n";
		cout << "\t\t\t\t\t| \033[36mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - category.size()) + 2) << " |\n";
		cout << "\t\t\t\t\t--------------------------------------------\n";
		switch (move)
		{
		case '1':
		{
			cout << "\t\t\t\t\t\t    |\033[104m1\033[0m\033[97m| \033[92mSelect \033[95mSection \033[97m|\n";
			cout << "\t\t\t\t\t\t    |2|   \033[96mAdd  \033[95mSection \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		case '2':
		{
			cout << "\t\t\t\t\t\t    |1| \033[92mSelect \033[95mSection \033[97m|\n";
			cout << "\t\t\t\t\t\t    |\033[104m2\033[0m\033[97m|   \033[96mAdd  \033[95mSection \033[97m|\n";
			cout << "\t\t\t\t\t\t    --------------------\n";
		}break;
		default:;
		}
		choose = _getch();

		if (static_cast<int>(choose) == ENTER)
		{
			if (move == '1')
			{
				if (!sections.empty())
				{
					if (show_sections(category, true) == false)
					{
					}
					else
					{
						return true;
					}
				}
				else
				{
					system("cls");
					cout << "\t\t\t     ----------------------------------------------------------------\n";
					cout << "\t\t\t     |\033[94mCONTROL\033[97m| \033[95mUp   Down \033[97m| Go to Back Menu - \033[91mESC\033[97m | Select - \033[92mENTER\033[97m |\n";
					cout << "\t\t\t     ----------------------------------------------------------------\n\n\n\n\n";

					cout << "\t\t\t\t\t\t    --------------------\n";
					cout << "\t\t\t\t\t\t    | \033[33mCreating  a \033[94mTest \033[97m|\n";
					cout << "\t\t\t\t\t--------------------------------------------\n";
					cout << "\t\t\t\t\t| \033[36mCategory\033[97m: " << category << setw(static_cast<streamsize>(cat_an_sec_len - category.size()) + 2) << " |\n";
					cout << "\t\t\t\t\t--------------------------------------------\n";
					cout << "\t\t\t\t\t\t    |\033[104m1\033[0m\033[97m| \033[92mSelect \033[95mSection \033[97m| \033[91mThere are no sections in this category!\033[97m\n";
					cout << "\t\t\t\t\t\t    |2|   \033[96mAdd  \033[95mSection \033[97m|\n";
					cout << "\t\t\t\t\t\t    --------------------\n";
					this_thread::sleep_for(chrono::milliseconds(1500));
				}
			}
			if (move == '2')
			{
				add_section(category);
			}
		}
		if (static_cast<int>(choose) == ESC)
		{
			return false;
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
	}
}

Section::~Section()
= default;

void operator<<(ofstream ofs, Test& obj)
{
}