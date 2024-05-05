#ifndef COMMON_CVARIANT_HPP
#define COMMON_CVARIANT_HPP
#include "Common_def.h"
#include <iostream>
#include <string>
#include <map>

BEGINE_NAMESPACE(mmrUtil)


class CVariant//注意：string长度最大微255，大于部分将截断
{
public:
	enum class EM_DataType : uint16_t
	{
		VAR_TYPE_INVALID = 0,
		VAR_TYPE_BOOL,
		VAR_TYPE_INT32,
		VAR_TYPE_FLOAT,
		VAR_TYPE_DOUBLE,
		VAR_TYPE_STRING,

		VAR_TYPE_ARR_BOOL,//数组类型，暂不实现
		VAR_TYPE_ARR_INT32,
		VAR_TYPE_ARR_FLOAT,
		VAR_TYPE_ARR_DOUBLE,
		VAR_TYPE_ARR_STRING

	};

	CVariant()
		:type(EM_DataType::VAR_TYPE_INVALID) {
	}

	CVariant(bool bValue)
		:type(EM_DataType::VAR_TYPE_BOOL) {
		data.bValue = bValue;
	}

	CVariant(int32_t lValue)
		:type(EM_DataType::VAR_TYPE_INT32) {
		data.lValue = lValue;
	}

	CVariant(float fValue)
		:type(EM_DataType::VAR_TYPE_FLOAT) {
		data.fValue = fValue;
	}

	CVariant(double dValue)
		:type(EM_DataType::VAR_TYPE_DOUBLE) {
		data.dValue = dValue;
	}

	CVariant(const char* szValue)
		:type(EM_DataType::VAR_TYPE_STRING) {
		std::string temStr(szValue);
		if (temStr.length() < 255)
		{
			data.strValue = new std::string(std::move(temStr));
		}
		else
		{
			data.strValue = new std::string;
			data.strValue->append(temStr.begin(), temStr.begin() + 255);
		}
	}

	CVariant(const std::string& strValue)
		:type(EM_DataType::VAR_TYPE_STRING) {
		if (strValue.length() < 255)
		{
			data.strValue = new std::string(strValue);
		}
		else
		{
			data.strValue = new std::string;
			data.strValue->append(strValue.begin(), strValue.begin() + 255);
		}
			
	}

	CVariant(const CVariant& var)
	{
		*this = var;
	}

	//CVariant(CVariant&& var)
	//	:type(EM_DataType::VAR_TYPE_INVALID)
	//{
	//	*this = std::move(var);
	//}

	~CVariant()
	{
		resetCheck();
	};

	CVariant& operator = (const CVariant& var)
	{
		if (this != &var)//避免自赋值
		{
			resetCheck();
			this->type = var.type;
			switch (type)
			{
			case EM_DataType::VAR_TYPE_INVALID:
			case EM_DataType::VAR_TYPE_BOOL:
			case EM_DataType::VAR_TYPE_INT32:
			case EM_DataType::VAR_TYPE_FLOAT:
			case EM_DataType::VAR_TYPE_DOUBLE:
				this->data = var.data;
				break;
			case EM_DataType::VAR_TYPE_STRING:
			{
				data.strValue = new std::string(*(var.data.strValue));
			}
			break;
			default:
				this->type = EM_DataType::VAR_TYPE_INVALID;
				break;
			}
		}
		return *this;
	}

	bool operator == (const CVariant& var) 
	{
		if (this->type != var.type)
		{
			return false;
		}
		else
		{
			switch (type)
			{
			case EM_DataType::VAR_TYPE_STRING:
			{
				return *(data.strValue) == *(var.data.strValue);
			}
			break;
			case EM_DataType::VAR_TYPE_INVALID:
			case EM_DataType::VAR_TYPE_BOOL:
			case EM_DataType::VAR_TYPE_INT32:
			case EM_DataType::VAR_TYPE_FLOAT:
			case EM_DataType::VAR_TYPE_DOUBLE:
			default:
				return data.dValue == var.data.dValue;//注意！！！！待验证
				break;
			}
			return false;
		}
	}

	//CVariant operator = (CVariant&& var) 
	//{
	//	type = svar.type;
	//	svar.type = EM_DataType::VAR_TYPE_INVALID);
	//	data = var.data;
	//}

	//设置数据
	void setBoolData(bool bValue)
	{
		resetCheck();
		type = EM_DataType::VAR_TYPE_BOOL;
		data.bValue = bValue;
	}

	void setInt32Data(int32_t lValue)
	{
		resetCheck();
		type = EM_DataType::VAR_TYPE_INT32;
		data.lValue = lValue;
	}

	void setFloatData(float fValue)
	{
		resetCheck();
		type = EM_DataType::VAR_TYPE_FLOAT;
		data.fValue = fValue;
	}

	void setDoubleData(double dValue)
	{
		resetCheck();
		type = EM_DataType::VAR_TYPE_DOUBLE;
		data.dValue = dValue;
	}

