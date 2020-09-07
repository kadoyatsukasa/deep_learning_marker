#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class MousePositionWidget;
class CVGraphicsView;
class OptionButtonBar;

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget();

private:
	void initWidget();
private slots:
	void handleDisplayImage(const char*);
private:
	Ui::MainWidget* ui;
	MousePositionWidget* m_mousePos;
	CVGraphicsView* m_image;
	OptionButtonBar* m_buttonBar;
};

#endif // MAINWIDGET_H
