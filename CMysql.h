#include <stdio.h>
#include <mysql.h>

class CMysql
{

public:
	CMysql();
	~CMysql();

public:
	bool ConnectDatabase();     //函数声明
	void FreeConnect();
	bool QueryDatabase1();  //查询1
	bool QueryDatabase2();  //查询2
	bool InsertData();
	bool ModifyData();
	bool DeleteData();
	int setSql();

public:
	MYSQL *mysql; //mysql连接
	MYSQL_FIELD* fd;  //字段列数组
	MYSQL_RES* res; //这个结构代表返回行的一个查询结果集
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列
	//char [150]; //查询语句
	//char field[32][32];  //存字段名二维数组
};