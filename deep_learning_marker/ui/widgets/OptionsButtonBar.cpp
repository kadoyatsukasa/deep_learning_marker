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
#include "utils/FileUtil.h"

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
	QString suffixString;

	for (int i = 0; i < fileInformation.size(); ++i)
	{
		QFileInfo info = fileInformation.at(i);
		suffixString = info.suffix();
		if (suffixString == "conf")
		{
			continue;
		}

		ImageModel::instance()->imageArchive.push_back(info);
	}
	ImageModel::instance()->currentImage = ImageModel::instance()->imageArchive.begin();

	emit SignalCenter::instance()->displayImage(ImageModel::instance()->imageArchive[0].absoluteFilePath());
}

void OptionsButtonBar::handleSaveAllPositions()
{
	FileUtil::instance()->saveToConfigFile();
}

void OptionsButtonBar::handleClearAllMarks()
{
	emit SignalCenter::instance()->clearAllMarks();
}