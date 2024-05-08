#include "Common_def.h"
#include "util/CVarDatas.hpp"
#include <iostream>


int main()
{
	for (uint32_t i = 0 ; i < 10000; ++i) 
	{
		try
		{
			{
				mmrUtil::CVariant var;
				var.setBoolData(true);
				std::cout << "bool data " << var.getBoolData() << std::endl;
				var.setCharData('a');
				std::cout << "Char data " << var.getCharData() << std::endl;
				var.setInt32Data(0xffffff);
				std::cout << "Int32 data " << var.getInt32Data() << std::endl;
				var.setUint32Data(0xffffff);
				std::cout << "Uint data " << var.getUint32Data() << std::endl;
				var.setInt64Data(0xffffff);
				std::cout << "Int64 data " << var.getInt64Data() << std::endl;
				var.setUint64Data(0xffffff);
				std::cout << "UInt64 data " << var.getUint64Data() << std::endl;
				var.setFloatData(0xffffff);
				std::cout << "Float data " << var.getFloatData() << std::endl;
				var.setDoubleData(0xffffff);
				std::cout << "Double data " << var.getDoubleData() << std::endl;
				var.setStringData("hello");
				std::cout << "String data " << var.getStringData() << std::endl;
				var.setByteArrayData({0x00,0x01,0x02});
				auto byteArr =  var.getByteArrayData();

				mmrUtil::CVariant var2(var);

				mmrUtil::CVariant var3(std::move(var));

				mmrUtil::CVariant var4 = std::move(var2);
			}


			{
				mmrUtil::CVarDatas vData;
				vData.addVar("int", int32_t(0xffffffff));
				vData.addVar("string", "hello!");
				auto allKey = vData.getAllKey();
				std::cout << "contain key int " << vData.isContain("int") << std::endl;
				std::cout << "contain key other " << vData.isContain("other") << std::endl;
				std::cout << "int data is " << vData.getVar("int").getInt32Data() << std::endl;
				std::cout << "string data is " << vData.getVar("string").getStringData() << std::endl;

				mmrUtil::CVarDatas vData2(vData);
				std::cout << "int data is " << vData2.getVar("int").getInt32Data() << std::endl;
				std::cout << "string data is " << vData2.getVar("string").getStringData() << std::endl;

				mmrUtil::CVarDatas vData3(std::move(vData2));
				std::cout << "int data is " << vData3.getVar("int").getInt32Data() << std::endl;
				std::cout << "string data is " << vData3.getVar("string").getStringData() << std::endl;

				mmrUtil::CVarDatas vData4  = std::move(vData);
				std::cout << "int data is " << vData4.getVar("int").getInt32Data() << std::endl;
				std::cout << "string data is " << vData4.getVar("string").getStringData() << std::endl;

				mmrUtil::CVarDatas vData5 = vData4;
				std::cout << "int data is " << vData5.getVar("int").getInt32Data() << std::endl;
				std::cout << "string data is " << vData5.getVar("string").getStringData() << std::endl;
			}
			std::cout << "cycle time " << i << std::endl;
				
		}
		catch (std::exception& e)
		{
			std::cout << "exception info is " << e.what()<<std::endl;
		}
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;

}
