/*
	Formatter.hpp
	A class that formats all the found data in the required arrangement
*/

#include "Formatter.hpp"
#include <opencv2/imgcodecs.hpp>
#include <string>
#include <vector>

// Class constructor
Formatter::Formatter(void)
{
	// Placeholder
}

std::vector<std::string>* Formatter::FormatData(std::vector<std::vector<cv::Rect>>* BBox, uint32_t* Width, uint32_t* Height)
{
	result.clear();
	std::string ClassNumber;
	std::string CenterXY;
	std::string WidthHeight;
	
	for (uint32_t ix = 0; ix < BBox->size(); ++ix)
	{
		for (uint32_t iy = 0; iy < BBox->at(ix).size(); ++iy)
		{
			// Save the class number of the current bounding box
			ClassNumber = std::to_string(ix);

			// Find the center of a bounding box and save it in a absolute measurement
			double CentX = (BBox->at(ix).at(iy).x + (BBox->at(ix).at(iy).width / 2)) / (double)*Width;
			double CentY = (BBox->at(ix).at(iy).y + (BBox->at(ix).at(iy).height / 2)) / (double)*Height;
			CenterXY = std::to_string(CentX) + " " + std::to_string(CentY);

			// Find the absolute width and height of the bounding box
			double absWidth = BBox->at(ix).at(iy).width / (double)*Width;
			double absHeight = BBox->at(ix).at(iy).height / (double)*Height;
			WidthHeight = std::to_string(absWidth) + " " + std::to_string(absHeight);

			// Save the string of data in a vector for exporting
			result.push_back(ClassNumber + " " + CenterXY + " " + WidthHeight);
		}
	}

	return &result;
}
