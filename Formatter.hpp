/*
	Formatter.hpp
	A class that formats all the found data in the required arrangement
*/

#ifndef FORMATTER
#define FORMATTER

#include <opencv2/imgcodecs.hpp>
#include <string>
#include <vector>

// Class declaration
class Formatter
{
	private:
		std::vector<std::string> result;

	public:
		Formatter(void);
		std::vector<std::string>* FormatData(std::vector<std::vector<cv::Rect>>* BBoxes, uint32_t* ImgWidth, uint32_t* ImgHeight);

};

#endif
