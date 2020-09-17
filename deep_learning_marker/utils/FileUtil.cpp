#include "FileUtil.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include "model/RoiRectModel.h"
#include "model/ImageModel.h"

FileUtil::FileUtil()
{
}

FileUtil* FileUtil::instance()
{
	static FileUtil ins;
	return &ins;
}

void FileUtil::saveToConfigFile()
{
	QFile file(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	QTextStream out(&file);

	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		for (int i = 0; i < RoiRectModel::instance()->regionCase.size(); i++)
		{
			out << RoiRectModel::instance()->regionCase[i].paraName << '\n';
			for (int j = i; j < RoiRectModel::instance()->regionCase[i].regions.size(); j++)
			{
				out << "TopLeft ("
					<< RoiRectModel::instance()->regionCase[i].regions[j].topLeft().x() << ","
					<< RoiRectModel::instance()->regionCase[i].regions[j].topLeft().y() << ")\n";
				out << "TopRight ("
					<< RoiRectModel::instance()->regionCase[i].regions[j].topRight().x() << ","
					<< RoiRectModel::instance()->regionCase[i].regions[j].topRight().y() << ")\n";
				out << "BottomLeft ("
					<< RoiRectModel::instance()->regionCase[i].regions[j].bottomLeft().x() << ","
					<< RoiRectModel::instance()->regionCase[i].regions[j].bottomLeft().y() << ")\n";
				out << "BottomRight ("
					<< RoiRectModel::instance()->regionCase[i].regions[j].bottomRight().x() << ","
					<< RoiRectModel::instance()->regionCase[i].regions[j].bottomRight().y() << ")\n";

				out << "Center ("
					<< RoiRectModel::instance()->regionCase[j].regions[j].center().x() << ","
					<< RoiRectModel::instance()->regionCase[j].regions[j].center().y() << ")\n";
				out << "Width = " << RoiRectModel::instance()->regionCase[j].regions[j].width() << '\t'
					<< "Height = " << RoiRectModel::instance()->regionCase[j].regions[j].height() << '\n';
			}
		}
	}
}