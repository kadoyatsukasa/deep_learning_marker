#include "ParamListModel.h"
#include "model/RoiRectModel.h"
#include <QListView>
#include <QModelIndex>
ParamListModel::ParamListModel()

{
	paramNameList.push_back(QString::fromLocal8Bit("Para01"));
	paramNameList.push_back(QString::fromLocal8Bit("Para02"));
	paramNameList.push_back(QString::fromLocal8Bit("Para03"));
	paramNameList.push_back(QString::fromLocal8Bit("Para04"));
}

ParamListModel* ParamListModel::instance()
{
	static ParamListModel ins;
	return &ins;
}