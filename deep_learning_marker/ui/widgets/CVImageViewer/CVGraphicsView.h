#ifndef CVIMAGEVIEW_H
#define CVIMAGEVIEW_H

#include <QGraphicsView>
#include <QWidget>
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
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void init();
	bool isContainPoint(const QPoint& point);
	QPoint mapToPixmap(const QPoint& point);

	void refresh(QPainter&);

private:
	QGraphicsPixmapItem* m_pixmap;
	QGraphicsScene* m_scene;
	QPoint m_topleft;

	bool m_isStartingCrop;
	bool m_isCroping;
};

#endif // CVIMAGEVIEW_H
