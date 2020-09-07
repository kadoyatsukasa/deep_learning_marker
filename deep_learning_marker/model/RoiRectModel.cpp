#include "RoiRectModel.h"

RoiRectModel::RoiRectModel()
{
}

RoiRectModel* RoiRectModel::instance()
{
	static RoiRectModel roi;
	return &roi;
}