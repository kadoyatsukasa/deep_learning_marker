#ifndef SIGNALCENTER_H
#define SIGNALCENTER_H

#include <QObject>

class SignalCenter :public QObject
{
	Q_OBJECT

public:
	static SignalCenter* instance();

signals:
	void displayImage(QString);
	void displayCurrentMousePoint(QPoint);
	void displayRoiStartPoint(QPoint);
	void displayRoiEndPoint(QPoint);

	void clearAllMarks();
private:
	explicit SignalCenter();
};

#endif // SIGNALCENTER_H
