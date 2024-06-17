#include "CQMTabWidget.h"
#include "util/UtilFunc.h"

CQMTagWidget::CQMTagWidget(QWidget* parent) 
	:QTabWidget(parent)
{
	this->setWindowTitle(u8"��������ͳ��");
	this->setMinimumHeight(650);
	this->setMinimumWidth(850);

	//��ʼ��excelApp
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_excelApp = new QAxObject(qApp);
	m_excelApp->setControl("Excel.Application");
	m_excelApp->setProperty("Visible", true);
	m_workbooks = m_excelApp->querySubObject("Workbooks");

	//��ȡ��ǰ����·��
	std::string strAppPath, strAppName;
	mmrUtil::getAppPathAndName(strAppPath, strAppName);
	m_configPath = strAppPath + "config/colDef.json";
	std::string strErr = Json::json_from_file(m_configPath, m_jsonRoot);
	if (m_jsonRoot.IsNull() || !strErr.empty())
	{
		LOG_ERROR_PRINT("parse json file [%s] failed! error message is: %s.", m_configPath.c_str(), strErr.c_str());
		QMessageBox::warning(nullptr, "����", u8"���������ļ�ʧ��");
		return;
	}

	for (const auto iterTab : m_jsonRoot.ObjectRange())
	{
		QString strTitle = iterTab.first.c_str();
		QualityMangerWgt* tabWgt = new QualityMangerWgt(strTitle, m_configPath, m_jsonRoot, m_workbooks);
		this->addTab(tabWgt, strTitle);
		m_mapSubWidgets.insert(std::make_pair(iterTab.first, tabWgt));
	}
}

CQMTagWidget::~CQMTagWidget()
{
}


void CQMTagWidget::closeEvent(QCloseEvent *event)
{
	int ret = QMessageBox::question(this, u8"�رմ���",
		u8"ȷ��Ҫ�رմ��������д򿪵��ĵ����رա�",
		QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		for (auto& iterWidget : m_mapSubWidgets)
		{
			iterWidget.second->release();
		}
		m_excelApp->dynamicCall("Quit (void)");
		event->accept(); // ���ܹر��¼�
	}
	else
	{
		event->ignore(); // ���Թر��¼������ڱ��ִ�״̬
	}
}