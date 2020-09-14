#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPen>

class MousePositionWidget;
class CVGraphicsView;
class OptionsButtonBar;
class ParamList;

namespace Ui {
	class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget();

protected:
	void keyPressEvent(QKeyEvent* event);

private slots:
	void handleDisplayImage(QString);
	void handleChangePen(const QModelIndex& index);

private:
	Ui::MainWidget* ui;
	MousePositionWidget* m_mousePos;
	CVGraphicsView* m_image;
	OptionsButtonBar* m_buttonBar;
	ParamList* m_list;

	QPen m_pen;
	std::vector<QString>::iterator m_currentImage;
};

#endif // MAINWIDGET_H
