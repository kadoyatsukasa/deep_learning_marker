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
#include "utils/FileUtil.h"

#include <QModelIndex>
#include <QKeyEvent>
#include <QListView>
#include <QDebug>

MainWidget::MainWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MainWidget),
	m_currentRow(0)
{
	ui->setupUi(this);

	connect(SignalCenter::instance(), SIGNAL(displayImage(QString)), this, SLOT(handleDisplayImage(QString)));
	connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleSelectPara(QModelIndex)));

	ui->listView->setFocus();
	ui->listView->setCurrentRow(0);
	m_currentRow = ui->listView->currentRow();

	for (int i = 0; i < ui->listView->count(); i++)
	{
		ui->listView->item(i)->setForeground(QColor(RoiRectModel::instance()->colourPen[i]));
	}
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
	QPen t_pen(RoiRectModel::instance()->colourPen[index.row()]);
	t_pen.setWidth(3);
	RoiRectModel::instance()->suit.crayon = t_pen;
	RoiRectModel::instance()->roiItem.paraName = ParamListModel::instance()->paramNameList[index.row()];
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
		--m_currentRow;
		qDebug() << m_currentRow;
		emit SignalCenter::instance()->goFore(m_currentRow);
		break;
	case Qt::Key_S:
		++m_currentRow;
		qDebug() << m_currentRow;
		emit SignalCenter::instance()->goNext(m_currentRow);

		break;
	case Qt::Key_E:
		FileUtil::instance()->saveToConfigFile();
		break;
	case Qt::Key_C:
		ui->graphicsView->clearAllMarks();
		break;
	default:
		break;
	}
}