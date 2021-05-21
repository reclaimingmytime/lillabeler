/*
	BBFinder.hpp
	Class to implement the bounding box finding algorithme
*/

#ifndef BBFINDER
#define BBFINDER

#include <opencv2/imgcodecs.hpp>
#include <string>
#include <vector>

// Class declaration
class BBFinder
{
	private:
		uint32_t index = 0;
		double MinArea = 1000;
		double MaxPoints = 3500;
		
		std::vector<std::vector<cv::Rect>> BBoxes;
		std::string FileName;
		uint32_t ImgWidth = 0;
		uint32_t ImgHeight = 0;

	public:
		BBFinder(void);
		bool Draw(std::vector<std::string>* ClassPath, std::vector<std::string>* ColourPath);
		std::vector<std::vector<cv::Rect>>* BBoxesPoint(void);
		std::string* FileNamePoint(void);
		uint32_t* ImgWidthPoint(void);
		uint32_t* ImgHeightPoint(void);
};

#endif
