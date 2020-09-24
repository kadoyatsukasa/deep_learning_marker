#ifndef OPTIONSBUTTONBAR_H
#define OPTIONSBUTTONBAR_H

#include <QWidget>
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
	void handleLoadArchive();
	void handleSaveAllPositions();
	void handleClearAllMarks();

private:
	void readConfig();

private:
	Ui::OptionsButtonBar* ui;
};

#endif // OPTIONSBUTTONBAR_H
