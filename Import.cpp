/*
	Import.hpp
	Class to implement the import functionality
*/

#include "Import.hpp"
#include <iostream>
#include <filesystem>

// Class constructor
Import::Import(void)
{
	// Placeholder
}

// Find the paths and location of all the files
void Import::Setup(void)
{
	std::filesystem::path dir_path = std::filesystem::current_path();

	std::string dir_string = std::filesystem::current_path().string();

	// Find all the folders in current scope
	for (const auto& entry : std::filesystem::directory_iterator(dir_path))
	{
		// Flag for marking if current string is a file
		bool isFile = false;

		//std::cout << entry.path() << std::endl; // Debug

		// Convert path to string var
		std::string temp_string = entry.path().string();

		// Look for a . in the name
		for (uint32_t i = 0; i < temp_string.size(); ++i)
		{
			if (temp_string.at(i) == 46) // 46 = "."
			{
				isFile = true;
				break;
			}
			else if (temp_string.at(i) == 92) // 92 = "\\")
			{
				temp_string.at(i) = 47; // 47 = "/"
			}
		}

		// Save the path
		if (isFile == false)
		{
			ClassPaths.push_back(temp_string);
		}
		else
		{
			// Check the file type for .jpg or .png before saving it
			std::string prefix;
			bool active = false;
			for (uint32_t i = 0; i < temp_string.size(); ++i)
			{
				// Check for a dot
				if (temp_string.at(i) == 46) // 46 = "."
				{
					active = true;
				}

				if (active == true)
				{
					prefix = prefix + temp_string.at(i);
				}
			}

			if (prefix == ".png" || prefix == ".jpg")
			{
				ColourPictPaths.push_back(temp_string);
			}
		}
	}
}

// Find the paths and location of all the files
std::vector<std::string>* Import::ClassPoint(void)
{
	return &ClassPaths;
}

// Returns a pointer to the paths of all the colour pictures
std::vector<std::string>* Import::ColourPoint(void)
{
	return &ColourPictPaths;
}
