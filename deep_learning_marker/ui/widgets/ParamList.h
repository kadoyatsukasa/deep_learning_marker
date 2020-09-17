#ifndef PARAMLIST_H
#define PARAMLIST_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QListWidget>
#include <QStandardItemModel>

class RoiRectModel;
class ParamListModel;

class ParamList : public QListWidget
{
	Q_OBJECT
public:
	ParamList(QWidget* parent = nullptr);

public slots:
	void changeCurrentRow(int row);

private:
	void init();

private:
	std::vector<QString> m_paramName;
	QStandardItemModel* m_itemModel;
};

#endif // PARAMLIST_H
