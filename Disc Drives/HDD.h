#pragma once
#include "Disc.h"
class HDD : public Disc
{

public:

	HDD();
	void Show_all_files_info() const override;
};
