#include "util/CLicenseObj.h"
#include <iostream>

using namespace mmrUtil;

CLicenseObj::CLicenseObj():
	m_licState(emLicenseState::LICENSE_NONE)
{
	std::cout << "hello obj!" << std::endl;
}

CLicenseObj::~CLicenseObj()
{

}

void CLicenseObj::parseLicenFile(const std::string strFilePath)
{

}

void CLicenseObj::updateLicenFile()
{
	return;
}


emLicenseState CLicenseObj::getLicenseState()
{
	switch (m_licState)
	{
		case emLicenseState::LICENSE_NONE:
		case emLicenseState::LICENSE_OVERDUE:
		{
			std::cout << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << "invalid license type " << static_cast<int>(m_licState) << std::endl;
		}
		break;
		case emLicenseState::LICENSE_OK:
		{
			updateLicenFile();
		}
		break;
		default:
		{
			std::cout << "[" << __FUNCTION__ << "][" << __LINE__ << "]" << "invalid license type " << static_cast<int>(m_licState) << std::endl;
		}
		break;
	}
	return m_licState;
}