	void setStringData(const std::string& strValue)
	{
		resetCheck();
		type = EM_DataType::VAR_TYPE_STRING;
		if (strValue.length() < 255)
		{
			data.strValue = new std::string(strValue);
		}
		else
		{
			data.strValue = new std::string;
			data.strValue->append(strValue.begin(), strValue.begin() + 255);
		}
	}

	//获取数据
	bool getBoolData(bool& bValue) const
	{
		if (EM_DataType::VAR_TYPE_BOOL != type)
			return false;
		bValue = data.bValue;
		return true;
	}

	bool getInt32Data(int32_t& lValue) const
	{
		if (EM_DataType::VAR_TYPE_INT32 != type)
			return false;
		lValue = data.lValue;
		return true;
	}

	bool getFloatData(float& fValue) const
	{
		if (EM_DataType::VAR_TYPE_FLOAT != type)
			return false;
		fValue = data.fValue;
		return true;
	}

	bool getDoubleData(double& dValue) const
	{
		if (EM_DataType::VAR_TYPE_DOUBLE != type)
			return false;
		dValue = data.dValue;
		return true;
	}

	bool getStringData(std::string& strValue) const
	{
		if (EM_DataType::VAR_TYPE_STRING != type)
			return false;
		strValue = *(data.strValue);
		return true;
	}

	//第二种get,赋值给引用有风险！！！！
	const bool& getBoolData() const
	{
		if (EM_DataType::VAR_TYPE_BOOL != type) 
		{
			static bool bTem = false;
			return bTem;
		}
		return data.bValue;
	}

	const int32_t& getInt32Data() const
	{
		if (EM_DataType::VAR_TYPE_INT32 != type) 
		{
			static int32_t lTem = 0;
			return lTem;
		}
		return data.lValue;
	}

	const float& getFloatData() const
	{
		if (EM_DataType::VAR_TYPE_FLOAT != type) 
		{
			static float fTem = 0.0;
			return fTem;
		}
		return data.fValue;
	}

	const double& getDoubleData() const
	{
		if (EM_DataType::VAR_TYPE_DOUBLE != type)
		{
			static double dTem = 0.0;
			return dTem;
		}
		return data.dValue;
	}

	const std::string& getStringData() const
	{
		if (EM_DataType::VAR_TYPE_STRING != type) 
		{
			static std::string retStr = "";
			return retStr;
		}
		else
		{
			return *(data.strValue);
		}
	}

	EM_DataType getType() { return type; }

	const EM_DataType getType() const { return type; }
private:
	void resetCheck()
	{
		switch (type)
		{
		case EM_DataType::VAR_TYPE_INVALID:
		case EM_DataType::VAR_TYPE_BOOL:
		case EM_DataType::VAR_TYPE_INT32:
		case EM_DataType::VAR_TYPE_FLOAT:
		case EM_DataType::VAR_TYPE_DOUBLE:
			break;
		case EM_DataType::VAR_TYPE_STRING:
		{
			delete data.strValue;
		}
		break;
		default:
			break;
		}
	}

private:
	union unData
	{
		//void* vPtr;
		bool bValue;
		int32_t lValue;
		float fValue;
		double dValue;
		std::string* strValue;
	};

	EM_DataType type = EM_DataType::VAR_TYPE_INVALID;
	unData data;
};

//数据解析类
class CVarDatas
{
	//要不要考虑大小端问题？？
	//目前最多支持256个参数
	//改成vector<char>防止内存泄漏
	//string参数长度目前不能超过256字节
public:
	CVarDatas()	
		:m_pMapVars(std::unique_ptr<std::map<std::string, CVariant>>(new std::map<std::string, CVariant>))
	{
	}

	CVarDatas(const CVarDatas& rhs)
		:m_pMapVars(std::unique_ptr<std::map<std::string, CVariant>>(new std::map<std::string, CVariant>((*rhs.m_pMapVars.get()))))
	{
	}

	CVarDatas(CVarDatas&& rhs)
		:m_pMapVars(std::move(rhs.m_pMapVars))
	{
	}


	~CVarDatas() = default;

	CVarDatas& operator = (const CVarDatas& rhs) 
	{
		m_pMapVars = std::unique_ptr<std::map<std::string, CVariant>>(new std::map<std::string, CVariant>((*rhs.m_pMapVars.get())));
	}

	CVarDatas& operator = (CVarDatas&& rhs)
	{
		m_pMapVars = std::move(rhs.m_pMapVars);
	}

	CVariant& operator [](std::string strKey) 
	{
		return (*m_pMapVars)[strKey];
	}

	const CVariant& operator [](std::string strKey) const
	{
		auto iterVar = (*m_pMapVars).find(strKey);
		if (iterVar != (*m_pMapVars).end())
		{
			return iterVar->second;
		}
		else
		{
			std::invalid_argument(std::string("invalid key " + strKey).c_str());
		}
	}
private:
	std::unique_ptr<std::map<std::string, CVariant>> m_pMapVars;//变量数量，不能超过255个
};



END_NAMESPACE(mmrUtil)

#endif


