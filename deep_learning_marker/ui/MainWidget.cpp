#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ui/widgets/MousePositionWidget.h"
#include "ui/widgets/CVImageViewer/CVGraphicsView.h"
#include "ui/widgets/OptionsButtonBar.h"
#include "ui/widgets/ParamList.h"

#include "controller/SignalCenter.h"
#include "model/ImageModel.h"
#include "model/RoiRectModel.h"

#include <QModelIndex>

MainWidget::MainWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::MainWidget),
	m_buttonBar(nullptr),
	m_image(nullptr),
	m_list(nullptr),
	m_mousePos(nullptr)
{
	ui->setupUi(this);

	connect(SignalCenter::instance(), SIGNAL(displayImage(QString)), this, SLOT(handleDisplayImage(QString)));
	connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleChangePen(QModelIndex)));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::handleDisplayImage(QString absolutePath)
{
	ui->graphicsView->loadImage(absolutePath);
}

void MainWidget::handleChangePen(const QModelIndex& index)
{
	QPen t_pen(RoiRectModel::instance()->colourPen[index.row()]);
	t_pen.setWidth(3);

	RoiRectModel::instance()->suit.pen = t_pen;
}