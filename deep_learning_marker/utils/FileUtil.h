#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

class FileUtil
{
public:
	static FileUtil* instance();

	void saveToConfigFile();
	void readFromConfigFile(QString file);

private:
	FileUtil();
};

#endif // FILEUTIL_H
