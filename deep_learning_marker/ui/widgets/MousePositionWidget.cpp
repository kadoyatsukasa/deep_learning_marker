#include "MousePositionWidget.h"
#include "ui_MousePostionWidget.h"
#include "controller/SignalCenter.h"

MousePositionWidget::MousePositionWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MousePositionWidget)
{
	ui->setupUi(this);

	connect(SignalCenter::instance(), SIGNAL(displayCurrentMousePoint(QPoint)), this, SLOT(handleChangeCurrentPosition(QPoint)));
	connect(SignalCenter::instance(), SIGNAL(displayRoiStartPoint(QPoint)), this, SLOT(handleChangeRoiStart(QPoint)));
	connect(SignalCenter::instance(), SIGNAL(displayRoiEndPoint(QPoint)), this, SLOT(handleChangeRoiEnd(QPoint)));
}

MousePositionWidget::~MousePositionWidget()
{
	delete ui;
}

void MousePositionWidget::handleChangeCurrentPosition(QPoint point)
{
	QString text = QString("(%1,%2)").arg(point.x()).arg(point.y());
	ui->lbMouseCurrent->setText(text);
}

void MousePositionWidget::handleChangeRoiStart(QPoint point)
{
	QString text = QString("(%1,%2)").arg(point.x()).arg(point.y());
	ui->lbROIStart->setText(text);
}

void MousePositionWidget::handleChangeRoiEnd(QPoint point)
{
	QString text = QString("(%1,%2)").arg(point.x()).arg(point.y());
	ui->lbROIEnd->setText(text);
}