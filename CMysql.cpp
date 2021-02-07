// STL_test.cpp : 定义控制台应用程序的入口点。
//
#include "CMysql.h"
#include <WinSock.h>  //一定要包含这个，或者winsock2.h
#include <Windows.h>

//包含附加依赖项，也可以在工程--属性里面设置
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"libmysql.lib")

using namespace std;

CMysql::CMysql() {
	mysql = new MYSQL;
}

CMysql::~CMysql() {
	delete mysql;
}

int CMysql::setSql()
{
	ConnectDatabase();
	QueryDatabase1();
	InsertData();
	QueryDatabase2();
	ModifyData();
	QueryDatabase2();
	DeleteData();
	QueryDatabase2();
	FreeConnect();
	system("pause");
	return 0;
}


//连接数据库
bool CMysql::ConnectDatabase()
{
	//初始化mysql
	mysql_init(mysql);  //连接mysql，数据库

	//返回false则连接失败，返回true则连接成功
	if (!(mysql_real_connect(mysql,"127.0.0.1", "caijiaqi", "123456", "world",3306, NULL, 0))) //中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等），可以先写成参数再传进去
	{
		printf( "Error connecting to database:%s\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("Connected...\n");
		return true;
	}

	return true;
}



//释放资源
void CMysql::FreeConnect()
{
	//释放资源
	mysql_free_result(res);
	mysql_close(mysql);
}

/***************************数据库操作***********************************/
//其实所有的数据库操作都是先写个sql语句，然后用mysql_query(&mysql,query)来完成，包括创建数据库或表，增删改查
//查询数据


bool CMysql::QueryDatabase1()
{
	char query[150] = "";
	sprintf(query, "select * from user"); //执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
	mysql_query(mysql,"set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
	//返回0 查询成功，返回1查询失败
	if(mysql_query(mysql, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//获取结果集
	if (!(res=mysql_store_result(mysql)))    //获得sql语句结束后返回的结果集
	{
		printf("Couldn't get result from %s\n", mysql_error(mysql));
		return false;
	}

	//打印数据行数
	printf("number of dataline returned: %d\n",mysql_affected_rows(mysql));

	//获取字段的信息
	char *str_field[32];  //定义一个字符串数组存储字段信息
	for(int i=0;i<4;i++)   //在已知字段数量的情况下获取字段名
	{
		str_field[i]=mysql_fetch_field(res)->name;
	}
	for(int i=0;i<4;i++)   //打印字段
		printf("%10s\t",str_field[i]);
	printf("\n");
	//打印获取的数据
	while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行
	{
		printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column是列数组
	}
	return true;
}


bool CMysql::QueryDatabase2()
{
	mysql_query(mysql,"set names gbk");
	//返回0 查询成功，返回1查询失败
	if(mysql_query(mysql, "select * from user"))        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	res=mysql_store_result(mysql);
	//打印数据行数
	printf("number of dataline returned: %d\n",mysql_affected_rows(mysql));
	char field[32][32];
	for(int i=0;fd=mysql_fetch_field(res);i++)  //获取字段名
		strcpy(field[i],fd->name);
	int j=mysql_num_fields(res);  // 获取列数
	for(int i=0;i<j;i++)  //打印字段
		printf("%10s\t",field[i]);
	printf("\n");
	while(column=mysql_fetch_row(res))
	{
		for(int i=0;i<j;i++)
			printf("%10s\t",column[i]);
		printf("\n");
	}
	return true;
}


//插入数据
bool CMysql::InsertData()
{
	char query[150] = "";
	sprintf(query, "insert into user values (NULL, 'Lilei', 'wyt2588zs','lilei23@sina.cn');");  //可以想办法实现手动在控制台手动输入指令
	if(mysql_query(mysql, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}



//修改数据
bool CMysql::ModifyData()
{
	char query[150] = "";
	sprintf(query, "update user set email='lilei325@163.com' where name='Lilei'");
	if(mysql_query(mysql, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}
//删除数据
bool CMysql::DeleteData()
{
	char query[150] = "";
	sprintf(query, "delete from user where id=6");
	//char query[100];
	//printf("please input the sql:\n");
	//gets(query);  //这里手动输入sql语句
	if(mysql_query(mysql, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}

