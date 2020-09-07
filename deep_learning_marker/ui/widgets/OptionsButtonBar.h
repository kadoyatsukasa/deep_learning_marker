#ifndef OPTIONSBUTTONBAR_H
#define OPTIONSBUTTONBAR_H

#include <QWidget>

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
private:
	Ui::OptionsButtonBar* ui;
};

#endif // OPTIONSBUTTONBAR_H
