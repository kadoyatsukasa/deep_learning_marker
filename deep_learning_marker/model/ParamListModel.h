#ifndef PARAMLISTMODEL_H
#define PARAMLISTMODEL_H

#include <vector>
#include <QString>
#include <map>
#include <QStandardItemModel>

class RoiRectModel;

class ParamListModel
{
public:
	static  ParamListModel* instance();

	std::vector<QString> paramNameList;
	std::vector<QString>::iterator currentName;

	QModelIndex paraIndex;
	QStandardItemModel* paraItem;

private:
	ParamListModel();
};

#endif // PARAMLISTMODEL_H
