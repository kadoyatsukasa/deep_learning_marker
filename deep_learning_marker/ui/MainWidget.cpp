#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ui/widgets/MousePositionWidget.h"
#include "ui/widgets/CVImageViewer/CVGraphicsView.h"
#include "ui/widgets/OptionsButtonBar.h"

#include "controller/SignalCenter.h"
#include "model/ImageModel.h"

MainWidget::MainWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MainWidget)
{
	initWidget();
	ui->setupUi(this);

	connect(SignalCenter::instance(), SIGNAL(displayImage(const char*)), this, SLOT(handleDisplayImage(const char*)));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::initWidget()
{
}

void MainWidget::handleDisplayImage(const char* img)
{
	ui->graphicsView->loadImage(img);
}