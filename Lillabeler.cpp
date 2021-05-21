/*
	Lillabeler.cpp
	Dependency: OpenCV 4.5.2

	A piece of software which can automagicly label your pictures via the use of a digital twin.
*/

#include "Import.hpp"
#include "BBFinder.hpp"
#include "Formatter.hpp"
#include "Export.hpp"

#include <filesystem>

Import Im;
BBFinder Find;
Formatter Format;
Export Ex;

std::vector<std::string> *textFile;

int main()
{
	// Setup filesystem
	Im.Setup();
	Ex.Setup(Im.ClassPoint());

	while (true)
	{
		// Find BBoxes in a single image
		bool returnVal = Find.Draw(Im.ClassPoint(), Im.ColourPoint());

		// Check if we procesed all the files
		if (returnVal == false)
		{
			textFile = Format.FormatData(Find.BBoxesPoint(), Find.ImgWidthPoint(), Find.ImgHeightPoint());
			Ex.WriteBBox(textFile, Find.FileNamePoint());
		}
		else
		{
			break;
		}
	}

	// Create the train.txt file
	Ex.WriteTrain();
}
