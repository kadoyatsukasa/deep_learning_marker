#ifndef ROIRECTMODEL_H
#define ROIRECTMODEL_H

#include <QPoint>
#include <QPainter>

class RoiRectModel
{
public:
	static RoiRectModel* instance();

	inline int height()const { return qAbs(startPoint.y() - endPoint.y()); }
	inline int width()const { return qAbs(startPoint.x() - endPoint.x()); }
	inline QSize& size()const { return QSize(width(), height()); }

public:
	QPoint startPoint;
	QPoint endPoint;

	std::vector<QPoint> roiStartPoints;
	std::vector<QPoint> roiEndPoints;
	std::vector<QRect> roiRects;

	const std::vector<QBrush> brush = {
		Qt::red,
		Qt::green,
		Qt::yellow,
		Qt::black,
		Qt::white
	};

	std::vector<QPen> pencilCase;

private:
	RoiRectModel();
};

#endif // ROIRECTMODEL_H
