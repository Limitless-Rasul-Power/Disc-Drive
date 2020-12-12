#pragma once
#include <string>
#define HARD_DISK_DRIVE_WRITE_SPEED             30
#define SOLID_STATE_DRIVE_WRITE_SPEED           HARD_DISK_DRIVE_WRITE_SPEED * 10
#define MAX_DISC_CAPACITY                       500

#define RED                                     12
#define GREEN                                   10
#define WHITE                                   7

class Disc
{

protected:

	struct File
	{
		std::string file_name;
		std::string file_content;
		bool is_content_hashed;
		char create_time[26]{};
		char change_time[26]{};

		File(const std::string&, const std::string&);

		void Set_file_name(const std::string&);
		std::string Get_file_name() const;

		void Set_file_content(const std::string&);
		std::string Get_file_content() const;

		bool Is_content_hashed() const;

		const char* Get_create_time() const;

		const char* Get_change_time() const;

	};

	double current_size{ 0 };
	File** files;
	unsigned short file_count{ 0 };
	unsigned short write_speed = 30;


	void Set_file_count(const short&);

	unsigned short Get_file_count() const;

	void Set_current_size(const double&);

	double Get_current_size() const;

	void Set_write_speed(const short&);

	unsigned short Get_write_speed() const;

	bool Is_hashed(File* const&) const;

	File* Get_file(const std::string&) const;

public:

	const static double max_capacity;

	Disc(const short&);

	bool Is_exist(const std::string&) const;

	void Delete_file_content(const std::string&);

	void Delete_file_by_file_name(const std::string&);

	void Create_file(const std::string&, const std::string& = "");

	void Set_file_content(const std::string&, const std::string&);

	void Update_file_name(const std::string&, const std::string&);

	void Hash_file(const std::string&) const;

	void Decode_content(const std::string&);

	virtual void Show_all_files_info() const;

	~Disc();

};

void Set_date(char* const&);

void Set_console_color(const unsigned short&);