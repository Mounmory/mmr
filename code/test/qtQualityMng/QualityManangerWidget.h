#ifndef QUALITYMANAGERWIDGET_H
#define QUALITYMANAGERWIDGET_H
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QFile>
#include <QPushButton>
#include <QTableWidget>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QEvent>
#include "qevent.h"

#include <set>
#include <map>
#include <string>
#include <fstream>
#include <atomic>

#include "util/Clogger.h"
#include "util/json.hpp"

#ifdef OS_WIN
#include <QAxObject>
#include "Windows.h"
#include <corecrt_io.h>	//_access头文件
#endif // OS_WIN


class AtomicLock 
{
public:
	AtomicLock(std::atomic_bool& bAt)
	:m_ref(bAt)
	{
		m_ref.store(true);
	}
	~AtomicLock() 
	{
		m_ref.store(false);
	}
private:
	std::atomic_bool& m_ref;
};
class QualityMangerWgt :public QWidget 
{
	Q_OBJECT
public:
	QualityMangerWgt(const QString& strTitle, const std::string& jsonFilePath, Json::Value& jsonRoot, QAxObject* axBooks, QWidget* parent = nullptr);
	~QualityMangerWgt();

	void release();

public slots:
	/*移除选中文档*/
	void slot_onClickDeleteFile();

	/*添加文件按钮*/
	void slot_onClickAddFile();

	/*左侧列表框控件选择变化*/
	void slot_onFileDoubleClicked(int row, int column);

	/*更新表格数据*/
	void slot_onClickUpdateTable();

	/*保存表格数据到EXCEL*/
	void slot_onClickSaveTable();



private:
	void saveJson();

private:
	struct stCurentFile 
	{
		QString strFileFullPath;
		QAxObject* ptrFileHandle = nullptr;

		void clear() 
		{
			strFileFullPath.clear();
			if (ptrFileHandle)
			{
				ptrFileHandle->dynamicCall("Close (Boolean)", false);//关闭不保存
				ptrFileHandle->dynamicCall("Release (void)");
				ptrFileHandle = nullptr;
			}
		}

		bool isEmpty() 
		{
			return strFileFullPath.isEmpty() && nullptr == ptrFileHandle;
		}
	};

	QAxObject* m_workbooks;//所有的excel表格

	//当前打开的
	stCurentFile m_ptrFileHandle;

	std::map<QString, QString> m_mapAllFile;//<全路径，文件名>
	
	std::atomic_bool m_bChanging;//表格是否正在添加行等操作

	std::map<int, std::pair<std::string,std::string>> m_mapColName;//<列索引,<列名称,列位置>>

	QString m_strTitle;//当前Tab页标题

	const std::string& m_jsonFilePath;
	
	Json::Value& m_jsonRoot;//根Json
private:
	QPushButton* m_btnDeleRow;
	QPushButton* m_btnOpenExcel;
	QPushButton* m_btnUpdate;
	QPushButton* m_btnSaveExcel;

	QTableWidget *m_tableFileList;
	QTableWidget *m_tableSheetList;

	QGridLayout* m_mainLayout;
};


#endif // !QUALITYMANAGERWIDGET_H
