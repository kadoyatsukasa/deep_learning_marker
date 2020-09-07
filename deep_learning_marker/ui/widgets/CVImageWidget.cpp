#include "CVGraphicsView.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "model/ImageModel.h"
#include "model/RoiRectModel.h"

CVGraphicsView::CVGraphicsView(QWidget* parent) :
	QGraphicsView(parent),
	m_view(nullptr),
	m_scene(nullptr),
	m_pixmapItem(nullptr)
{
	init();
}

CVGraphicsView::~CVGraphicsView()
{
}

/**
 * override QGraphicsView events
 */

void CVGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
}

void CVGraphicsView::mousePressEvent(QMouseEvent* event)
{
}

void CVGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
}

void CVGraphicsView::resizeEvent(QResizeEvent* event)
{
	m_view->resize(frameGeometry().size());
	m_view->scene()->setSceneRect(0, 0, frameGeometry().width(), frameGeometry().height());
	m_scalingFactory = m_view->scene()->width() / m_pixmapItem->pixmap().width();
}

/**
 * Public Functions
 */

bool CVGraphicsView::loadImage(const char* imageName)
{
	ImageModel::instance()->srcImage = cv::imread(imageName);
	if (ImageModel::instance()->srcImage.empty())
	{
		return false;
	}

	cv::cvtColor(ImageModel::instance()->srcImage, ImageModel::instance()->rgbImage, CV_BGR2RGB);
	ImageModel::instance()->targetImage =
		QImage(
			(const unsigned char*)(ImageModel::instance()->rgbImage.data),
			ImageModel::instance()->rgbImage.cols,
			ImageModel::instance()->rgbImage.rows,
			ImageModel::instance()->rgbImage.step,
			QImage::Format_RGB888
		);

	m_pixmapItem->setPixmap(QPixmap::fromImage(ImageModel::instance()->targetImage).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
	m_scene->addItem(m_pixmapItem);

	return true;
}

/**
 * Private Functions
 */

void CVGraphicsView::init()
{
	m_view = new QGraphicsView(this);
	m_scene = new QGraphicsScene(this);
	m_pixmapItem = new QGraphicsPixmapItem();

	m_view->setScene(m_scene);
}

bool CVGraphicsView::isContainPoint(QPoint& point)
{
	QSize size = m_pixmapItem->pixmap().size();
	size.scale(m_scalingFactory * size, Qt::KeepAspectRatio);

	if ((size.height() > m_view->height()) && (size.width() > m_view->width()))
	{
		return true;
	}

	QPoint topleft;
	topleft.setX((m_view->scene()->width() - size.width()) / 2);
	topleft.setY((m_view->scene()->height() - size.height()) / 2);

	QRect rect(topleft, size);
	return rect.contains(point);
}