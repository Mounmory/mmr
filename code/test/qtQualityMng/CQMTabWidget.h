#ifndef CQMTABWIDGET_H
#define CQMTABWIDGET_H
#include "QualityManangerWidget.h"
#include <QTabWidget>


class CQMTagWidget:public QTabWidget
{
	Q_OBJECT
public:
	CQMTagWidget(QWidget* parent = nullptr);
	~CQMTagWidget();

protected:
	virtual void closeEvent(QCloseEvent *event) override;

private:
	Json::Value m_jsonRoot;
	std::string m_configPath;

	QAxObject* m_excelApp;
	QAxObject* m_workbooks;//所有的excel表格

	std::map<std::string, QualityMangerWgt*>m_mapSubWidgets;
};


#endif