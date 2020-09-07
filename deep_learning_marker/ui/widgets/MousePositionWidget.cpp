#include "MousePositionWidget.h"
#include "ui_MousePostionWidget.h"

MousePositionWidget::MousePositionWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MousePositionWidget)
{
	ui->setupUi(this);
}

MousePositionWidget::~MousePositionWidget()
{
	delete ui;
}