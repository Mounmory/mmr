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
	QualityMangerWgt(QString& strTitle, const std::string& jsonFilePath, Json::Value& jsonRoot,QWidget* parent = nullptr);
	~QualityMangerWgt();


public slots:
	void slot_onClickDeleteFile();

	void slot_onClickSlectFile();

	void slot_onFileSelectChanged();

	void slot_onClickUpdateTable();

	void slot_onClickSaveTable();

	void slot_onCellChanged(int row, int column);
protected:
	void closeEvent(QCloseEvent *event) override;

private:
	void saveJson();

	bool openFile(QString strPath);
private:
	QAxObject* m_excelApp;
	QAxObject* m_workbooks;
	
	std::map<QString, QAxObject*> m_mapAllFile;
	QAxObject* m_currentFile = nullptr;

	std::atomic_bool m_bChanging;//表格是否正在添加行等操作

	std::map<int, std::pair<std::string,std::string>> m_mapColName;//<列索引,<列名称,列位置>>

	const std::string& m_jsonFilePath;
	QString m_strTitle;//当前Tab页标题
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
