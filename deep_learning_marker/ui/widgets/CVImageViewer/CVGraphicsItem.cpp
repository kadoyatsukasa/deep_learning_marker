#include "CVGraphicsItem.h"
#include "model/RoiRectModel.h"
#include "model/ImageModel.h"
#include "model/CVGraphicsModel.h"

#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <opencv2/opencv.hpp>

CVGraphicsItem::CVGraphicsItem() :
	m_brushColor(Qt::red)
{
	setFlag(QGraphicsPixmapItem::ItemIsFocusable);
}

void CVGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "****************QGraphicsPixmapItem::mouseMoveEvent() active ***********************************";

	QGraphicsPixmapItem::mouseMoveEvent(event);
}

void CVGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "****************QGraphicsPixmapItem::mousePressEvent() active ***********************************";
	QGraphicsPixmapItem::mousePressEvent(event);
}

//void CVGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
//{
//	qDebug() << "****************paint() active ***********************************";
//	if (hasFocus())
//		painter->setPen(QPen(Qt::green));
//	else
//		painter->setPen(QPen(Qt::blue));
//	painter->setBrush(m_brushColor);
//
//	setPixmap(QPixmap::fromImage(ImageModel::instance()->targetImage).scaled(CVGraphicsModel::instance()->viewWidth, CVGraphicsModel::instance()->viewHeight, Qt::KeepAspectRatio));
//}