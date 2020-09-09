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

	//void saveAllStartPositions(QSettings& setting, std::vector<QPoint> startPoints);
	//void saveAllEndPositions(QSettings& setting, std::vector<QPoint> endPoints);
	//void saveAllRects(QSettings& setting, std::vector<QRect> roiRects);

	void saveAllStartPositions(QFile& file, std::vector<QPoint> pos);
	void saveAllEndPositions(QFile& file, std::vector<QPoint> pos);
	void saveAllRects(QFile& file, std::vector<QRect> roiRects);

private:
	Ui::OptionsButtonBar* ui;
};

#endif // OPTIONSBUTTONBAR_H
