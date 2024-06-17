#include "CQMTabWidget.h"
#include "util/UtilFunc.h"

CQMTagWidget::CQMTagWidget(QWidget* parent) 
	:QTabWidget(parent)
{
	this->setWindowTitle(u8"质量问题统计");
	this->setMinimumHeight(650);
	this->setMinimumWidth(850);

	//初始化excelApp
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_excelApp = new QAxObject(qApp);
	m_excelApp->setControl("Excel.Application");
	m_excelApp->setProperty("Visible", true);
	m_workbooks = m_excelApp->querySubObject("Workbooks");

	//获取当前进程路径
	std::string strAppPath, strAppName;
	mmrUtil::getAppPathAndName(strAppPath, strAppName);
	m_configPath = strAppPath + "config/colDef.json";
	std::string strErr = Json::json_from_file(m_configPath, m_jsonRoot);
	if (m_jsonRoot.IsNull() || !strErr.empty())
	{
		LOG_ERROR_PRINT("parse json file [%s] failed! error message is: %s.", m_configPath.c_str(), strErr.c_str());
		QMessageBox::warning(nullptr, "错误", u8"解析配置文件失败");
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
	int ret = QMessageBox::question(this, u8"关闭窗口",
		u8"确定要关闭窗口吗？所有打开的文档将关闭。",
		QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		for (auto& iterWidget : m_mapSubWidgets)
		{
			iterWidget.second->release();
		}
		m_excelApp->dynamicCall("Quit (void)");
		event->accept(); // 接受关闭事件
	}
	else
	{
		event->ignore(); // 忽略关闭事件，窗口保持打开状态
	}
}