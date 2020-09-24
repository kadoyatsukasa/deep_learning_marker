#ifndef ROIRECTMODEL_H
#define ROIRECTMODEL_H

#include <QPoint>
#include <QPainter>

struct PEN_CASE
{
	QPen crayon;
	QRect rect;
};

struct REGION_CASE
{
	QString paraName;
	std::vector<PEN_CASE> regions;
};

class RoiRectModel
{
public:
	static RoiRectModel* instance();

	inline int height()const { return qAbs(startPoint.y() - endPoint.y()); }
	inline int width()const { return qAbs(startPoint.x() - endPoint.x()); }
	inline QSize& size()const { return QSize(width(), height()); }

	void dataReset();
	bool dataExists();

public:
	QPoint startPoint;
	QPoint endPoint;

	std::vector<QPoint> roiStartPoints;
	std::vector<QPoint> roiEndPoints;
	std::vector<QRect> roiRects;

	const std::vector<int> colourPen = {
		0xFF0000,
		0xFF1493,
		0x00FF00,
		0x00FFFF,
		0x00FF7F,
		0xFF00FF
	};

	std::vector<REGION_CASE> regionCase;
	PEN_CASE suit;
	REGION_CASE roiItem;

private:
	RoiRectModel();
};

#endif // ROIRECTMODEL_H
