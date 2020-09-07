#include "ImageModel.h"

ImageModel::ImageModel()
{
}

ImageModel* ImageModel::instance()
{
	static ImageModel ins;
	return &ins;
}