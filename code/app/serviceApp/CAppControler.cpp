#include <iostream>
#include "CAppControler.h"
#include "core/include/CCompFramework.h"


static const char detail_options[] = R"(
  -h|--help                 Print this information
  -l|--log                  Component logger settings and viewing
  -q|--quit                 quit
)";

void print_help() 
{
	printf("Options:\n%s\n", detail_options);
}

CAppControler::CAppControler()
{

}

CAppControler::~CAppControler()
{

}

void CAppControler::run()
{
	if (CoreFrameworkIns->start())
	{
		print_help();

		while (true)
		{
			std::string strCmd;
			printf("> ");
			std::getline(std::cin, strCmd);

			if(strCmd == "-h" )
			{
				print_help();
			}
			else if (strCmd == "-l")
			{
				CoreFrameworkIns->loggerCtrlLoop();
			}
			else if (strCmd == "-q")
			{
				CoreFrameworkIns->stop();
				printf("app stopped!\n");
				break;
			}
			else
			{
				printf("invalid command[%s]!\n", strCmd.c_str());
				print_help();
			}
		}

	}
	else 
	{
		std::cout << "Core framework start failed!\n";
	}




	
}
