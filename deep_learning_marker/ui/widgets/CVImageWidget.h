#ifndef CVGRAPHICSVIEW_H
#define CVGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

#include "ui/widgets/CVImageViewer/CVGraphicsItem.h"
#include "ui/widgets/CVImageViewer/CVGraphicsScene.h"


class CVGraphicsView : public QGraphicsView
{
public:
	explicit CVGraphicsView(QWidget*);
	~CVGraphicsView();

	bool loadImage(const char*);
protected:
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

private:
	void init();

	bool isContainPoint(QPoint& point);
	QPoint mapToPixmap(QPoint& point);

private:
	QGraphicsScene* m_scene;
	QGraphicsPixmapItem* m_pixmapItem;
	QGraphicsView* m_view;

	float m_scalingFactory;
	bool m_isStartingCrop;
};

#endif // CVGRAPHICSVIEW_H
