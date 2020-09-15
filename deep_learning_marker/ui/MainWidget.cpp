#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ui/widgets/MousePositionWidget.h"
#include "ui/widgets/CVImageViewer/CVGraphicsView.h"
#include "ui/widgets/OptionsButtonBar.h"
#include "ui/widgets/ParamList.h"

#include "controller/SignalCenter.h"
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"
#include "model/ParamListModel.h"

#include <QModelIndex>
#include <QKeyEvent>

MainWidget::MainWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MainWidget),
	m_buttonBar(nullptr),
	m_image(nullptr),
	m_list(nullptr),
	m_mousePos(nullptr)
{
	ui->setupUi(this);

	connect(SignalCenter::instance(), SIGNAL(displayImage(QString)), this, SLOT(handleDisplayImage(QString)));
	connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleSelectPara(QModelIndex)));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::handleDisplayImage(QString absolutePath)
{
	ui->graphicsView->loadImage(absolutePath);
}

void MainWidget::handleSelectPara(const QModelIndex& index)
{
	changePenColor(index);
	changeCurrentPara(index);
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_D:
		if (ImageModel::instance()->currentImage == ImageModel::instance()->imageArchive.end() - 1)
		{
			ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.begin();
			ui->graphicsView->loadImage(*ImageModel::instance()->currentImage);
		}
		else
		{
			++ImageModel::instance()->currentImage;
			ui->graphicsView->loadImage(*ImageModel::instance()->currentImage);
		}
		break;

	case Qt::Key_A:
		if (ImageModel::instance()->currentImage == ImageModel::instance()->imageArchive.begin())
		{
			ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.end() - 1;
			ui->graphicsView->loadImage(*ImageModel::instance()->currentImage);
		}
		else
		{
			--ImageModel::instance()->currentImage;
			ui->graphicsView->loadImage(*ImageModel::instance()->currentImage);
		}
		break;
	case Qt::Key_W:
		break;
	case Qt::Key_S:
		break;
	default:
		break;
	}
}

void MainWidget::changePenColor(const QModelIndex& index)
{
	QPen t_pen(RoiRectModel::instance()->colourPen[index.row()]);
	t_pen.setWidth(3);

	RoiRectModel::instance()->suit.pen = t_pen;
}

void MainWidget::changeCurrentPara(const QModelIndex& index)
{
	RoiRectModel::instance()->roiItem.paraName = ParamListModel::instance()->paramNameList[index.row()];
}