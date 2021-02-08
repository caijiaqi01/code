#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QColor>
#include <QVector>
#include <QString>
#include <QVariantList>
class Calculate : public QObject
{
	Q_OBJECT
		Q_ENUMS(GenerateAlgorithm)
		Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
		Q_PROPERTY(QColor timeColor READ timeColor)
		Q_PROPERTY(QVariantList output READ getOutput NOTIFY outputChanged)

public:
	Calculate(QObject* parent = 0);
	~Calculate();

	enum GenerateAlgorithm {
		RandomRGB,
		RandomRed,
		RandomGreen,
		RandomBlue,
		LinearIncrease
	};

	enum CodeType {
		UNKNOWN,
		CPP,
		HEAD,
		QRC,
		PRO,
		QML
	};

	enum ChangeCodeType {
		ADD,
		COVER
	};

	QColor color() const;
	void setColor(const QColor& color);
	QColor timeColor() const;
	bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
	bool copyDirectoryFiles(const QString& fromDir, const QString& toDir, bool coverFileIfExist);
	bool changeCodeFile(const QString& filePath, ChangeCodeType changeType);
	bool copyDevice(const QString& fromDir, bool coverFileIfExist, ChangeCodeType changeType);

	QVariantList getOutput();

	Q_INVOKABLE GenerateAlgorithm algorithm() const;
	Q_INVOKABLE void setAlgorithm(GenerateAlgorithm algorithm);
	Q_INVOKABLE QString getStr(const QString& str);
	Q_INVOKABLE void copyMasterPlusDevice(const QString& sourceDevide, const QString& toDevide);
	Q_INVOKABLE void createPath();
	Q_INVOKABLE void connectMysql(); //连接数据库

signals:
	void colorChanged(const QColor& color);
	void currentTime(const QString& strTime);
	void outputChanged();

public slots:
	void start();
	void stop();

protected:
	void timerEvent(QTimerEvent* e);

private:
	GenerateAlgorithm m_algorithm;
	QColor m_currentColor;
	int m_nColorTimer;
	QString oldDevice = "CK55550";
	QString newDevice = "CK53330";
	QVariantList m_output;
};