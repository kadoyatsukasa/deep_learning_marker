#ifndef PARAMLIST_H
#define PARAMLIST_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QStandardItemModel>

class RoiRectModel;
class ParamListModel;

class ParamList : public QListView
{
	Q_OBJECT
public:
	ParamList(QWidget* parent = nullptr);

private:
	void init();

private:
	std::vector<QString> m_paramName;
	QStandardItemModel* m_itemModel;
};

#endif // PARAMLIST_H
