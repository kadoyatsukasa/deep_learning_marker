#include "CVGraphicsScene.h"
#include "CVGraphicsItem.h"
#include "model/ImageModel.h"
#include <QDebug>
CVGraphicsScene::CVGraphicsScene(QObject* parent) :
	QGraphicsScene(parent)
{
	clearFocus();
}

void CVGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "****************QGraphicsScene::mousePressEvent() active ***********************************";
	return QGraphicsScene::mousePressEvent(event);
}

void CVGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "****************QGraphicsPixmapItem::mouseMoveEvent() active ***********************************";
	QGraphicsScene::mouseMoveEvent(event);
}