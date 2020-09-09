#ifndef OPTIONSBUTTONBAR_H
#define OPTIONSBUTTONBAR_H

#include <QWidget>
//#include <QSettings>
#include <QFile>
#include <QFileInfo>

namespace Ui {
	class OptionsButtonBar;
}

class OptionsButtonBar : public QWidget
{
	Q_OBJECT

public:
	explicit OptionsButtonBar(QWidget* parent = nullptr);
	~OptionsButtonBar();

private slots:
	void handleLoadSingleImage();
	void handleSaveAllPositions();
	void handleClearAllMarks();

private:
	void clearAllRects(std::vector<QRect> roiRects);
	void clearAllStartPoints(std::vector<QPoint> startPoints);
	void clearAllEndPoints(std::vector<QPoint> endPoints);

private:
	Ui::OptionsButtonBar* ui;
};

#endif // OPTIONSBUTTONBAR_H
