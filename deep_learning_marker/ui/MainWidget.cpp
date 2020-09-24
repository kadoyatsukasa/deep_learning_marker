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

	ui->listView->changeCurrentRow(0);
	initWidget();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::initWidget()
{
	for (int i = 0; i < ui->listView->count(); i++)
	{
		ui->listView->item(i)->setForeground(QColor(RoiRectModel::instance()->colourPen[i]));
		ui->listView->item(i)->setBackground(Qt::transparent);
	}
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

	initWidget();
	ui->listView->changeCurrentRow(index.row());
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_D:
		if (ImageModel::instance()->currentImage == ImageModel::instance()->imageArchive.end() - 1)
		{
			ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.begin();
			ImageModel::instance()->imageFilePathName = ImageModel::instance()->currentImage->filePath();
			ImageModel::instance()->imageFilePath = ImageModel::instance()->currentImage->path();
			ImageModel::instance()->imageFileName = ImageModel::instance()->currentImage->baseName();
			if (FileUtil::instance()->fileIsExsit())
				FileUtil::instance()->readFromConfigFile();
			ui->graphicsView->loadImage(ImageModel::instance()->currentImage->filePath());
		}
		else
		{
			++ImageModel::instance()->currentImage;
			ImageModel::instance()->imageFilePathName = ImageModel::instance()->currentImage->filePath();
			ImageModel::instance()->imageFilePath = ImageModel::instance()->currentImage->path();
			ImageModel::instance()->imageFileName = ImageModel::instance()->currentImage->baseName();
			if (FileUtil::instance()->fileIsExsit())
				FileUtil::instance()->readFromConfigFile();
			ui->graphicsView->loadImage(ImageModel::instance()->currentImage->filePath());
		}
		break;

	case Qt::Key_A:
		if (ImageModel::instance()->currentImage == ImageModel::instance()->imageArchive.begin())
		{
			ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.end() - 1;
			ImageModel::instance()->imageFilePathName = ImageModel::instance()->currentImage->filePath();
			ImageModel::instance()->imageFilePath = ImageModel::instance()->currentImage->path();
			ImageModel::instance()->imageFileName = ImageModel::instance()->currentImage->baseName();
			if (FileUtil::instance()->fileIsExsit())
				FileUtil::instance()->readFromConfigFile();
			ui->graphicsView->loadImage(ImageModel::instance()->currentImage->filePath());
		}
		else
		{
			--ImageModel::instance()->currentImage;
			ImageModel::instance()->imageFilePathName = ImageModel::instance()->currentImage->filePath();
			ImageModel::instance()->imageFilePath = ImageModel::instance()->currentImage->path();
			ImageModel::instance()->imageFileName = ImageModel::instance()->currentImage->baseName();
			if (FileUtil::instance()->fileIsExsit())
				FileUtil::instance()->readFromConfigFile();
			ui->graphicsView->loadImage(ImageModel::instance()->currentImage->filePath());
		}
		break;
	case Qt::Key_W:
		--m_currentRow;
		if (m_currentRow < 0)
			m_currentRow = ui->listView->count() - 1;
		qDebug() << m_currentRow;
		initWidget();
		emit SignalCenter::instance()->goFore(m_currentRow);
		break;
	case Qt::Key_S:
		++m_currentRow;
		if (m_currentRow == ui->listView->count())
			m_currentRow = 0;
		qDebug() << m_currentRow;
		initWidget();
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