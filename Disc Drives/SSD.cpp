#include <iostream>
#include "SSD.h"

SSD::SSD() :Disc(SOLID_STATE_DRIVE_WRITE_SPEED)
{}

void SSD::Show_all_files_info() const
{
	std::cout << "SSD INFORMATION\n\n";
	Disc::Show_all_files_info();
}
