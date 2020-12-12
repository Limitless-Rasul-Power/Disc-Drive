#include <iostream>
#include "HDD.h"

HDD::HDD() :Disc(HARD_DISK_DRIVE_WRITE_SPEED)
{}

void HDD::Show_all_files_info() const
{
	std::cout << "HDD INFORMATION\n\n";
	Disc::Show_all_files_info();
}