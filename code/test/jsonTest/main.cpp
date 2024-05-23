#include "Common_def.h"
#include "util/json.hpp"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;
using Json::Value;

#ifdef OS_WIN
std::string strJsonIn = "D:/VMs/jsonTestIn.json";
std::string strJsonOut = "D:/VMs/jsonTestOut.json";
#else
std::string strJsonIn = "/media/sf_VMs/jsonTestIn.json";
std::string strJsonOut = "/media/sf_VMs/jsonTestOut.json";
#endif // OS_WIN



/**
*  Simple testing program that takes an input
*  JSON file, loads it, and then dumps it the
*  given output file.
*/
int main()
{
	Value obj1;
	
	std::string errStr = Json::json_from_file(strJsonIn, obj1);

	if (!errStr.empty()) 
	{
		std::cout << "error message :" << errStr << std::endl;
		return -1;
	}

	cout<< "obj1 before move\n" << obj1.dump() << endl;

	std::cout << "dump json \n" << obj1.dump() << std::endl;

	Value obj2 = std::move(obj1);
	cout << "obj2 after move\n" << obj2.dump() << endl;
	cout << "obj1 after move\n" << obj1.dump() << endl;
	obj1 = std::move(obj2);
	cout << "obj2 after move\n" << obj2.dump() << endl;
	cout << "obj1 after move\n" << obj1.dump() << endl;

	ofstream output1;
	output1.open(strJsonIn, std::ofstream::out);
	if (output1.is_open())
	{
		output1 << obj1.dump() << std::endl;
	}

	//дJson
	Value Obj = Json::Value();
	Value Obj1 = Json::Value();
	Value Obj11 = Json::Value();

	Obj11["para1"] = 1;
	Obj1["ComponentDemo"] = Obj11;
	Obj["Components"].append(Obj1);
	//Obj["Key1"] = 1.023;
	//Obj["Key2"] = "Value";

	//JSON Obj2 = mmrUtil::Object();
	//Obj2["Key3"] = 1;
	//Obj2["Key4"] = "hello!";
	//Obj2["Key4"] = 3.140909077;

	//// Nested Object
	//Obj["Key6"] = std::move(Obj2);

	//if (Obj.hasKey("Key1"))
	//{
	//	std::cout <<  "Key1 value is "<< Obj.at("Key1").ToFloat()<<std::endl;
	//}


	// Dump Obj to a string.
	cout << Obj.dump() << endl;

	ofstream output;
	output.open(strJsonOut,std::ofstream::out);
	if (output.is_open())
	{
		output << Obj.dump() << std::endl;
		output.close();
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
