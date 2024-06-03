#include <iostream>
#include <string>


#include "CLoggerCtrl.h"


mmrComp::CLoggerCtrl::CLoggerCtrl()
{

}

mmrComp::CLoggerCtrl::~CLoggerCtrl()
{

}

static const char logger_options[] = R"(
  -vl|--view logger         Viewing all component logger settings
  -sl|--set logger          set component logger
  -q|--quit                 quit
)";

void print_log_opt()
{
	printf("Options:\n%s\n", logger_options);
}

void mmrComp::CLoggerCtrl::loop()
{
	print_log_opt();
	while (true)
	{
		std::string strCmd;
		printf("logger> ");
		std::getline(std::cin, strCmd);

		auto pos = strCmd.find("-vl");
		if (strCmd.find("-vl") == 0)
		{
			printf("  ComponentName\t\tLogLevel \n");
			for (const auto& iterLogger : m_mapCompLogger)
			{
				auto LoggerPtr = iterLogger.second.lock();
				if (LoggerPtr)
					printf("  %s\t\t%d \n", iterLogger.first.c_str(), static_cast<int>(LoggerPtr->logLevel));
				else
					printf("  %s\t\t-1 \n", iterLogger.first.c_str());
			}
		}
		else if (strCmd.find("-sl") == 0)
		{
			printf("set component log level like [ComponentName]:[level].level [-1](log_off) use symbol [/].\n");
			printf("this modification is temporary.\n");
			
			printf("logger>-sl>");
			std::getline(std::cin, strCmd);
			auto pos = strCmd.find(':');
			if (pos > 0 && pos == (strCmd.size() - 2))//暂时不支持设置关闭
			{
				std::string compName(strCmd.begin(), strCmd.begin() + pos);
				auto iterLogger = m_mapCompLogger.find(compName);
				if (iterLogger != m_mapCompLogger.end())
				{
					auto LoggerPtr = iterLogger->second.lock();
					if (LoggerPtr)
					{
						int32_t level = static_cast<int8_t>(strCmd[pos + 1]) - 0x30 ;
						if (level >= -1 && level <= 5) //暂时不支持设置关闭
						{
							LoggerPtr->logLevel = static_cast<mmrUtil::emLogLevel>(level);
							printf("%s log level set %d success.\n", compName.c_str(), level);
							continue;
						}
					}
				}
			}
			printf("unknown command! you can input [-vl] to view all component info.\n");
		}
		else if (strCmd == "-q")
		{
			printf("quit log setting \n");
			break;
		}
		else
		{
			printf("invalid command[%s]!\n", strCmd.c_str());
			print_log_opt();
		}
	}
}

