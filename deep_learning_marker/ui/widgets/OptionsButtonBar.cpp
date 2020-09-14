#include "OptionsButtonBar.h"
#include "ui_OptionsButtonBar.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"
#include "controller/SignalCenter.h"

OptionsButtonBar::OptionsButtonBar(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::OptionsButtonBar)
{
	ui->setupUi(this);
	connect(ui->btnLoadImage, SIGNAL(clicked()), this, SLOT(handleLoadSingleImage()));
	connect(ui->btnClearAll, SIGNAL(clicked()), this, SLOT(handleClearAllMarks()));
	connect(ui->btnSaveMarks, SIGNAL(clicked()), this, SLOT(handleSaveAllPositions()));
	connect(ui->btnLoadArchive, SIGNAL(clicked()), this, SLOT(handleLoadArchive()));
}

OptionsButtonBar::~OptionsButtonBar()
{
	delete ui;
}

void OptionsButtonBar::handleLoadSingleImage()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Select image"), ".", tr("Image Files(*.png *.jpg *.bmp *.jpeg)"));

	QFileInfo info(filename);

	if (filename.isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("You haven't chosen any image yet"));
	}
	else
	{
		ImageModel::instance()->imageFilePathName = filename;
		ImageModel::instance()->imageFilePath = info.absolutePath();
		ImageModel::instance()->imageFileName = info.baseName();

		emit SignalCenter::instance()->displayImage(ImageModel::instance()->imageFilePathName);

		qDebug() << info.absolutePath();
		qDebug() << info.fileName();
		qDebug() << info.baseName();
	}
}

void OptionsButtonBar::handleLoadArchive()
{
	QString filepath = QFileDialog::getExistingDirectory(this, QStringLiteral("Ñ¡ÔñÎÄ¼þ¼Ð"), "./");
	if (filepath.isEmpty())
	{
		return;
	}
	QDir dir(filepath);
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Size | QDir::Reversed);
	QFileInfoList fileInformation = dir.entryInfoList();

	for (int i = 0; i < fileInformation.size(); ++i)
	{
		QFileInfo info = fileInformation.at(i);
		ImageModel::instance()->imageArchive.push_back(info.absoluteFilePath());
		qDebug() << ImageModel::instance()->imageArchive[i];
	}
	ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.begin();
	emit SignalCenter::instance()->displayImage(ImageModel::instance()->imageArchive[0]);
}

void OptionsButtonBar::handleSaveAllPositions()
{
	QFile file(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	QTextStream out(&file);

	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		for (int i = 0, j = 0, k = 0;
			i < RoiRectModel::instance()->roiStartPoints.size(),
			j < RoiRectModel::instance()->roiEndPoints.size(),
			k < RoiRectModel::instance()->roiRects.size();
			i++, j++, k++)
		{
			out << "[ROI]" << '\n';

			out << "startPoint:" << "(" <<
				RoiRectModel::instance()->roiStartPoints[i].x() << "," <<
				RoiRectModel::instance()->roiStartPoints[i].y() << ")" << '\n';

			out << "endPoint:" << "(" <<
				RoiRectModel::instance()->roiEndPoints[j].x() << "," <<
				RoiRectModel::instance()->roiEndPoints[j].y() << ")" << '\n';

			out << "width = " << RoiRectModel::instance()->roiRects[k].width() << ","
				<< "height = " << RoiRectModel::instance()->roiRects[k].height() << '\n';
		}
	}
}

void OptionsButtonBar::handleClearAllMarks()
{
	emit SignalCenter::instance()->clearAllMarks();
}

void OptionsButtonBar::clearAllRects(std::vector<QRect> roiRects)
{
	roiRects.clear();
	//emit SignalCenter::instance()->clearAllRects(roiRects);
}

void OptionsButtonBar::clearAllStartPoints(std::vector<QPoint> startPoint)
{
	startPoint.clear();
	//emit SignalCenter::instance()->clearAllStartPoints(startPoint);
}

void OptionsButtonBar::clearAllEndPoints(std::vector<QPoint> endPoint)
{
	endPoint.clear();
	//emit SignalCenter::instance()->clearAllEndPoints(endPoint);
}