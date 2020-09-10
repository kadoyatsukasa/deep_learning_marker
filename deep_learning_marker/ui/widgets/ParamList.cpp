#include "ParamList.h"
#include "model/RoiRectModel.h"
#include "model/ParamListModel.h"
#include "controller/SignalCenter.h"
#include <map>
#include <QPen>
#include <QModelIndex>

ParamList::ParamList(QWidget* parent) :
	QListView(parent)
{
	init();
}

void ParamList::init()
{
	std::vector<QString>::iterator it;
	m_itemModel = new QStandardItemModel(this);

	for (it = ParamListModel::instance()->paramNameList.begin(); it != ParamListModel::instance()->paramNameList.end(); it++)
	{
		QStandardItem* item = new QStandardItem(*it);
		m_itemModel->appendRow(item);
	}

	setModel(m_itemModel);
}