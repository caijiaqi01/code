#include "calculate.h"
#include <QTimerEvent>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QFile>
//#include <QTextCodec>
//#include "CMysqlConnect.h"

Calculate::Calculate(QObject* parent)
	: QObject(parent)
	, m_algorithm(RandomRGB)
	, m_currentColor(Qt::black)
	, m_nColorTimer(0)
{
	qsrand(QDateTime::currentDateTime().toTime_t());
	oldDevice = "CK55550";
	newDevice = "CK53330";
}

Calculate::~Calculate()
{
}

QColor Calculate::color() const
{
	return m_currentColor;
}

void Calculate::setColor(const QColor& color)
{
	m_currentColor = color;
	emit colorChanged(m_currentColor);
}

QColor Calculate::timeColor() const
{
	QTime time = QTime::currentTime();
	int r = time.hour();
	int g = time.minute() * 2;
	int b = time.second() * 4;
	return QColor::fromRgb(r, g, b);
}

Calculate::GenerateAlgorithm Calculate::algorithm() const
{
	return m_algorithm;
}

void Calculate::setAlgorithm(GenerateAlgorithm algorithm)
{
	m_algorithm = algorithm;
}

void Calculate::start()
{
	if (m_nColorTimer == 0)
	{
		m_nColorTimer = startTimer(1000);
	}
}

void Calculate::stop()
{
	if (m_nColorTimer > 0)
	{
		killTimer(m_nColorTimer);
		m_nColorTimer = 0;
	}
}

void Calculate::timerEvent(QTimerEvent* e)
{
	if (e->timerId() == m_nColorTimer)
	{
		switch (m_algorithm)
		{
		case RandomRGB:
			m_currentColor.setRgb(qrand() % 255, qrand() % 255, qrand() % 255);
			break;
		case RandomRed:
			m_currentColor.setRed(qrand() % 255);
			break;
		case RandomGreen:
			m_currentColor.setGreen(qrand() % 255);
			break;
		case RandomBlue:
			m_currentColor.setBlue(qrand() % 255);
			break;
		case LinearIncrease:
		{
			int r = m_currentColor.red() + 10;
			int g = m_currentColor.green() + 10;
			int b = m_currentColor.blue() + 10;
			m_currentColor.setRgb(r % 255, g % 255, b % 255);
		}
		break;
		}
		emit colorChanged(m_currentColor);
		emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	}
	else
	{
		QObject::timerEvent(e);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//拷贝文件：
bool Calculate::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
	toDir.replace("\\", "/");
	if (sourceDir == toDir) {
		return true;
	}
	if (!QFile::exists(sourceDir)) {
		return false;
	}
	QDir* createfile = new QDir;
	bool exist = createfile->exists(toDir);
	if (exist) {
		if (coverFileIfExist) {
			createfile->remove(toDir);
		}
	}//end if

	if (!QFile::copy(sourceDir, toDir))
	{
		return false;
	}
	return true;
}

//拷贝文件夹：
bool Calculate::copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
		if (!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;

		if (fileInfo.isDir()) {    /**< 当为目录时，递归的进行copy */
			if (!copyDirectoryFiles(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()),
				coverFileIfExist))
				return false;
		}
		else {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
			if (coverFileIfExist && targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}

			/// 进行文件copy
			if (!QFile::copy(fileInfo.filePath(),
				targetDir.filePath(fileInfo.fileName()))) {
				return false;
			}
		}
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////

//修改文件内容
bool Calculate::changeCodeFile(const QString& filePath, ChangeCodeType changeType)
{
	CodeType codeType = UNKNOWN;
	if (filePath.indexOf(".cpp") > -1) {
		codeType = CPP;
	}
	else if (filePath.indexOf(".pro") > -1) {
		codeType = PRO;
	}
	else if (filePath.indexOf(".qrc") > -1) {
		codeType = QRC;
	}
	else if (filePath.indexOf(".h") > -1) {
		codeType = HEAD;
	}
	else if (filePath.indexOf(".qml") > -1) {
		codeType = QML;
	}
	else {
		codeType = UNKNOWN;
		return true;
	}

	QVector<QString> vecCodes;
	QFile file(filePath);
	QVector<QString> newCodes;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!file.atEnd())
		{
			QByteArray line = file.readLine();
			QString code(line);
			if (changeType == ADD) {
				vecCodes.push_back(code);
				code.replace(oldDevice, newDevice);
				QString lowerOldDevice = oldDevice.toLower();
				QString lowerNewDevice = newDevice.toLower();
				code.replace(lowerOldDevice, lowerNewDevice);
				if (code.indexOf(newDevice) > -1 || code.indexOf(lowerNewDevice) > -1) {
					if (codeType == QRC) {
						newCodes.push_back(code);
					}
					else {
						vecCodes.push_back(code);
					}
				}
			}
			else if (changeType == COVER) {
				code.replace(oldDevice, newDevice);
				QString lowerOldDevice = oldDevice.toLower();
				QString lowerNewDevice = newDevice.toLower();
				code.replace(lowerOldDevice, lowerNewDevice);
				vecCodes.push_back(code);
			}

		}
	}
	file.close();

	QFile writeFile(filePath);
	writeFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
	for (QString& code : vecCodes) {
		if (codeType == QRC && code.indexOf("</qresource>") > -1) {
			for (QString& str : newCodes) {
				writeFile.write(str.toUtf8());
			}
		}
		writeFile.write(code.toUtf8());
	}
	writeFile.close();

	return true;
}

