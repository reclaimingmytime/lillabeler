/*
	Import.hpp
	Class to implement the import functionality
*/

#ifndef IMPORT
#define IMPORT

#include <string>
#include <vector>

// Class declaration
class Import
{
	private:
		std::vector<std::string> ClassPaths;		// Path to the coloured class pictures
		std::vector<std::string> ColourPictPaths;	// Path to the colour pictures

	public:
		Import(void);
		void Setup();

		std::vector<std::string>* ClassPoint(void);
		std::vector<std::string>* ColourPoint(void);
};

#endif
