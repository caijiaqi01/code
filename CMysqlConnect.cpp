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

int CMysqlConnect::setSql()
{
	cout << endl;
	cout << "����ִ�� SELECT sage from student where sno = '20081001197'" << endl;

	try {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::ResultSet* res;

		/* �������� */
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "caijiaqi", "123456"); // ��Ҫ�޸�Ϊ�����ݿ���û�����
		/* ���� MySQL ���ݿ� university  */
		con->setSchema("world");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM world.city;"); // ��׼sql���
		while (res->next()) {
			cout << "\t MySQL replies: ";
			/* ͨ������ƫ����, 1 �����һ�� */
			int id = res->getInt(1);
			string name = res->getString(2);
			int a = 0;

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