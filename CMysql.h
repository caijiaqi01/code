#include <stdio.h>
#include <mysql.h>

class CMysql
{

public:
	CMysql();
	~CMysql();

public:
	bool ConnectDatabase();     //��������
	void FreeConnect();
	bool QueryDatabase1();  //��ѯ1
	bool QueryDatabase2();  //��ѯ2
	bool InsertData();
	bool ModifyData();
	bool DeleteData();
	int setSql();

public:
	MYSQL *mysql; //mysql����
	MYSQL_FIELD* fd;  //�ֶ�������
	MYSQL_RES* res; //����ṹ�������е�һ����ѯ�����
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
	//char [150]; //��ѯ���
	//char field[32][32];  //���ֶ�����ά����
};