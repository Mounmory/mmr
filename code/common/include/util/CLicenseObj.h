#ifndef CLICENSEOBJ_H
#define CLICENSEOBJ_H
#include "Common_def.h"
#include "UtilCommon.h"
#include <fstream>
#include <string>
#include <vector>

BEGINE_NAMESPACE(mmrUtil)

enum class emLicenseState : uint8_t
{
	LICENSE_OK = 0,
	LICENSE_NONE,
	LICENSE_OVERDUE
};

class COMMON_CLASS_API CLicenseObj
{
public:
	CLicenseObj();
	virtual ~CLicenseObj();

	virtual void parseLicenFile(const std::string strFilePath);

	virtual void updateLicenFile();

	emLicenseState getLicenseState();

private:
	std::fstream m_fstream;
	std::string m_fileFullPath;
	std::vector<std::string> m_vecText;
	emLicenseState m_licState;
};


END_NAMESPACE(mmrUtil)

#endif