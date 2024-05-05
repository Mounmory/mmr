#include "Common_def.h"
#include "util/json.hpp"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;
using mmrUtil::JSON;

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
	string inFile = strJsonIn;
	string contents;
	ifstream input(inFile);
	if (!input.is_open()) 
	{
		std::cout << "open file failed!" << std::endl;
	}
	input.seekg(0, ios::end);
	contents.reserve(input.tellg());
	input.seekg(0, ios::beg);

	contents.assign((istreambuf_iterator<char>(input)),
		istreambuf_iterator<char>());

	JSON obj1 = JSON::Load(contents);

	cout<< "obj1 befor move\n" << obj1 << endl;

	JSON obj2 = std::move(obj1);
	cout << "obj2 after move\n" << obj2 << endl;
	cout << "obj1 after move\n" << obj1 << endl;
	obj1 = std::move(obj2);
	cout << "obj2 after move\n" << obj2 << endl;
	cout << "obj1 after move\n" << obj1 << endl;

	ofstream output1;
	output1.open(inFile, std::ofstream::out);
	if (output1.is_open())
	{
		output1 << obj1 << std::endl;
	}

	//дJson
	JSON Obj = mmrUtil::Object();
	Obj["Key1"] = 1.023;
	Obj["Key2"] = "Value";

	JSON Obj2 = mmrUtil::Object();
	Obj2["Key3"] = 1;
	Obj2["Key4"] = "hello!";
	Obj2["Key4"] = 3.140909077;

	// Nested Object
	Obj["Key6"] = std::move(Obj2);

	if (Obj.hasKey("Key1"))
	{
		std::cout <<  "Key1 value is "<< Obj.at("Key1").ToFloat()<<std::endl;
	}


	// Dump Obj to a string.
	cout << Obj << endl;

	ofstream output;
	output.open(strJsonOut,std::ofstream::out);
	if (output.is_open())
	{
		output << Obj << std::endl;
		output.close();
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
