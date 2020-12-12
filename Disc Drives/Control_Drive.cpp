#include <iostream>
#include "Control_Drive.h"

void System::Control_Drive()
{

	//HDD drive;
	SSD drive; ////10 times faster than HDD in program

	try
	{
		//drive.Create_file("new.txt", "Hello World, how are you where are you!");
		//drive.Set_file_content("new.txt", "Nothing");
		//drive.Set_file_content("old.txt", "Nothing");//exception

		//drive.Create_file("new.txt", "Hello World, how are you where are you!");
		//drive.Create_file("old.txt", "Joker is coming help me to get out of here!");
		//drive.Create_file("biw.txt", "Everyone wants to go Paradise, but nobody wants to die!");
		//drive.Create_file("biw.txt", "Except You!");//exception


		//drive.Create_file("new.txt", "Hello World, how are you where are you!");
		//drive.Create_file("old.txt", "Joker is coming help me to get out of here!");
		//drive.Create_file("biw.txt", "Everyone wants to go Paradise, but nobody wants to die!");
		//drive.Delete_file_content("new.txt");
		//drive.Delete_file_content("new.txt");


		//drive.Create_file("new.txt", "Hello World, how are you where are you!");
		//drive.Create_file("old.txt", "Joker is coming help me to get out of here!");
		//drive.Create_file("biw.txt", "Everyone wants to go Paradise, but nobody wants to die!");
		//drive.Delete_file_by_file_name("old.txt");
		//drive.Delete_file_by_file_name("new.txt");
		//drive.Delete_file_by_file_name("hhhh");//exception
		//drive.Delete_file_by_file_name("biw.txt");

		drive.Create_file("new.txt", "Hello World, how are you where are you!");
		drive.Create_file("old.txt", "Joker is coming help me to get out of here!");
		drive.Create_file("biw.txt", "Everyone wants to go Paradise, but nobody wants to die!!");
		drive.Update_file_name("old.txt", "amazing.txt");
		drive.Hash_file("amazing.txt");
		
		drive.Show_all_files_info();
		
		std::cout << "\n\n\n====================== After Decoded =====================\n\n\n";
		
		drive.Decode_content("amazing.txt");
		drive.Update_file_name("newewe", "fsdfsf");//exception
	}
	catch (const char* ex)
	{
		std::cout << "Error: " << ex << '\n';
	}
	catch (const std::string& ex)
	{
		std::cout << "Error: " << ex << '\n';
	}

	std::cout << "\n\n";
	drive.Show_all_files_info();

}