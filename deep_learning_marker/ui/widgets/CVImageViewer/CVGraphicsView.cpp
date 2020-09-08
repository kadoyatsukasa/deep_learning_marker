#include "CVGraphicsView.h"
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

CVGraphicsView::CVGraphicsView(QWidget* parent) :
	QGraphicsView(parent),
	m_pixmap(nullptr),
	m_scene(nullptr)
{
	init();
}
void CVGraphicsView::paintEvent(QPaintEvent* event)
{
	QGraphicsView::paintEvent(event);
	if (ImageModel::instance()->targetImage.isNull())
	{
		return;
	}

	QPainter painter(viewport());
	qDebug() << "****************QGraphicsView::paintEvent() active ***********************************";

	QPixmap img;
	img = m_pixmap->pixmap();
	painter.drawPixmap(QRect(0, 0, width(), height()), img);

	QSize rectSize = event->rect().size();
	ImageModel::instance()->scalingFactory = 1.0 * rectSize.width() / m_pixmap->pixmap().size().width();

	m_topleft.setX((viewport()->width() - m_pixmap->pixmap().width()) / 2);
	m_topleft.setY((viewport()->height() - m_pixmap->pixmap().height()) / 2);

	qDebug() << m_topleft;
	qDebug() << ImageModel::instance()->scalingFactory;

	if (m_isStartingCrop)
	{
		qDebug() << RoiRectModel::instance()->width() << '\t' << RoiRectModel::instance()->height();
		QPainter t_painter(viewport());
		QPen pen;
		pen.setBrush(Qt::red);
		pen.setWidth(1.5);
		t_painter.setPen(pen);

		if (RoiRectModel::instance()->start.x() < RoiRectModel::instance()->end.x())
		{
			if (RoiRectModel::instance()->start.y() < RoiRectModel::instance()->end.y())
			{
				t_painter.drawRect(
					m_topleft.x() + RoiRectModel::instance()->start.x() * ImageModel::instance()->scalingFactory,
					m_topleft.y() + RoiRectModel::instance()->start.y() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
				);
			}
			else
			{
				t_painter.drawRect(
					m_topleft.x() + RoiRectModel::instance()->start.x() * ImageModel::instance()->scalingFactory,
					m_topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
				);
			}
		}
		else
		{
			if (RoiRectModel::instance()->start.y() > RoiRectModel::instance()->end.y())
			{
				t_painter.drawRect(
					m_topleft.x() + RoiRectModel::instance()->end.x() * ImageModel::instance()->scalingFactory,
					m_topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
				);
			}
			else
			{
				t_painter.drawRect(
					m_topleft.x() + RoiRectModel::instance()->end.x() * ImageModel::instance()->scalingFactory,
					m_topleft.y() + RoiRectModel::instance()->start.y() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
					RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
				);
			}
		}
	}
}

void CVGraphicsView::mousePressEvent(QMouseEvent* event)
{
	QGraphicsView::mousePressEvent(event);
	qDebug() << "****************QGraphicsView::mousePressEvent() active ***********************************";
	if ((event->buttons() == Qt::LeftButton) /*&& (isContainPoint(event->pos()))*/)
	{
		RoiRectModel::instance()->start = mapToPixmap(event->pos());
		RoiRectModel::instance()->end = mapToPixmap(event->pos());
		m_isStartingCrop = true;

		qDebug() << RoiRectModel::instance()->start << '\t' << RoiRectModel::instance()->end;
	}
}

void CVGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	QGraphicsView::mouseMoveEvent(event);
	qDebug() << "****************QGraphicsView::mouseMoveEvent() active ***********************************";

	QPixmap temp = m_pixmap->pixmap();
	QPainter t_painter(&temp);

	t_painter.setBrush(Qt::red);

	if ((event->buttons() == Qt::LeftButton) && m_isStartingCrop)
	{
		if (isContainPoint(event->pos()))
		{
			RoiRectModel::instance()->end = mapToPixmap(event->pos());
			qDebug() << RoiRectModel::instance()->end;
		}
	}

	viewport()->update();
}

void CVGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	QGraphicsView::mouseReleaseEvent(event);
	qDebug() << "****************QGraphicsView::mouseReleaseEvent() active ***********************************";
	QRect rect(RoiRectModel::instance()->start, RoiRectModel::instance()->end);
	m_isStartingCrop = false;
}

void CVGraphicsView::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);

	resize(frameGeometry().size());
	scene()->setSceneRect(0, 0, frameGeometry().width(), frameGeometry().height());
}

void CVGraphicsView::init()
{
	m_scene = new QGraphicsScene(this);
	m_pixmap = new QGraphicsPixmapItem();
	setScene(m_scene);
}

bool CVGraphicsView::isContainPoint(const QPoint& point)
{
	QSize pixSize = m_pixmap->pixmap().size();
	pixSize.scale(ImageModel::instance()->scalingFactory * pixSize, Qt::KeepAspectRatio);

	if ((pixSize.height() > viewport()->rect().height()) &&
		(pixSize.width() > viewport()->rect().width()))
	{
		return true;
	}

	QPoint topleft;
	topleft.setX((viewport()->width() - pixSize.width()) / 2);
	topleft.setY((viewport()->height() - pixSize.height()) / 2);

	qDebug() << topleft;

	QRect rect(m_topleft, pixSize);
	return rect.contains(point);
}

QPoint CVGraphicsView::mapToPixmap(const QPoint& point)
{
	QSize pixSize = m_pixmap->pixmap().size();
	QPoint pos;
	pixSize.scale(ImageModel::instance()->scalingFactory * pixSize, Qt::KeepAspectRatio);

	if (pixSize.width() > viewport()->width() && pixSize.height() > viewport()->height())
	{
		pos.setX(pixSize.width() - (viewport()->width() - point.x()));
		pos.setY(pixSize.height() - (viewport()->height() - point.y()));
	}
	else if (pixSize.width() < viewport()->width() && pixSize.height() > viewport()->height())
	{
		pos.setX(point.x() - (viewport()->width() - pixSize.width()) / 2);
		pos.setY(pixSize.height() - (viewport()->height() - point.y()));
	}
	else if (pixSize.width() > viewport()->width() && pixSize.height() < viewport()->height())
	{
		pos.setX(pixSize.width() - (viewport()->width() - point.x()));
		pos.setY(point.y() - (viewport()->height() - pixSize.height()) / 2);
	}
	else
	{
		QPoint topleft;
		topleft.setX((viewport()->width() - pixSize.width()) / 2);
		topleft.setY((viewport()->height() - pixSize.height()) / 2);
		pos.setX(point.x() - m_topleft.x());
		pos.setY(point.y() - m_topleft.y());

		qDebug() << topleft;
		qDebug() << pos;
	}
	QPoint result;
	result = QPoint(pos.x() / (ImageModel::instance()->scalingFactory), pos.y() / (ImageModel::instance()->scalingFactory));
	return result;
}

void CVGraphicsView::loadImage(const char* imagePath)
{
	ImageModel::instance()->srcImage = cv::imread(imagePath);

	if (ImageModel::instance()->srcImage.empty())
		return;

	cv::cvtColor(ImageModel::instance()->srcImage, ImageModel::instance()->rgbImage, CV_BGR2RGB);

	ImageModel::instance()->targetImage =
		QImage(
			static_cast<const unsigned char*>(ImageModel::instance()->rgbImage.data),
			ImageModel::instance()->rgbImage.cols,
			ImageModel::instance()->rgbImage.rows,
			ImageModel::instance()->rgbImage.step,
			QImage::Format_RGB888
		);
	m_pixmap->setPixmap(QPixmap::fromImage(ImageModel::instance()->targetImage).scaled(viewport()->width(), viewport()->height(), Qt::KeepAspectRatio));
	m_scene->addItem(m_pixmap);
}