#include "ParamListModel.h"
#include "model/RoiRectModel.h"
#include <QListView>
#include <QModelIndex>
ParamListModel::ParamListModel()

{
	paramNameList.push_back(QString::fromLocal8Bit("参数一"));
	paramNameList.push_back(QString::fromLocal8Bit("参数二"));
	paramNameList.push_back(QString::fromLocal8Bit("参数三"));
	paramNameList.push_back(QString::fromLocal8Bit("参数四"));
}

ParamListModel* ParamListModel::instance()
{
	static ParamListModel ins;
	return &ins;
}