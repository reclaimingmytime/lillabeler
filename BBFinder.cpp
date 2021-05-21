/*
	BBFinder.hpp
	Class to implement the bounding box finding algorithme
*/

#include "BBFinder.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

// Class constructor
BBFinder::BBFinder(void)
{
	// Placeholder
}

bool BBFinder::Draw(std::vector<std::string>* ClassPath, std::vector<std::string>* ColourPath)
{
	// Check if we have iterated over every image
	if (index >= ColourPath->size())
	{
		// Clear data out of memory
		BBoxes.clear();

		// Return true if all pictures have been labeled
		return true; 
	}
	else
	{
		// Clear previos data out of memory
		BBoxes.clear();

		// Find the filename of the current picture to be labeled
		size_t pos = 0;
		pos = ColourPath->at(index).find_last_of(47);
		FileName = ColourPath->at(index).substr(pos + 1, ColourPath->at(index).size());
	}

	// Iterate through all classes
	for (uint32_t i = 0; i < ClassPath->size(); ++i)
	{
		// Read image to Mat format
		cv::Mat Img;
		Img = cv::imread(ClassPath->at(i) + "/" + FileName);

		// Prepare image for contour finder
		cv::Mat ImgGray;
		cv::Mat ImgBin;
		cv::Mat ImgBinInv;
		cv::cvtColor(Img, ImgGray, cv::COLOR_BGR2GRAY);
		cv::threshold(ImgGray, ImgBin, 105, 255, cv::THRESH_BINARY);
		cv::threshold(ImgGray, ImgBinInv, 95, 255, cv::THRESH_BINARY_INV);

		cv::Mat ResultMat = ImgBin + ImgBinInv;
		
		// Find the contours
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		findContours(ImgBinInv, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		// Calculate the area of all the contours and delete any contours that are smaller or greater than a predefined value
		for (uint32_t i = 0; i < contours.size(); ++i)
		{
			// Calculate the area of the currently selected contour
			double area = contourArea(contours.at(i));
			if (area < MinArea || contours.at(i).size() > MaxPoints)
			{
				// Delete the data out of the vectors
				contours.erase(contours.begin() + i);
				hierarchy.erase(hierarchy.begin() + i);
				--i;
			}
			else if (contours.at(i).size() > MaxPoints)
			{
				// Delete the data out of the vectors
				contours.erase(contours.begin() + i);
				hierarchy.erase(hierarchy.begin() + i);
				--i;
			}
		}

		// Save all the minimal enclousing rectangles and the size of the image
		std::vector<cv::Rect> totalRect(contours.size());
		for (uint32_t i = 0; i < contours.size(); ++i)
		{
			totalRect.at(i) = boundingRect(contours.at(i));
		}

		// Print contours to image
		cv::Mat ImgCopy = Img.clone();
		for (uint32_t i = 0; i < contours.size(); ++i)
		{
			cv::Scalar colour(rand() & 255, rand() & 255, rand() & 255);
			cv::drawContours(ImgCopy, contours, i, colour, cv::FILLED, 8, hierarchy);
		}

		// Save data for use by the next class
		BBoxes.push_back(totalRect);
		ImgWidth = Img.cols;
		ImgHeight = Img.rows;
	}

	++index;
	return false;
}

// Returns a pointer to all the detected bounding boxes
std::vector<std::vector<cv::Rect>>* BBFinder::BBoxesPoint(void)
{
	return &BBoxes;
}

// Returns a pointer to the paths of all the class names
uint32_t* BBFinder::ImgWidthPoint(void)
{
	return &ImgWidth;
}

// Returns a pointer to the paths of all the class names
uint32_t* BBFinder::ImgHeightPoint(void)
{
	return &ImgHeight;
}

// Returns a pointer to the paths of all the class names
std::string* BBFinder::FileNamePoint(void)
{
	return &FileName;
}