//拷贝设备：
bool Calculate::copyDevice(const QString& fromDir, bool coverFileIfExist, ChangeCodeType changeType)
{
	if (fromDir.indexOf(".pro") > -1 ||
		fromDir.indexOf(".qrc") > -1 ||
		changeType == ADD) {
		changeCodeFile(fromDir, changeType);
		return true;
	}

	QDir sourceDir(fromDir);

	QString toDir = fromDir;
	toDir.replace(oldDevice, newDevice);
	QDir targetDir(toDir);

	if (!targetDir.exists()) {    /**< 如果目标目录不存在，则进行创建 */
		if (!targetDir.mkdir(targetDir.absolutePath()))
			return false;
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList) {
		QString strFileName = fileInfo.fileName();
		if (strFileName == "." || strFileName == "..")
			continue;

		if (fileInfo.isDir()) {    /**< 当为目录时，递归的进行copy */
			if (!copyDevice(fileInfo.filePath(),
				coverFileIfExist, changeType))
				return false;
		}
		else {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */

			QString sourceFile = fileInfo.filePath();
			QString toFileName = strFileName;
			toFileName.replace(oldDevice, newDevice);
			QString toFilePath = targetDir.filePath(toFileName);
			toFilePath.replace(oldDevice, newDevice);

			if (toFilePath.indexOf(newDevice) < 0) {
				continue;
			}

			if (coverFileIfExist && targetDir.exists(toFileName)) {
				targetDir.remove(toFileName);
			}

			/// 进行文件copy
			if (QFile::copy(fileInfo.filePath(), toFilePath)) {
				changeCodeFile(toFilePath, changeType);

			}
		}
	}
	return true;
}

void Calculate::copyMasterPlusDevice(const QString& sourceDevide, const QString& toDevide)
{
	oldDevice = sourceDevide;
	newDevice = toDevide;
//	copyDevice("E:/cmdesktop_CK530/CMDesktopApp/src/qml/Widgets", true, COVER);
	copyDevice("E:/cmdesktop_CK530/CMDesktopApp/src/qml/qml.qrc", true, ADD);
//	copyDevice("E:/cmdesktop_CK530/CMDesktopApp/src/UIMediators/UICMMediatorsContainer.h", true, ADD);
}

#include <QDateTime>
#include <qtextcodec.h>
void Calculate::createPath()
{
	return;
	QString fullPath = "C:/Program Files (x86)/CoolerMaster/MasterPlus/DataLog/XGPlus_DataLog.txt";
	QString fullPath_1 = QString("\"%1\"").arg(fullPath);
	QFile file(fullPath_1);
	file.open(QIODevice::ReadWrite | QIODevice::Append);
	file.close();

	QFile file1("C:/DataLog/XGPlus_DataLog.txt");
	file1.open(QIODevice::ReadWrite | QIODevice::Append);
	file1.close();

	QFile file2("E:/DataLog/XGPlus_DataLog.txt");
	file2.open(QIODevice::ReadWrite | QIODevice::Append);
	file2.close();
}

QString Calculate::getStr(const QString& str)
{
	QTextCodec* codec = QTextCodec::codecForName("GBK");
	QString m_str = "";
	if (str == "copy device") m_str = codec->toUnicode("复制设备");
	else if (str == "update SDK") m_str = codec->toUnicode("更新SDK");
	else if (str == "form Device") m_str = codec->toUnicode("参考设备:");
	else if (str == "to Device") m_str = codec->toUnicode("目标设备:");
	else if (str == "drop") m_str = codec->toUnicode("拖拽");
	else if (str == "path") m_str = codec->toUnicode("路径");
	else if (str == "database") m_str = codec->toUnicode("连接数据库");
	return m_str;

}

void Calculate::connectMysql()
{
	//CMysqlConnect m_mysql;
	//m_mysql.setSql(m_output);

	//emit outputChanged();
}

QVariantList Calculate::getOutput()
{
	return m_output;
}
