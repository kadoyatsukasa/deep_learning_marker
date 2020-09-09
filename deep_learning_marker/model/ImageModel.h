#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H
#include<vector>
#include<QString>
#include<QImage>
#include <opencv2/opencv.hpp>

class ImageModel
{
public:
	static ImageModel* instance();

public:
	std::vector<QString> imageDirector;
	QString imageFilePathName;
	QString imageFilePath;
	QString imageFileName;

	cv::Mat srcImage;
	cv::Mat rgbImage;
	QImage targetImage;

	float scalingFactory;

private:
	explicit ImageModel();
};

#endif // IMAGEMODEL_H
