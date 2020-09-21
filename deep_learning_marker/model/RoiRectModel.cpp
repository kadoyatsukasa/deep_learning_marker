#include "RoiRectModel.h"

RoiRectModel::RoiRectModel()
{
	suit.crayon.setWidth(3);
}

RoiRectModel* RoiRectModel::instance()
{
	static RoiRectModel roi;
	return &roi;
}

void RoiRectModel::dataReset()
{
	roiRects.clear();
	roiStartPoints.clear();
	roiEndPoints.clear();
	startPoint = QPoint(0, 0);
	endPoint = QPoint(0, 0);

	std::vector<REGION_CASE>::iterator t_caseIterator;
	std::vector<PEN_CASE>::iterator t_it;
	for (t_caseIterator = regionCase.begin(); t_caseIterator != regionCase.end();)
	{
		for (t_it = t_caseIterator->regions.begin(); t_it != t_caseIterator->regions.end();)
		{
			t_it = t_caseIterator->regions.erase(t_it);
		}
		t_caseIterator = regionCase.erase(t_caseIterator);
	}
	roiItem.regions.clear();
}

bool RoiRectModel::dataExsits()
{
	return
		!(roiRects.empty() ||
			roiStartPoints.empty() ||
			roiEndPoints.empty() ||
			startPoint.isNull() ||
			endPoint.isNull() ||
			regionCase.empty() ||
			roiItem.regions.empty());
}