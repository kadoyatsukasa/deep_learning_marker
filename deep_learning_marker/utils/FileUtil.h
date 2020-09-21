#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>
#include <QFile>

class FileUtil
{
public:
	static FileUtil* instance();
	~FileUtil();

	void saveToConfigFile();
	void readFromConfigFile();
	bool fileIsExsit();

private:
	FileUtil();

	void reset();

	void parseDoc(QByteArray&);

	QFile* m_file;

	QString m_resultTLX;
	QString m_resultTLY;
	QString m_resultBRX;
	QString m_resultBRY;
	QString m_resultWidth;
	QString m_resultHeight;
	QString m_resultColor;
};

#endif // FILEUTIL_H
