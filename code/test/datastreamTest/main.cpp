#include "Common.h"
#include "util/CDataStream.h"
#include <iostream>


struct Mydata :public MmrCommon::IDealByStream 
{
	Mydata() = default;
	Mydata(int n, float f) 
		:nValue(n)
		,fValue(f)
	{
	}
	int nValue;
	float fValue;

	virtual void marshal(MmrCommon::CDataStream& dataStream) const override 
	{
		dataStream << nValue;
		dataStream << fValue;
	}

	virtual void unmarshal(MmrCommon::CDataStream& dataStream) override 
	{
		dataStream >> nValue;
		dataStream >> fValue;
	}
};





int main()
{
	MmrCommon::CDataStream dataMarshal(MmrCommon::emEndian::BIG);

	{
		Mydata dataTest = { 5,2.5 };
		std::cout << "origin data is " << dataTest.nValue << " " << dataTest.fValue << std::endl;
		dataTest.marshal(dataMarshal);
	}

	//复制数据到byte
	char transData[1024];
	int byteLen = dataMarshal.size();
	memcpy(transData, &dataMarshal[0], byteLen);

	MmrCommon::CDataStream dataUnmarshal(transData, byteLen, MmrCommon::emEndian::BIG);
	{
		Mydata dataTrans;
		dataTrans.unmarshal(dataUnmarshal);
		std::cout << "unmarshal data is " << dataTrans.nValue << " " << dataTrans.fValue << std::endl;
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
