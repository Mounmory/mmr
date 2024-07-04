#include "Common_def.h"
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

	//sqlite3* db;
	//char* zErrMsg = 0;
	//int rc;

	//// 打开或创建数据库
	//rc = sqlite3_open("test.db", &db);
	//if (rc) {
	//	std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
	//	return rc;
	//}
	//else {
	//	std::cout << "成功打开数据库" << std::endl;
	//}

	//// 创建表
	//std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Students (ID INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL, Age INT NOT NULL);";
	//rc = sqlite3_exec(db, createTableSQL.c_str(), 0, 0, &zErrMsg);
	//if (rc != SQLITE_OK) {
	//	std::cerr << "SQL错误: " << zErrMsg << std::endl;
	//	sqlite3_free(zErrMsg);
	//	return rc;
	//}
	//else {
	//	std::cout << "表创建成功" << std::endl;
	//}

	//// 插入数据
	//std::string insertSQL = "INSERT INTO Students (ID, Name, Age) VALUES (1, 'Alice', 20);";
	//rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &zErrMsg);
	//if (rc != SQLITE_OK) {
	//	std::cerr << "SQL错误: " << zErrMsg << std::endl;
	//	sqlite3_free(zErrMsg);
	//	return rc;
	//}
	//else {
	//	std::cout << "插入数据成功" << std::endl;
	//}

	//// 更新数据
	//std::string updateSQL = "UPDATE Students SET Age = 21 WHERE Name = 'Alice';";
	//rc = sqlite3_exec(db, updateSQL.c_str(), 0, 0, &zErrMsg);
	//if (rc != SQLITE_OK) {
	//	std::cerr << "SQL错误: " << zErrMsg << std::endl;
	//	sqlite3_free(zErrMsg);
	//	return rc;
	//}
	//else {
	//	std::cout << "更新数据成功" << std::endl;
	//}

	//// 查询数据
	//std::string selectSQL = "SELECT * FROM Students;";
	//rc = sqlite3_exec(db, selectSQL.c_str(), callback, 0, &zErrMsg);
	//if (rc != SQLITE_OK) {
	//	std::cerr << "SQL错误: " << zErrMsg << std::endl;
	//	sqlite3_free(zErrMsg);
	//	return rc;
	//}
	//else {
	//	std::cout << "查询数据成功" << std::endl;
	//}

	//// 删除数据
	//std::string deleteSQL = "DELETE FROM Students WHERE Name = 'Alice';";
	//rc = sqlite3_exec(db, deleteSQL.c_str(), 0, 0, &zErrMsg);
	//if (rc != SQLITE_OK) {
	//	std::cerr << "SQL错误: " << zErrMsg << std::endl;
	//	sqlite3_free(zErrMsg);
	//	return rc;
	//}
	//else {
	//	std::cout << "删除数据成功" << std::endl;
	//}

	//// 关闭数据库
	//sqlite3_close(db);

	sqlite3 *db;
	char *errMsg = 0;
	int rc;

	*errMsg = 'a';
	// 打开数据库（如果数据库不存在，则创建一个）  
	rc = sqlite3_open_v2("example.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0);
	if (rc) {
		fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else {
		fprintf(stderr, "成功打开数据库\n");
	}

	// 创建一个新的表  
	char *sql = "CREATE TABLE IF NOT EXISTS students ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"name TEXT NOT NULL,"
		"age INTEGER"
		");";
	rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL错误: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else {
		fprintf(stderr, "表创建成功\n");
	}

	// 插入一些数据  
	sql = "INSERT INTO students (name, age) VALUES ('Alice', 25), ('Bob', 22);";
	rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL错误: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else {
		fprintf(stderr, "数据插入成功\n");
	}

	// 查询数据  
	sqlite3_stmt *res;
	sql = "SELECT id, name, age FROM students;";
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
	if (rc) {
		fprintf(stderr, "准备语句失败: %s\n", sqlite3_errmsg(db));
	}
	else {
		while (sqlite3_step(res) == SQLITE_ROW) {
			int id = sqlite3_column_int(res, 0);
			const unsigned char *name = sqlite3_column_text(res, 1);
			int age = sqlite3_column_int(res, 2);
			printf("ID: %d, Name: %s, Age: %d\n", id, name, age);
		}
		sqlite3_finalize(res);
	}

	// 关闭数据库  
	sqlite3_close_v2(db);

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}


