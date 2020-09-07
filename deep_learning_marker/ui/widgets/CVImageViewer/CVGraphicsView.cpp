#include "CVGraphicsView.h"
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"
#include "model/CVGraphicsModel.h"
#include <QDebug>

CVGraphicsView::CVGraphicsView(QWidget* parent) :
	QGraphicsView(parent),
	m_pixmap(nullptr),
	m_scene(nullptr)
{
	init();
}
//void CVGraphicsView::paintEvent(QPaintEvent* event)
//{
//	qDebug() << "****************QGraphicsView::paintEvent() active ***********************************";
//	QGraphicsView::paintEvent(event);
//}

void CVGraphicsView::mousePressEvent(QMouseEvent* event)
{
	QGraphicsView::mousePressEvent(event);
	qDebug() << "****************QGraphicsView::mousePressEvent() active ***********************************";
	if ((event->buttons() == Qt::LeftButton) && (isContainPoint(event->pos())))
	{
		RoiRectModel::instance()->start = mapToPixmap(event->pos());
		m_isStartingCrop = true;
	}
}

void CVGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	QGraphicsView::mouseMoveEvent(event);
	qDebug() << "****************QGraphicsView::mouseMoveEvent() active ***********************************";

	QPainter painter(this);
	QPoint topleft;

	topleft.setX((CVGraphicsModel::instance()->sceneWidth - CVGraphicsModel::instance()->pixmapSize.width()) / 2);
	topleft.setY((CVGraphicsModel::instance()->sceneHeight - CVGraphicsModel::instance()->pixmapSize.height()) / 2);
	QPen pen;
	pen.setBrush(Qt::red);
	pen.setStyle(Qt::DashLine);
	pen.setWidth(1);
	painter.setPen(pen);
	//        qDebug() << RoiRectModel::instance()->width() << RoiRectModel::instance()->height();

	if ((event->buttons() == Qt::LeftButton) && m_isStartingCrop)
	{
		//            qDebug() << event->pos().x() << event->pos().y();
		if (isContainPoint(event->pos()))
		{
			RoiRectModel::instance()->end = mapToPixmap(event->pos());

			if (RoiRectModel::instance()->start.x() < RoiRectModel::instance()->end.x())
			{
				if (RoiRectModel::instance()->start.y() < RoiRectModel::instance()->end.y())
				{
					painter.drawRect(
						topleft.x() + RoiRectModel::instance()->start.x() * ImageModel::instance()->scalingFactory,
						topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
					);
				}
				else
				{
					painter.drawRect(
						topleft.x() + RoiRectModel::instance()->start.x() * ImageModel::instance()->scalingFactory,
						topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
					);
				}
			}
			else
			{
				if (RoiRectModel::instance()->start.y() > RoiRectModel::instance()->end.y())
				{
					painter.drawRect(
						topleft.x() + RoiRectModel::instance()->end.x() * ImageModel::instance()->scalingFactory,
						topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
					);
				}
				else
				{
					painter.drawRect(
						topleft.x() + RoiRectModel::instance()->end.x() * ImageModel::instance()->scalingFactory,
						topleft.y() + RoiRectModel::instance()->end.y() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->width() * ImageModel::instance()->scalingFactory,
						RoiRectModel::instance()->height() * ImageModel::instance()->scalingFactory
					);
				}
			}
			update();
		}
	}
}

void CVGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
	RoiRectModel::instance()->end = mapToPixmap(event->pos());
	QRect rect(RoiRectModel::instance()->start, RoiRectModel::instance()->end);
	m_isStartingCrop = false;
}

void CVGraphicsView::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event);

	CVGraphicsModel::instance()->sceneWidth = scene()->width();
	CVGraphicsModel::instance()->sceneHeight = scene()->height();
	CVGraphicsModel::instance()->viewWidth = width();
	CVGraphicsModel::instance()->viewHeight = height();

	CVGraphicsModel::instance()->pixmapSize = m_pixmap->pixmap().size();

	resize(frameGeometry().size());
	scene()->setSceneRect(0, 0, frameGeometry().width(), frameGeometry().height());
	ImageModel::instance()->scalingFactory = CVGraphicsModel::instance()->sceneWidth / CVGraphicsModel::instance()->pixmapSize.width();
}

