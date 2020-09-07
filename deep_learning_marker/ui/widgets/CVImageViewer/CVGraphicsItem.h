#ifndef CVGRAPHICSITEM_H
#define CVGRAPHICSITEM_H

//#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneEvent>

class CVGraphicsItem : public QGraphicsPixmapItem
{
public:
	CVGraphicsItem();
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:

private:
	QColor m_brushColor;
};

#endif // CVGRAPHICSITEM_H
