#include "CVGraphicsView.h"
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"
#include "model/ParamListModel.h"
#include "controller/SignalCenter.h"
#include "utils/FileUtil.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QModelIndex>

CVGraphicsView::CVGraphicsView(QWidget* parent) :
	QGraphicsView(parent),
	m_pixmap(nullptr),
	m_scene(nullptr)
{
	init();

	connect(SignalCenter::instance(), SIGNAL(clearAllMarks()), this, SLOT(clearAllMarks()));
}
void CVGraphicsView::paintEvent(QPaintEvent* event)
{
	QGraphicsView::paintEvent(event);
	if (ImageModel::instance()->targetImage.isNull())
	{
		return;
	}

	m_imgCanvas = new QPainter(viewport());
	QPixmap img;
	img = m_pixmap->pixmap();
	m_imgCanvas->drawPixmap(QRect(0, 0, viewport()->width(), viewport()->height()), img);
	m_roiCanvas = new QPainter(viewport());

	QSize rectSize = event->rect().size();
	ImageModel::instance()->scalingFactory = 1.0 * rectSize.width() / m_pixmap->pixmap().width();
	m_pixmap->pixmap().size().scale(m_pixmap->pixmap().size() * ImageModel::instance()->scalingFactory, Qt::KeepAspectRatio);

	m_topleft.setX((viewport()->width() - m_pixmap->pixmap().width()) / 2);
	m_topleft.setY((viewport()->height() - m_pixmap->pixmap().height()) / 2);

	if (FileUtil::instance()->fileIsExsit())
	{
		drawFromFile(m_roiCanvas);
	}
	else
	{
		drawFirst(m_roiCanvas);
	}
}

void CVGraphicsView::mousePressEvent(QMouseEvent* event)
{
	QGraphicsView::mousePressEvent(event);
	if ((event->buttons() == Qt::LeftButton) /*&& (isContainPoint(event->pos()))*/)
	{
		RoiRectModel::instance()->startPoint = mapToPixmap(event->pos());
		m_isStartingCrop = true;

		emit SignalCenter::instance()->displayRoiStartPoint(RoiRectModel::instance()->startPoint);
	}
}

void CVGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	QGraphicsView::mouseMoveEvent(event);

	if ((event->buttons() == Qt::LeftButton) && m_isStartingCrop)
	{
		if (isContainPoint(event->pos()))
		{
			RoiRectModel::instance()->endPoint = mapToPixmap(event->pos());
		}
	}

	emit SignalCenter::instance()->displayCurrentMousePoint(event->pos());

	viewport()->update();
}

void CVGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	QGraphicsView::mouseReleaseEvent(event);
	QRect rect(RoiRectModel::instance()->startPoint, RoiRectModel::instance()->endPoint);
	m_isStartingCrop = false;

	RoiRectModel::instance()->roiStartPoints.push_back(RoiRectModel::instance()->startPoint);
	RoiRectModel::instance()->roiEndPoints.push_back(RoiRectModel::instance()->endPoint);
	RoiRectModel::instance()->roiRects.push_back(rect);

	RoiRectModel::instance()->roiItem.regions.push_back(RoiRectModel::instance()->suit);
	RoiRectModel::instance()->regionCase.push_back(RoiRectModel::instance()->roiItem);

	emit SignalCenter::instance()->displayRoiEndPoint(RoiRectModel::instance()->endPoint);
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

	m_topleft.setX((viewport()->width() - pixSize.width()) / 2);
	m_topleft.setY((viewport()->height() - pixSize.height()) / 2);

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
		m_topleft.setX((viewport()->width() - pixSize.width()) / 2);
		m_topleft.setY((viewport()->height() - pixSize.height()) / 2);
		pos.setX(point.x() - m_topleft.x());
		pos.setY(point.y() - m_topleft.y());
	}
	QPoint result;
	result = QPoint(pos.x() / (ImageModel::instance()->scalingFactory), pos.y() / (ImageModel::instance()->scalingFactory));
	return result;
}

void CVGraphicsView::loadImage(QString absolutePath)
{
	clearAllMarks();
	RoiRectModel::instance()->dataReset();

	ImageModel::instance()->srcImage = cv::imread(absolutePath.toStdString().c_str());

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

	if (RoiRectModel::instance()->dataExsits())
	{
		RoiRectModel::instance()->dataReset();
	}

	m_pixmap->setPixmap(QPixmap::fromImage(ImageModel::instance()->targetImage).scaled(viewport()->width(), viewport()->height(), Qt::KeepAspectRatio));
	m_scene->addItem(m_pixmap);
}

void CVGraphicsView::refresh(QPainter* painter)
{
	for each (REGION_CASE t_caseItem in RoiRectModel::instance()->regionCase)
	{
		for each (PEN_CASE t_roiItem in t_caseItem.regions)
		{
			t_roiItem.crayon.setWidth(3);
			painter->setPen(t_roiItem.crayon);
			painter->drawRect(t_roiItem.rect);
		}
	}
}

void CVGraphicsView::clearAllMarks()
{
	RoiRectModel::instance()->dataReset();

	viewport()->repaint();
}

void CVGraphicsView::drawFirst(QPainter* painter)
{
	QRect t_rect;
	if (RoiRectModel::instance()->startPoint.x() < RoiRectModel::instance()->endPoint.x())
	{
		if (RoiRectModel::instance()->startPoint.y() < RoiRectModel::instance()->endPoint.y())
		{
			RoiRectModel::instance()->suit.rect = QRect(
				m_topleft.x() + RoiRectModel::instance()->startPoint.x() * ImageModel::instance()->scalingFactory,
				m_topleft.y() + RoiRectModel::instance()->startPoint.y() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory);
		}
		else
		{
			RoiRectModel::instance()->suit.rect = QRect(
				m_topleft.x() + RoiRectModel::instance()->startPoint.x() * ImageModel::instance()->scalingFactory,
				m_topleft.y() + RoiRectModel::instance()->endPoint.y() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
			);
		}
	}
	else
	{
		if (RoiRectModel::instance()->startPoint.y() > RoiRectModel::instance()->endPoint.y())
		{
			RoiRectModel::instance()->suit.rect = QRect(
				m_topleft.x() + RoiRectModel::instance()->endPoint.x() * ImageModel::instance()->scalingFactory,
				m_topleft.y() + RoiRectModel::instance()->endPoint.y() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
			);
		}
		else
		{
			RoiRectModel::instance()->suit.rect = QRect(
				m_topleft.x() + RoiRectModel::instance()->endPoint.x() * ImageModel::instance()->scalingFactory,
				m_topleft.y() + RoiRectModel::instance()->startPoint.y() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
				RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
			);
		}
	}

	painter->setPen(RoiRectModel::instance()->suit.crayon);
	painter->drawRect(RoiRectModel::instance()->suit.rect);

	refresh(painter);
}

void CVGraphicsView::drawFromFile(QPainter* painter)
{
	FileUtil::instance()->readFromConfigFile();
	refresh(painter);
}