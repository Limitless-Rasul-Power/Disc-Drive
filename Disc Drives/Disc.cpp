#include <iostream>
#include <ctime>
#include <windows.h>
#include "Disc.h"

void Set_console_color(const unsigned short& color_id)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_id);
}

void Set_date(char* const& date)
{
	time_t now = time(NULL);
	ctime_s(date, 26 * sizeof(char), &now);
}

Disc::File::File(const std::string& file_name, const std::string& file_content)
{
	Set_file_name(file_name);
	Set_file_content(file_content);
	this->is_content_hashed = false;
	Set_date(this->create_time);
	memcpy(this->change_time, "None", strlen("None"));
}

void Disc::File::Set_file_name(const std::string& file_name)
{
	if (file_name.empty())
		throw "File Name is Empty please fill it!";

	this->file_name = file_name;
}

std::string Disc::File::Get_file_name() const
{
	return file_name;
}

void Disc::File::Set_file_content(const std::string& file_content)
{
	this->file_content = file_content;
}

std::string Disc::File::Get_file_content() const
{
	return file_content;
}

const char* Disc::File::Get_create_time() const
{
	return create_time;
}

const char* Disc::File::Get_change_time() const
{
	return change_time;
}

bool Disc::File::Is_content_hashed() const
{
	return is_content_hashed;
}

void Disc::Set_file_count(const short& file_count)
{
	this->file_count = file_count;
}

unsigned short Disc::Get_file_count() const
{
	return file_count;
}

void Disc::Set_current_size(const double& current_size)
{
	this->current_size = current_size;
}

double Disc::Get_current_size() const
{
	return current_size;
}

void Disc::Set_write_speed(const short& write_speed)
{
	if (write_speed <= 0)
		throw "Write Speed must be more than 0!";

	this->write_speed = write_speed;
}

unsigned short Disc::Get_write_speed() const
{
	return write_speed;
}

bool Disc::Is_hashed(Disc::File* const& file) const
{
	if (file->is_content_hashed)
		return true;

	return false;
}

Disc::File* Disc::Get_file(const std::string& file_name) const
{
	for (unsigned short i = 0; i < Get_file_count(); i++)
	{
		if (files[i]->file_name == file_name)
			return files[i];
	}
	throw "File didn't exist!";
}


Disc::Disc(const short& write_speed)
{
	Set_write_speed(write_speed);
}

bool Disc::Is_exist(const std::string& file_name) const
{
	for (int i = 0; i < Get_file_count(); i++)
	{
		if (files[i]->file_name == file_name)
			return true;
	}
	return false;
}

void Disc::Delete_file_content(const std::string& file_name)
{
	if (Get_file_count() <= 0)
		throw "There is No File in the DISC!\n";

	bool is_here = Is_exist(file_name);

	if (!is_here)
		throw "There is no " + file_name + " in the DISC!\n";

	else if (Get_file(file_name)->Get_file_content().length() == 0)
		throw "This file content is already deleted!\n";

	File* file = Get_file(file_name);

	Set_current_size(Get_current_size() - file->file_content.length());

	file->file_content = "";
	std::cout << file_name << " Content Successfully Deleted!\n";
	file = nullptr;
}

void Disc::Delete_file_by_file_name(const std::string& file_name)
{
	if (Get_file_count() <= 0)
		throw "There is No File in the DISC!\n";

	bool is_here = Is_exist(file_name);

	if (!is_here)
		throw "There is no " + file_name + " in the DISC!\n";

	Disc::File** new_file = new Disc::File * [Get_file_count() - 1];
	unsigned short go = 0U;

	for (unsigned short i = 0; i + go < Get_file_count(); i++)
	{
		if (files[i]->file_name == file_name)
		{
			Set_current_size(Get_current_size() - files[i]->file_content.length());
			delete files[i];
			++go;
		}

		if (i + go < Get_file_count())
			new_file[i] = files[i + go];
	}

	delete[] files;

	files = new_file;
	new_file = nullptr;

	Set_file_count(Get_file_count() - 1);
}

