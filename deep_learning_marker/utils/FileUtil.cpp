#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QDebug>

#include "FileUtil.h"
#include "model/RoiRectModel.h"
#include "model/ImageModel.h"

FileUtil::FileUtil()
{
}

FileUtil::~FileUtil()
{
}

FileUtil* FileUtil::instance()
{
	static FileUtil ins;
	return &ins;
}

void FileUtil::saveToConfigFile()
{
	m_file = new QFile(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	QTextStream out(m_file);

	if (m_file->open(QFile::WriteOnly | QFile::Truncate))
	{
		out.reset();
		for (int i = 0; i < RoiRectModel::instance()->regionCase.size(); i++)
		{
			out << "[" << RoiRectModel::instance()->regionCase[i].paraName << "]\n";
			out << "pen = " << RoiRectModel::instance()->colourPen[i] << '\n';
			for (int j = i; j < RoiRectModel::instance()->regionCase[i].regions.size(); j++)
			{
				out << "x = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.topLeft().x() << '\n';
				out << "y = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.topLeft().y() << '\n';
				out << "xr = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.bottomRight().x() << '\n';
				out << "yr = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.bottomRight().y() << '\n';

				out << "width = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.width() << '\n'
					<< "height = " << RoiRectModel::instance()->regionCase[i].regions[j].rect.height() << '\n';
				out << '\n';
			}
		}
		m_file->close();
	}

	delete m_file;

	if (RoiRectModel::instance()->dataExists())
	{
		RoiRectModel::instance()->dataReset();
	}
}

void FileUtil::readFromConfigFile()
{
	m_file = new QFile(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	qDebug() << m_file->fileName();
	if (!m_file->open(QFile::ReadOnly | QFile::Truncate))
	{
		return;
	}
	else
	{
		while (!m_file->atEnd())
		{
			QByteArray lines = m_file->readLine();
			parseDoc(lines);
		}

		m_file->close();
		delete m_file;
	}
}

void FileUtil::parseDoc(QByteArray& line)
{
	if (line.contains("x ="))
		m_resultTLX = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("y ="))
		m_resultTLY = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("xr ="))
		m_resultBRX = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("yr ="))
		m_resultBRY = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("width ="))
		m_resultWidth = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("height ="))
		m_resultHeight = line.mid(line.indexOf("=") + 2).simplified();
	if (line.contains("pen = "))
		m_resultColor = line.mid(line.indexOf("=") + 2).simplified();

	if (!m_resultTLX.isEmpty())
		RoiRectModel::instance()->startPoint.setX(m_resultTLX.toInt());
	if (!m_resultTLY.isEmpty())
		RoiRectModel::instance()->startPoint.setY(m_resultTLY.toInt());
	if (!m_resultBRX.isEmpty())
		RoiRectModel::instance()->endPoint.setX(m_resultBRX.toInt());
	if (!m_resultBRY.isEmpty())
		RoiRectModel::instance()->endPoint.setY(m_resultBRY.toInt());
	if (!m_resultColor.isEmpty())
		RoiRectModel::instance()->suit.crayon = QPen(m_resultColor.toInt());

	//set the data of rectangle
	if (RoiRectModel::instance()->startPoint.x() > 0 &&
		RoiRectModel::instance()->startPoint.y() > 0 &&
		RoiRectModel::instance()->endPoint.x() > 0 &&
		RoiRectModel::instance()->endPoint.y() > 0)
	{
		QRect t_rect(RoiRectModel::instance()->startPoint, RoiRectModel::instance()->endPoint);

		RoiRectModel::instance()->suit.rect = t_rect;
		RoiRectModel::instance()->roiItem.regions.push_back(RoiRectModel::instance()->suit);
		RoiRectModel::instance()->regionCase.push_back(RoiRectModel::instance()->roiItem);

		//Reset after read the data of ROI every time
		reset();
	}
}

void FileUtil::reset()
{
	RoiRectModel::instance()->startPoint.setX(0);
	RoiRectModel::instance()->startPoint.setY(0);
	RoiRectModel::instance()->endPoint.setX(0);
	RoiRectModel::instance()->endPoint.setY(0);

	m_resultTLX.clear();
	m_resultTLY.clear();
	m_resultBRX.clear();
	m_resultBRY.clear();
	m_resultWidth.clear();
	m_resultHeight.clear();
	m_resultColor.clear();
}

bool FileUtil::fileIsExsit()
{
	m_file = new QFile(QString("%1/conf-%2.conf").arg(ImageModel::instance()->imageFilePath).arg(ImageModel::instance()->imageFileName));
	qDebug() << m_file->fileName();
	return m_file->exists();
}