#include "OptionsButtonBar.h"
#include "ui_OptionsButtonBar.h"
#include <QFileDialog>
#include <QMessageBox>
#include "model/ImageModel.h"
#include "controller/SignalCenter.h"
OptionsButtonBar::OptionsButtonBar(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::OptionsButtonBar)
{
	ui->setupUi(this);
	connect(ui->btnLoadImage, SIGNAL(clicked()), this, SLOT(handleLoadSingleImage()));
}

OptionsButtonBar::~OptionsButtonBar()
{
	delete ui;
}

void OptionsButtonBar::handleLoadSingleImage()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Select image"), ".", tr("Image Files(*.png *.jpg *.bmp *.jpeg)"));
	if (filename.isEmpty())
	{
		QMessageBox::information(this, tr("Hint"), tr("You haven't chosen any image yet"));
	}
	else
	{
		ImageModel::instance()->imageFilename = filename;
		emit SignalCenter::instance()->displayImage(ImageModel::instance()->imageFilename.toStdString().c_str());
	}

	ImageModel::instance()->imageFilename.clear();
}