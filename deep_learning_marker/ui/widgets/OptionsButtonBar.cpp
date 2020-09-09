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

		emit SignalCenter::instance()->displayImage(ImageModel::instance()->imageFilePathName.toStdString().c_str());

		qDebug() << info.absolutePath();
		qDebug() << info.fileName();
		qDebug() << info.baseName();
	}
}

void OptionsButtonBar::handleSaveAllPositions()
{
//	//QSettings positions(ImageModel::instance()->imageFilePathName + ".ini", QSettings::IniFormat);
//
//	//saveAllStartPositions(positions, RoiRectModel::instance()->roiStartPoints);
//	//saveAllEndPositions(positions, RoiRectModel::instance()->roiEndPoints);
//	//saveAllRects(positions, RoiRectModel::instance()->roiRects);
//
//	//QMessageBox::information(this, tr(QStringLiteral("提示").toStdString().c_str()), tr(QStringLiteral("保存成功").toStdString().c_str()));

	QFile file(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	QTextStream out(&file);
	
	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		//saveAllStartPositions(file, RoiRectModel::instance()->roiStartPoints);
		//saveAllEndPositions(file, RoiRectModel::instance()->roiEndPoints);
		//saveAllRects(file, RoiRectModel::instance()->roiRects);

		for (int i = 0, j = 0, k = 0;
			i < RoiRectModel::instance()->roiStartPoints.size(), 
			j < RoiRectModel::instance()->roiEndPoints.size(), 
			k < RoiRectModel::instance()->roiRects.size();
			i++, j++, k++)
		{
			out << "[ROI]"<<'\n';

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

//void OptionsButtonBar::saveAllStartPositions(QSettings& setting, std::vector<QPoint> startPoints)
//{
//	setting.beginGroup("start-points");
//	std::vector<QPoint>::iterator pos;
//	for (pos = startPoints.begin(); pos != startPoints.end(); pos++)
//	{
//		setting.setValue("x", pos->x());
//		setting.setValue("y", pos->y());
//	}
//
//	setting.endGroup();
//}
//
//void OptionsButtonBar::saveAllEndPositions(QSettings& setting, std::vector<QPoint> endPoints)
//{
//	setting.beginGroup("end-points");
//	std::vector<QPoint>::iterator pos;
//	for (pos = endPoints.begin(); pos != endPoints.end(); pos++)
//	{
//		setting.setValue("x", pos->x());
//		setting.setValue("y", pos->y());
//	}
//	setting.endGroup();
//}
//
//void OptionsButtonBar::saveAllRects(QSettings& setting, std::vector<QRect> roiRects)
//{
//	setting.beginGroup("roi-rect");
//	std::vector<QRect>::iterator roi;
//
//	for (roi = roiRects.begin(); roi != roiRects.end(); roi++)
//	{
//		setting.setValue("width", roi->width());
//		setting.setValue("height", roi->height());
//	}
//	setting.endGroup();
//}

void OptionsButtonBar::saveAllStartPositions(QFile& file, std::vector<QPoint> pos)
{
	std::vector<QPoint>::iterator it;
	QTextStream out(&file);

	for (it = pos.begin(); it != pos.end(); it++)
	{
		out << "startPoint:" << "(" << it->x() << "," << it->y() << ")" << '\n';
	}
}

void OptionsButtonBar::saveAllEndPositions(QFile& file, std::vector<QPoint> pos)
{
	std::vector<QPoint>::iterator it;
	QTextStream out(&file);

	for (it = pos.begin(); it != pos.end(); it++)
	{
		out << "endPoint:" << "(" << it->x() << "," << it->y() << ")" << '\n';
	}
}

void OptionsButtonBar::saveAllRects(QFile& file, std::vector<QRect> rect)
{
	std::vector<QRect>::iterator it;
	QTextStream out(&file);

	for (it = rect.begin(); it != rect.end(); it++)
	{
		out << "width:" << it->width() << '\n' << "height:" << it->height() << '\n';
	}
}