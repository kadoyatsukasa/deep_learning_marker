#include "ParamList.h"
#include "model/RoiRectModel.h"
#include "model/ParamListModel.h"
#include "controller/SignalCenter.h"
#include "controller/SignalCenter.h"

#include <map>
#include <QPen>
#include <QModelIndex>

ParamList::ParamList(QWidget* parent) :
	QListWidget(parent)
{
	init();
	connect(SignalCenter::instance(), SIGNAL(goNext(int)), this, SLOT(changeCurrentRow(int)));
	connect(SignalCenter::instance(), SIGNAL(goFore(int)), this, SLOT(changeCurrentRow(int)));
}

void ParamList::init()
{
	std::vector<QString>::iterator it;

	for (it = ParamListModel::instance()->paramNameList.begin(); it != ParamListModel::instance()->paramNameList.end(); it++)
	{
		addItem(*it);
	}

	item(0)->setForeground(Qt::black);
	item(0)->setBackground(QColor(RoiRectModel::instance()->colourPen[0]));
	setCurrentItem(item(0));
}

void ParamList::changeCurrentRow(int currentRow)
{
	item(currentRow)->setSelected(true);
	item(currentRow)->setForeground(Qt::black);
	item(currentRow)->setBackground(QColor(RoiRectModel::instance()->colourPen[currentRow]));
	setCurrentItem(item(currentRow));

	QPen t_pen(RoiRectModel::instance()->colourPen[currentRow]);
	t_pen.setWidth(3);
	RoiRectModel::instance()->suit.crayon = t_pen;
	RoiRectModel::instance()->roiItem.paraName = ParamListModel::instance()->paramNameList[currentRow];
}