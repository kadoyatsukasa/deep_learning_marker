#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H
#include<vector>
#include<QString>
#include<QImage>
#include <QFileInfo>
#include <opencv2/opencv.hpp>

class ImageModel
{
public:
	static ImageModel* instance();

public:
	std::vector<QFileInfo> imageArchive;
	std::vector<QFileInfo>::iterator currentImage;
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
