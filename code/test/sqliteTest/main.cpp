#include "Common.h"
#include "util/CDataStream.h"
#include "sqlite3/sqlite3.h"
#include <iostream>


// 回调函数，用于SELECT语句
int callback(void* data, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		std::cout << azColName[i] << ": " << argv[i] << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

int main() {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;

	// 打开或创建数据库
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
		return rc;
	}
	else {
		std::cout << "成功打开数据库" << std::endl;
	}

	// 创建表
	std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Students (ID INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Age INT NOT NULL);";
	rc = sqlite3_exec(db, createTableSQL.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
		return rc;
	}
	else {
		std::cout << "表创建成功" << std::endl;
	}

	// 插入数据
	std::string insertSQL = "INSERT INTO Students (ID, Name, Age) VALUES (1, 'Alice', 20);";
	rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
		return rc;
	}
	else {
		std::cout << "插入数据成功" << std::endl;
	}

	// 更新数据
	std::string updateSQL = "UPDATE Students SET Age = 21 WHERE Name = 'Alice';";
	rc = sqlite3_exec(db, updateSQL.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
		return rc;
	}
	else {
		std::cout << "更新数据成功" << std::endl;
	}

	// 查询数据
	std::string selectSQL = "SELECT * FROM Students;";
	rc = sqlite3_exec(db, selectSQL.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
		return rc;
	}
	else {
		std::cout << "查询数据成功" << std::endl;
	}

	// 删除数据
	std::string deleteSQL = "DELETE FROM Students WHERE Name = 'Alice';";
	rc = sqlite3_exec(db, deleteSQL.c_str(), 0, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL错误: " << zErrMsg << std::endl;
		sqlite3_free(zErrMsg);
		return rc;
	}
	else {
		std::cout << "删除数据成功" << std::endl;
	}

	// 关闭数据库
	sqlite3_close(db);

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}


