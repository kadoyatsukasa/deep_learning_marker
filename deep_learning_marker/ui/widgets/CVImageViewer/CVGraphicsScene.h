#ifndef CVGRAPHICSSCENE_H
#define CVGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>

class CVGraphicsItem;

class CVGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
	CVGraphicsScene(QObject* parent = 0);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
	CVGraphicsItem* m_pixmap;
};

#endif // CVGRAPHICSSCENE_H
