/*
	Export.hpp
	Class to implement the export functionality
*/

#ifndef EXPORT
#define EXPORT

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

// Class declaration
class Export
{
	private:
		std::vector<std::string> ClassNames;
		std::vector<std::string> TrainFile;

	public:
		Export(void);
		void Setup(std::vector<std::string>* ClassPath);
		void WriteBBox(std::vector<std::string>* BBoxString, std::string* FileName);
		void WriteTrain(void);
		std::vector<std::string>* ClassNamesPoint(void);
};

#endif
