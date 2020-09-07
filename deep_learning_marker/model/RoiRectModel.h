#ifndef ROIRECTMODEL_H
#define ROIRECTMODEL_H

#include <QPoint>
#include <QPainter>

class RoiRectModel
{
public:
	static RoiRectModel* instance();

	inline int height()const { return qAbs(start.y() - end.y()); }
	inline int width()const { return qAbs(start.x() - end.x()); }
	inline QSize& size()const { return QSize(width(), height()); }

public:
	QPoint start;
	QPoint end;
private:
	RoiRectModel();
};

#endif // ROIRECTMODEL_H