void Disc::Create_file(const std::string& file_name, const std::string& content)
{
	bool is_here = Is_exist(file_name);

	if (is_here)
		throw "This " + file_name + " exist, please change name!\n";

	if (Get_current_size() + content.length() >= max_capacity)
		throw "Disc is Full!\n";

	std::cout << "File is Creating and Content is adding...\n";
	Sleep((content.length() / Get_write_speed()) * 1000);
	system("CLS");

	std::cout << "Successfully Created and Added Content!\n\n";

	File* added_file = new File(file_name, content);

	File** new_file = new File * [Get_file_count() + 1];

	for (unsigned short i = 0; i < Get_file_count(); i++)
		new_file[i] = files[i];

	delete[] files;

	new_file[Get_file_count()] = added_file;
	files = new_file;

	new_file = nullptr;
	added_file = nullptr;

	Set_current_size(Get_current_size() + content.length());
	Set_file_count(Get_file_count() + 1);
}

void Disc::Set_file_content(const std::string& file_name, const std::string& content)
{
	bool is_here = Is_exist(file_name);

	if (!is_here)
		throw "There is no " + file_name + " in the disk!\n";

	if (Get_current_size() + content.length() >= max_capacity)
		throw "Disc is Full!\n";

	std::cout << "File Content is setting...\n";
	Sleep((content.length() / Get_write_speed()) * 1000);
	system("CLS");
	std::cout << "Successfully Setted!\n\n";

	for (unsigned short i = 0; i < Get_file_count(); i++)
	{
		if (files[i]->file_name == file_name)
		{
			Set_current_size(Get_current_size() - files[i]->file_content.length());
			files[i]->file_content = content;
			Set_current_size(Get_current_size() + content.length());
			Sleep(1000);
			Set_date(files[i]->change_time);
		}
	}	
}

void Disc::Update_file_name(const std::string& old_file_name, const std::string& new_file_name)
{
	bool is_here = Is_exist(old_file_name);

	if (!is_here)
		throw "There is no " + old_file_name + " in the disk!\n";

	File* file = Get_file(old_file_name);
	file->file_name = new_file_name;
	
	Sleep(1000);
	Set_date(file->change_time);
	std::cout << old_file_name << " successfully changed to " << new_file_name << '\n';
	file = nullptr;
}

void Disc::Hash_file(const std::string& file_name) const
{
	bool is_here = Is_exist(file_name);

	if (!is_here)
		throw "There is no " + file_name + " in the disk!\n";

	if (Is_hashed(Get_file(file_name)))
		throw file_name + " is already hashed!";


	File* file = Get_file(file_name);

	unsigned short hash{ 0U };

	std::string hash_content{};
	for (size_t i = 0; i < file->file_content.length(); i++)
	{
		hash = (unsigned short)(file->file_content.at(i) ^ 'ə');
		hash_content += (char)hash;
	}

	Sleep(1000);
	Set_date(file->change_time);
	file->file_content = hash_content;
	file->file_content.shrink_to_fit();
	file->is_content_hashed = true;
	file = nullptr;
}

void Disc::Decode_content(const std::string& file_name)
{
	bool is_here = Is_exist(file_name);

	if (!is_here)
		throw "There is no " + file_name + " in the disk!\n";

	if (!Is_hashed(Get_file(file_name)))
		throw file_name + " isn't hashed!";

	File* file = Get_file(file_name);

	unsigned short decode{ 0U };
	std::string decode_content{};

	std::cout << "\n\n";
	for (size_t i = 0; i < file->file_content.length(); i++)
	{
		decode = (unsigned short)(file->file_content.at(i) ^ 'ə');
		decode_content += (char)decode;
	}

	Sleep(1000);
	Set_date(file->change_time);
	file->file_content = decode_content;
	file->file_content.shrink_to_fit();
	file->is_content_hashed = false;
	file = nullptr;

}

void Disc::Show_all_files_info() const
{
	for (unsigned short i = 0; i < Get_file_count(); i++)
	{
		std::cout << '#' << i + 1 << ", File Name: " << files[i]->Get_file_name() << ", " << \
			"Content: " << files[i]->Get_file_content() << '\n';
		Set_console_color(GREEN);
		std::cout << '#' << i + 1 << ", File Create Time: " << files[i]->Get_create_time();
		Set_console_color(RED);
		std::cout << '#' << i + 1 << ", File Change Time: " << files[i]->Get_change_time() << "\n\n";
		Set_console_color(WHITE);
	}
	std::cout << "Disc write speed: " << Get_write_speed() << " byte/second\n";
	std::cout << "Disc Max Capacity: " << max_capacity << " GB\n";
	std::cout << "Available Space: " << max_capacity - Get_current_size() << " GB\n";
	std::cout << "Loaded Space: " << Get_current_size() << " GB\n";
}

Disc::~Disc()
{
	for (unsigned short i = 0; i < Get_file_count(); i++)
		delete files[i];

	delete[] files;
}