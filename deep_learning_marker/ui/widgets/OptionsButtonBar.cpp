#include "OptionsButtonBar.h"
#include "ui_OptionsButtonBar.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "model/ImageModel.h"
#include "model/ParamListModel.h"
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
	saveAsConfig();
}

void OptionsButtonBar::handleClearAllMarks()
{
	emit SignalCenter::instance()->clearAllMarks();
}

void OptionsButtonBar::saveAsConfig()
{
	QFile file(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	QTextStream out(&file);

	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		for (int i = 0; i < ParamListModel::instance()->paramNameList.size(); i++)
		{
			out << ParamListModel::instance()->paramNameList[i] << '\n';
			for (int j = i; j < RoiRectModel::instance()->regionCase[i].regions.size(); j++)
			{
				out << "Gravity Point ("
					<< RoiRectModel::instance()->regionCase[i].regions[j].x() << ","
					<< RoiRectModel::instance()->regionCase[i].regions[j].y() << ")\n";
				out << "width = " << RoiRectModel::instance()->regionCase[i].regions[j].width() << '\t'
					<< "height = " << RoiRectModel::instance()->regionCase[i].regions[j].height() << '\n';
			}
		}
	}
}