void CVGraphicsView::init()
{
	m_scene = new CVGraphicsScene(this);
	m_pixmap = new CVGraphicsItem();
	setScene(m_scene);


}

bool CVGraphicsView::isContainPoint(const QPoint& point)
{
	//QSize size = m_pixmap->pixmap().size();
	CVGraphicsModel::instance()->pixmapSize.scale(ImageModel::instance()->scalingFactory * CVGraphicsModel::instance()->pixmapSize, Qt::KeepAspectRatio);

	if ((CVGraphicsModel::instance()->pixmapSize.height() > height()) && (CVGraphicsModel::instance()->pixmapSize.width() > width()))
	{
		return true;
	}

	QPoint topleft;
	topleft.setX((CVGraphicsModel::instance()->sceneWidth - CVGraphicsModel::instance()->pixmapSize.width()) / 2);
	topleft.setY((CVGraphicsModel::instance()->sceneHeight - CVGraphicsModel::instance()->pixmapSize.height()) / 2);

	QRect rect(topleft, CVGraphicsModel::instance()->pixmapSize);
	return rect.contains(point);
}

QPoint CVGraphicsView::mapToPixmap(const QPoint& point)
{
	//QSize size = m_pixmap->pixmap().size();
	QPoint pos;
	CVGraphicsModel::instance()->pixmapSize.scale(ImageModel::instance()->scalingFactory * CVGraphicsModel::instance()->pixmapSize, Qt::KeepAspectRatio);

	if (CVGraphicsModel::instance()->pixmapSize.width() > CVGraphicsModel::instance()->sceneWidth && CVGraphicsModel::instance()->pixmapSize.height() > CVGraphicsModel::instance()->sceneHeight)
	{
		pos.setX(CVGraphicsModel::instance()->pixmapSize.width() - (CVGraphicsModel::instance()->sceneWidth - point.x()));
		pos.setY(CVGraphicsModel::instance()->pixmapSize.height() - (CVGraphicsModel::instance()->sceneHeight - point.y()));
	}
	else if (CVGraphicsModel::instance()->pixmapSize.width() < CVGraphicsModel::instance()->sceneWidth && CVGraphicsModel::instance()->pixmapSize.height() > CVGraphicsModel::instance()->sceneHeight)
	{
		pos.setX(point.x() - (CVGraphicsModel::instance()->sceneWidth - CVGraphicsModel::instance()->pixmapSize.width()) / 2);
		pos.setY(CVGraphicsModel::instance()->pixmapSize.height() - (CVGraphicsModel::instance()->sceneHeight - point.y()));
	}
	else if (CVGraphicsModel::instance()->pixmapSize.width() > CVGraphicsModel::instance()->sceneWidth && CVGraphicsModel::instance()->pixmapSize.height() < CVGraphicsModel::instance()->sceneHeight)
	{
		pos.setX(CVGraphicsModel::instance()->pixmapSize.width() - (CVGraphicsModel::instance()->sceneWidth - point.x()));
		pos.setY(point.y() - (CVGraphicsModel::instance()->sceneHeight - CVGraphicsModel::instance()->pixmapSize.height()) / 2);
	}
	else
	{
		QPoint topleft;
		topleft.setX((CVGraphicsModel::instance()->sceneWidth - CVGraphicsModel::instance()->pixmapSize.width()) / 2);
		topleft.setY((CVGraphicsModel::instance()->sceneHeight - CVGraphicsModel::instance()->pixmapSize.height()) / 2);
		pos.setX(point.x() - topleft.x());
		pos.setY(point.y() - topleft.y());
	}

	return QPoint(pos.x() / (ImageModel::instance()->scalingFactory), pos.y() / (ImageModel::instance()->scalingFactory));
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

	m_pixmap->setPixmap(QPixmap::fromImage(ImageModel::instance()->targetImage).scaled(CVGraphicsModel::instance()->viewWidth, CVGraphicsModel::instance()->viewHeight, Qt::KeepAspectRatio));
	m_scene->addItem(m_pixmap);
}