#include <stdio.h>
#include <mysql.h>
#include <QVector>
#include <QString>
#include <QVariantList>

class CMysqlConnect
{

public:
	CMysqlConnect();
	~CMysqlConnect();

public:
	int setSql(QVariantList& output);

public:
	
};