#ifndef PARAMLISTMODEL_H
#define PARAMLISTMODEL_H

#include <vector>
#include <QString>
#include <map>

class RoiRectModel;

class ParamListModel
{
public:
	static  ParamListModel* instance();

	std::vector<QString> paramNameList;
	std::vector<std::map<QString, RoiRectModel>> paramList;
private:
	ParamListModel();
};

#endif // PARAMLISTMODEL_H
