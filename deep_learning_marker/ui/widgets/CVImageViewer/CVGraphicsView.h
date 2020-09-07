#ifndef CVIMAGEVIEW_H
#define CVIMAGEVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include "CVGraphicsScene.h"
#include "CVGraphicsItem.h"
#include "model/ImageModel.h"

class CVGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit CVGraphicsView(QWidget* parent = nullptr);

	void loadImage(const char* img);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	//void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void init();
	bool isContainPoint(const QPoint& point);
	QPoint mapToPixmap(const QPoint& point);

private:
	CVGraphicsItem* m_pixmap;
	CVGraphicsScene* m_scene;

	bool m_isStartingCrop;
};

#endif // CVIMAGEVIEW_H
