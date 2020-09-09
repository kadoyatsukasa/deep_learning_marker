#ifndef SIGNALCENTER_H
#define SIGNALCENTER_H

#include <QObject>

class SignalCenter :public QObject
{
	Q_OBJECT

public:
	static SignalCenter* instance();

signals:
	void displayImage(const char*);
	void displayCurrentMousePoint(QPoint);
	void displayRoiStartPoint(QPoint);
	void displayRoiEndPoint(QPoint);

	//void clearAllRects(std::vector<QRect> roiRects);
	//void clearAllStartPoints(std::vector<QPoint> startPoints);
	//void clearAllEndPoints(std::vector<QPoint> endPoints);
	void clearAllMarks();

private:
	explicit SignalCenter();
};

#endif // SIGNALCENTER_H
