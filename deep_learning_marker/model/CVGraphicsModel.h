#ifndef CVGRAPHICSMODEL_H
#define CVGRAPHICSMODEL_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class CVGraphicsModel
{
public:
	static CVGraphicsModel* instance();

	qreal sceneWidth;
	qreal sceneHeight;

	QSize pixmapSize;
	int pixmapWidth;
	int pixmapHeight;

	int viewWidth;
	int viewHeight;

	QPen crayon;
private:
	CVGraphicsModel();
};

#endif // CVGRAPHICSMODEL_H
