// STL_test.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "CMysql.h"
#include <WinSock.h>  //һ��Ҫ�������������winsock2.h
#include <Windows.h>

//�������������Ҳ�����ڹ���--������������
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


//�������ݿ�
bool CMysql::ConnectDatabase()
{
	//��ʼ��mysql
	mysql_init(mysql);  //����mysql�����ݿ�

	//����false������ʧ�ܣ�����true�����ӳɹ�
	if (!(mysql_real_connect(mysql,"127.0.0.1", "caijiaqi", "123456", "world",3306, NULL, 0))) //�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ
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



//�ͷ���Դ
void CMysql::FreeConnect()
{
	//�ͷ���Դ
	mysql_free_result(res);
	mysql_close(mysql);
}

/***************************���ݿ����***********************************/
//��ʵ���е����ݿ����������д��sql��䣬Ȼ����mysql_query(&mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�
//��ѯ����


bool CMysql::QueryDatabase1()
{
	char query[150] = "";
	sprintf(query, "select * from user"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�user�Ǳ��������ü����ţ���strcpyҲ����
	mysql_query(mysql,"set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if(mysql_query(mysql, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	//��ȡ�����
	if (!(res=mysql_store_result(mysql)))    //���sql�������󷵻صĽ����
	{
		printf("Couldn't get result from %s\n", mysql_error(mysql));
		return false;
	}

	//��ӡ��������
	printf("number of dataline returned: %d\n",mysql_affected_rows(mysql));

	//��ȡ�ֶε���Ϣ
	char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
	for(int i=0;i<4;i++)   //����֪�ֶ�����������»�ȡ�ֶ���
	{
		str_field[i]=mysql_fetch_field(res)->name;
	}
	for(int i=0;i<4;i++)   //��ӡ�ֶ�
		printf("%10s\t",str_field[i]);
	printf("\n");
	//��ӡ��ȡ������
	while (column = mysql_fetch_row(res))   //����֪�ֶ���������£���ȡ����ӡ��һ��
	{
		printf("%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2],column[3]);  //column��������
	}
	return true;
}


bool CMysql::QueryDatabase2()
{
	mysql_query(mysql,"set names gbk");
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if(mysql_query(mysql, "select * from user"))        //ִ��SQL���
	{
		printf("Query failed (%s)\n",mysql_error(mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	res=mysql_store_result(mysql);
	//��ӡ��������
	printf("number of dataline returned: %d\n",mysql_affected_rows(mysql));
	char field[32][32];
	for(int i=0;fd=mysql_fetch_field(res);i++)  //��ȡ�ֶ���
		strcpy(field[i],fd->name);
	int j=mysql_num_fields(res);  // ��ȡ����
	for(int i=0;i<j;i++)  //��ӡ�ֶ�
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


//��������
bool CMysql::InsertData()
{
	char query[150] = "";
	sprintf(query, "insert into user values (NULL, 'Lilei', 'wyt2588zs','lilei23@sina.cn');");  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	if(mysql_query(mysql, query))        //ִ��SQL���
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



//�޸�����
bool CMysql::ModifyData()
{
	char query[150] = "";
	sprintf(query, "update user set email='lilei325@163.com' where name='Lilei'");
	if(mysql_query(mysql, query))        //ִ��SQL���
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
//ɾ������
bool CMysql::DeleteData()
{
	char query[150] = "";
	sprintf(query, "delete from user where id=6");
	//char query[100];
	//printf("please input the sql:\n");
	//gets(query);  //�����ֶ�����sql���
	if(mysql_query(mysql, query))        //ִ��SQL���
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

