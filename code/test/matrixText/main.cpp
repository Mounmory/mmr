#include "Common_def.h"
#include "util/CMatrix.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

using namespace mmrUtil;
template<typename _T>
void printMatrix(CMatrix<_T>& mt) 
{
	size_t rowCount = mt.getRowCount();
	size_t colCount = mt.getColCount();

	std::cout << "CMatrix Type:" << typeid(_T).name() <<
		"\t" << "nRow:" << rowCount << "\t" << "nCol:" << colCount << std::endl;
	for (size_t i = 0; i < rowCount; ++i)
	{
		for (size_t j = 0; j < colCount; ++j)
		{
			std::cout << mt.getPtr()[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}


int main()
{
	std::cout << "test std::string begin!" << std::endl;
	try
	{
		int count = 0;
		while (count++ < 100000)
		{
			//string 测试
			CMatrix<std::string> emptyInt;//默认构造函数，构造空数组
			CMatrix<std::string> emptyInt1(0, 2);//默认构造函数，构造空数组
			CMatrix<std::string> emptyInt2(2, 0);
			emptyInt1 = "hello";
			emptyInt2 = "ok";
			emptyInt2.reSizeArray(3, 0);
			emptyInt2 = "ok";
			emptyInt1 = emptyInt2;

			CMatrix<std::string> arrayInt1(2, 2);//构造数组大小

			std::cout << "1、数组1默认值" << std::endl;
			printMatrix<std::string>(arrayInt1);

			arrayInt1.zeroArray();//数值清零
			std::cout << "2、数组1清零值" << std::endl;
			printMatrix<std::string>(arrayInt1);

			arrayInt1 = "arrayInt1";//整体赋值
			arrayInt1[1][0] = "change10";
			std::cout << "3、数组1修改值" << std::endl;
			printMatrix<std::string>(arrayInt1);

			CMatrix<std::string> arrayInt2(arrayInt1);//拷贝构造函数
			std::cout << "4、数组2使用数组1拷贝构造值" << std::endl;
			printMatrix<std::string>(arrayInt2);

			arrayInt2.reSizeArray(3, 4);

			arrayInt2 = "changeInt2";
			std::cout << "5、数组2使用赋值运算符，等于常数" << std::endl;
			printMatrix<std::string>(arrayInt2);

			arrayInt1 = arrayInt2;
			arrayInt2[0][0] = "changearray2";
			std::cout << "6、数组1使用赋值运算符，等于数组2" << std::endl;
			printMatrix<std::string>(arrayInt1);

			arrayInt2 = arrayInt1;
			arrayInt1 = arrayInt2;
			arrayInt1 = arrayInt1;
			std::cout << "7、数组1使用赋值运算符，自赋值" << std::endl;
			printMatrix<std::string>(arrayInt1);

			CMatrix<std::string> arrayInt3(std::move(arrayInt1));
			std::cout << "8、数组3使用移动构造函数" << std::endl;
			printMatrix<std::string>(arrayInt3);

			arrayInt3.reSizeArray(5, 6);
			arrayInt3 = "arrayInt3";
			std::cout << "9、交换数组2与3" << std::endl;
			std::cout << "交换前2与3：" << std::endl;
			printMatrix<std::string>(arrayInt2);
			printMatrix<std::string>(arrayInt3);
			std::swap(arrayInt3, arrayInt2);
			std::cout << "交换后2与3：" << std::endl;
			printMatrix<std::string>(arrayInt2);
			printMatrix<std::string>(arrayInt3);

			std::cout << "10、3自身移动赋值运算符" << std::endl;
			arrayInt3 = std::move(arrayInt3);
			printMatrix<std::string>(arrayInt3);

			std::cout << "11、2对3自身移动赋值运算符" << std::endl;
			arrayInt3 = std::move(arrayInt2);
			std::cout << "3的值" << std::endl;
			arrayInt3 = std::move(arrayInt3);
			std::cout << "2的值" << std::endl;
			arrayInt3 = std::move(arrayInt2);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	//测试Int类型
	std::cout << "test int begin!" << std::endl;
	try
	{
		int count = 0;
		while (count++ < 100000)
		{
			CMatrix<int> emptyInt;//默认构造函数，构造空数组
			CMatrix<int> emptyInt1(0, 2);//默认构造函数，构造空数组
			CMatrix<int> emptyInt2(2, 0);
			emptyInt1 = 10;
			emptyInt2 = 10;
			emptyInt2.reSizeArray(3, 0);
			emptyInt1 = emptyInt2;

			CMatrix<int> arrayInt1(2, 2);//构造数组大小

			std::cout << "1、数组1默认值" << std::endl;
			printMatrix(arrayInt1);

			arrayInt1.zeroArray();//数值清零
			std::cout << "2、数组1清零值" << std::endl;
			printMatrix(arrayInt1);

			arrayInt1 = 2;//整体赋值
			arrayInt1[1][0] = 3;
			std::cout << "3、数组1修改值" << std::endl;
			printMatrix(arrayInt1);

			CMatrix<int> arrayInt2(arrayInt1);//拷贝构造函数
			std::cout << "4、数组2使用数组1拷贝构造值" << std::endl;
			printMatrix(arrayInt2);

			arrayInt2.reSizeArray(3, 4);

			arrayInt2 = 5;
			std::cout << "5、数组2使用赋值运算符，等于常数" << std::endl;
			printMatrix(arrayInt2);

			arrayInt1 = arrayInt2;
			std::cout << "6、数组1使用赋值运算符，等于数组2" << std::endl;
			printMatrix(arrayInt1);

			arrayInt1 = arrayInt1;
			std::cout << "7、数组1使用赋值运算符，自赋值" << std::endl;
			printMatrix(arrayInt1);

			CMatrix<int> arrayInt3(std::move(arrayInt1));
			std::cout << "8、数组3使用移动构造函数" << std::endl;
			printMatrix(arrayInt3);

			arrayInt3.reSizeArray(5, 6);
			arrayInt3 = 8;
			std::cout << "9、交换数组2与3" << std::endl;
			std::cout << "交换前2与3：" << std::endl;
			printMatrix(arrayInt2);
			printMatrix(arrayInt3);
			std::swap(arrayInt3, arrayInt2);
			std::cout << "交换后2与3：" << std::endl;
			printMatrix(arrayInt2);
			printMatrix(arrayInt3);

			std::cout << "10、3自身移动赋值运算符" << std::endl;
			arrayInt3 = std::move(arrayInt3);
			printMatrix(arrayInt3);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();

	return 0;
}




