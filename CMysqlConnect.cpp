#include <CMysqlConnect.h>
#include <stdlib.h>
#include <iostream>

#include "jdbc/mysql_connection.h"

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

using namespace std;

CMysqlConnect::CMysqlConnect() {
}

CMysqlConnect::~CMysqlConnect() {
}
/*
//1 QString与int相互转换  

QString qstr = QString::number(123);
int i = atoi(qstr.toStdString().c_str());

//也可以这样：  
int i = atoi(qstr.ascii());

//2 QString与string，即std::string  

string s = qstr.toStdString();
QString qstr2 = QString::fromStdString(s);
*/

int CMysqlConnect::setSql(QVariantList& output)
{
	output.clear();
	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		/* 创建连接 */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "caijiaqi", "123456"); // 需要修改为你数据库的用户密码
		/* 连接 MySQL 数据库 university  */
		con->setSchema("world");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM world.city;"); // 标准sql语句
		while (res->next()) {
			cout << "\t MySQL replies: ";
			/* 通过数字偏移量, 1 代表第一列 */
			int id = res->getInt(1);
			string name = res->getString(2);
			int a = 0;

			QString str = QString::number(res->getInt(1)) + "    " +  QString::fromStdString(res->getString(2)) +
				"    " + QString::fromStdString(res->getString(3)) + "    " + QString::fromStdString(res->getString(4)) +
				"    " + QString::number(res->getInt(5));
			output.push_back(str);

			if (output.size() > 100) break;

		}
		delete res;
		delete stmt;
		delete con;

	}
	catch (sql::SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	cout << endl;

	return EXIT_SUCCESS;
}