#include "ParamListModel.h"
#include "model/RoiRectModel.h"
#include <QListView>
#include <QModelIndex>
ParamListModel::ParamListModel()

{
	paramNameList.push_back(QString::fromLocal8Bit("����һ"));
	paramNameList.push_back(QString::fromLocal8Bit("������"));
	paramNameList.push_back(QString::fromLocal8Bit("������"));
	paramNameList.push_back(QString::fromLocal8Bit("������"));
}

ParamListModel* ParamListModel::instance()
{
	static ParamListModel ins;
	return &ins;
}