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
	//initWidget();

	connect(SignalCenter::instance(), SIGNAL(displayImage(const char*)), this, SLOT(handleDisplayImage(const char*)));
	connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(handleChangePen(QModelIndex)));
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::initWidget()
{
	//m_buttonBar = new OptionsButtonBar(this);
	//m_image = new CVGraphicsView(this);
	//m_list = new ParamList(this);
	//m_mousePos = new MousePositionWidget(this);
}

void MainWidget::handleDisplayImage(const char* img)
{
	ui->graphicsView->loadImage(img);
}

void MainWidget::handleChangePen(const QModelIndex& index)
{
	m_pen.setBrush(RoiRectModel::instance()->brush[index.row()]);
	m_pen.setWidth(3);
	RoiRectModel::instance()->pencilCase.push_back(m_pen);
	emit SignalCenter::instance()->changePen(m_pen);
}