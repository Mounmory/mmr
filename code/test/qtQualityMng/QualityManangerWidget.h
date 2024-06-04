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

#include "util/Clogger.h"

#ifdef OS_WIN
#include <QAxObject>
#include "Windows.h"
#endif // OS_WIN

class QualityMangerWgt :public QWidget 
{
	Q_OBJECT
public:
	QualityMangerWgt(QWidget* parent = nullptr);
	~QualityMangerWgt();


public slots:
	void slot_onClickSlectFile();

	void slot_onFileSelectChanged();

	void slot_onClickSaveTable();

	void slot_onCellChanged(int row, int column);
protected:
	void closeEvent(QCloseEvent *event) override;
private:
	QAxObject* m_excelApp;
	QAxObject* m_workbooks;
	
	std::map<QString, QAxObject*> m_mapAllFile;
	QAxObject* m_currentFile = nullptr;
private:
	QPushButton* m_btnDeleRow;
	QPushButton* m_btnOpenExcel;
	QPushButton* m_btnSaveExcel;

	QTableWidget *m_tableFileList;
	QTableWidget *m_tableSheetList;

	QGridLayout* m_mainLayout;
};


#endif // !QUALITYMANAGERWIDGET_H
