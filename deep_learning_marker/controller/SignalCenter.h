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

private:
	explicit SignalCenter();
};

#endif // SIGNALCENTER_H
