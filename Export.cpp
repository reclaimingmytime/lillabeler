/*
	Export.hpp
	Class to implement the export functionality
*/

#include "Export.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

// Class constructor
Export::Export(void)
{
	// Placeholder
}

// Setup class to make a the needed .txt files
void Export::Setup(std::vector<std::string>* ClassPath)
{
	// Save the names of the classes to a var
	for (uint32_t i = 0; i < ClassPath->size(); ++i)
	{
		size_t pos = 0;
		std::string temp;
		pos = ClassPath->at(i).find_last_of(47);
		temp = ClassPath->at(i).substr(pos + 1, ClassPath->at(i).size());
		ClassNames.push_back(temp);
	}

	// Create directorie structure
	std::filesystem::create_directories("data/img");

	// Write a file which links all other data to each other
	std::ofstream File1("data/obj.data");
	if (File1.is_open())
	{
		File1 << "classes = " + std::to_string(ClassNames.size()) + "\n";
		File1 << "train = data/train.txt\n";
		File1 << "valid = data/train.txt\n";
		File1 << "names = data/obj.names\n";
		File1 << "backup = backup/";
		File1.close();
	}

	// Write all the names of the classes to a .txt file
	std::ofstream File2("data/obj.names");
	if (File2.is_open())
	{
		for (uint32_t i = 0; i < ClassNames.size(); ++i)
		{
			if (i + 1 != ClassNames.size())
			{
				File2 << ClassNames.at(i) + "\n";
			}
			else
			{
				File2 << ClassNames.at(i);
			}
		}
		File2.close();
	}
}

// Write BBox location to a .txt file
void Export::WriteBBox(std::vector<std::string>* BBoxString, std::string* FileName)
{
	// Remove file extention
	size_t pos = 0;
	std::string FileNameEx;
	pos = FileName->find_last_of(46);
	FileNameEx = FileName->substr(0, pos);

	// Write all the names of the classes to a .txt file
	std::ofstream File("data/img/" + FileNameEx + ".txt");
	if (File.is_open())
	{
		for (uint32_t i = 0; i < BBoxString->size(); ++i)
		{
			if (i + 1 != BBoxString->size())
			{
				File << BBoxString->at(i) + "\n";
			}
			else
			{
				File << BBoxString->at(i);
			}
		}
		File.close();
	}

	// Copy picture to data/img/
	std::filesystem::copy(*FileName, "data/img/" + *FileName);

	// Save filename to var for making train.txt file at the end
	TrainFile.push_back("data/img/" + *FileName);
}

// Write the locations of all the training data to one .txt file called: train.txt
void Export::WriteTrain(void)
{
	// Write the locations of all the data to a single file
	std::ofstream File("data/train.txt");
	if (File.is_open())
	{
		for (uint32_t i = 0; i < TrainFile.size(); ++i)
		{
			if (i + 1 != TrainFile.size())
			{
				File << TrainFile.at(i) + "\n";
			}
			else
			{
				File << TrainFile.at(i);
			}
		}
		File.close();
	}
}
