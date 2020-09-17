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

	setCurrentItem(item(0));
}

void ParamList::changeCurrentRow(int currentRow)
{
	setCurrentRow(currentRow);
	item(currentRow)->setSelected(true);
	setCurrentItem(item(currentRow));
	setCurrentIndex(model()->index(currentRow, 0));

	QPen t_pen(RoiRectModel::instance()->colourPen[currentRow]);
	t_pen.setWidth(3);
	RoiRectModel::instance()->suit.pen = t_pen;
	RoiRectModel::instance()->roiItem.paraName = ParamListModel::instance()->paramNameList[currentRow];
}