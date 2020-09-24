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

enum DIRECTION
{
	FORE,
	NEXT
};
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
	void handleSelectPara(const QModelIndex& index);

private:
	void initWidget();

private:
	Ui::MainWidget* ui;

	QPen m_pen;
	std::vector<QString>::iterator m_currentImage;
	int m_currentRow;
};

#endif // MAINWIDGET_H
