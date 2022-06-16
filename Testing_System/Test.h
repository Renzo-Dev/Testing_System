#pragma once
#include "Local_Database.h"

constexpr  size_t test_name_length = 31;  // *

class Section
{
protected:

	Section(); // Constructor

	set<string> sections;  // section list

	static void load_sections(const string& category, set<string>& sections); // load sections(for section list)
	static void save_section(const string& category, char* name_section); // save sections (by section list)

	bool show_sections(const string& category, bool type); // show sections(section list)

	void add_section(const string& category); // add section(save new section)

	bool section_initialization(const string& category); // Section Context Menu (Select,Add)

	~Section(); // Destructor
};

class Category : protected Section
{
public:

	Category(); // Constructor - init category list(load_categories)

	set<string> categories; // category list

	static void load_categories(set<string>& categories); // load categories (for category list)
	static void save_category(char* name_category);  // save categories (by category list)

	bool show_categories(bool type);  // show categories (show category list)

	void add_category();  // add category (save new category)

	void category_initialization(); // Category Context Menu (Select,Add)

	~Category(); // Destructor
};

class Test
{
	typedef class Question  // QUESTION TYPE
	{
	public:
		size_t length_text = 271;   // Number of characters in the text
		char* text = nullptr; // *ptr text = nullptr
		int n_points = 0; // number of points
		bool answer;

		Question() : text(new char[length_text + 1]), answer(false)  // default answer= false, init text*length_text
		{
			for (int i = 0; i < length_text; i++)
			{
				text[i] = ' ';
			}
			text[length_text] = '\0';  // termination zero
		}

		size_t length() const   // return length of obj->text<- length (const)
		{
			int size = 0;
			for (int i = 0; i < length_text; i++)
			{
				if (text[i] == '\0')
				{
					size = i;
					return size;
				}
				if (text[i] == ' ' && text[i + 1] == ' ' && text[i + 2] == ' ')
				{
					size = i;
					return size;
				}
				size++;
			}
			return size;
		}

		~Question()  // Destructor
		{
			delete[] this->text;
		}
	}question;

public:
	int num_questions_ = 0;         // Number of Questions

	char* test_name = nullptr;

	question* quest = nullptr;        // *ptr questions = nullptr

	void operator()(size_t new_n_q);  // dynamically changing and initialization the number of questions

	Test();               // Default Constructor

	explicit Test(const char* test_name);

	void quest_initialization(const char* category, const char* section);  //

	void test_initialization(const char* category, const char* section);       // Creating a test. Setting the parameters. Saving a test

	void test_save_finish(const char* category, const char* section);  //

	Test(size_t num_q);               // Constructor for runtime initialization of the number of questions
									  // num_q - number of questions in the object(class Test)

	~Test(); // Destructor

	static void show_tests(const char* category, const char* section, set<string>::const_iterator s_beg, set<string>::const_iterator s_end);

	void save_test(const char* category, const char* section); // save test

	void save_num_questions(const char* category, const char* section) const; // save number questions (by test)

	void add_new_test_name(const char* category, const char* section); // add new test nam

	static void save_list_tests(const char* category, const char* section, set<string>& test_list);

	void load_test(const char* category, const char* section); // laod test

	static void load_list_tests(const char* category, const char* section, set<string>& tests_list); // load test

	void load_number_questions(const char* category, const char* section, const char* test_name); // load number questions
};