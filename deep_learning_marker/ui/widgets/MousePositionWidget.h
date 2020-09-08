#ifndef MOUSEPOSTIONWIDGET_H
#define MOUSEPOSTIONWIDGET_H

#include <QWidget>

namespace Ui {
	class MousePositionWidget;
}

class MousePositionWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MousePositionWidget(QWidget* parent = nullptr);
	~MousePositionWidget();

private slots:
	void handleChangeCurrentPosition(QPoint current);
	void handleChangeRoiStart(QPoint start);
	void handleChangeRoiEnd(QPoint end);
private:
	Ui::MousePositionWidget* ui;
};

#endif // MOUSEPOSTIONWIDGET_H
