#include "Common_def.h"
#include "QualityManangerWidget.h"
#include "CQMTabWidget.h"



/*
QT导出excel
https://blog.csdn.net/wuyuewei/article/details/134329533
https://blog.csdn.net/hitzsf/article/details/117174007
*/



int main(int argc, char *argv[])
{

#ifdef OS_WIN
	QApplication a(argc, argv);
	logInstancePtr->start();

	CQMTagWidget tabWidget;
	tabWidget.show();
	return a.exec();

	//CoInitializeEx(NULL, COINIT_MULTITHREADED);
	////QAxObject excel("Excel.Application");
	////excel.setProperty("Visible", true);
	////QAxObject *workbooks = excel.querySubObject("Workbooks");
	////QAxObject *workbook = workbooks->querySubObject("Add()");

	////QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
	////// 写入数据到单元格
	////QAxObject *cell = worksheet->querySubObject("Cells(int, int)", 1, 1);
	////cell->dynamicCall("SetValue(const QVariant&)", "Hello");
	////// 保存工作簿
	//////workbook->dynamicCall("SaveAs(const QString&)D:/example.xlsx");
	////workbook->dynamicCall("SaveAs(example)");//保存到文档下面
	////// 关闭Excel应用
	////excel.dynamicCall("Quit()");

	//QAxObject *excel = new QAxObject(qApp);

	//excel->setControl("Excel.Application");
	//excel->setProperty("Visible", false);

	//QAxObject *workbooks = excel->querySubObject("Workbooks");
	//workbooks->dynamicCall("Open (const QString&)", QString(u8"D:/中文.xlsx"));

	//QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
	//QAxObject *sheets = workbook->querySubObject("Sheets");
	//int sheetNum = sheets->property("Count").toInt();
	//QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 3);
	//auto sheetName = worksheet->property("Name").toString().toStdString();
	//qDebug() << "sheet name " << sheetName.c_str();
	//QAxObject *range = worksheet->querySubObject("Range(const QString&)", "A2:E4");

	//QVariant var = range->dynamicCall("Value");
	//QVariantList list = var.toList();

	//for (const QVariant& item : list) {
	//	QVariantList rowData = item.toList();
	//	for (const QVariant& cell : rowData) {
	//		qDebug() << cell.toString();
	//	}
	//}
	//QString nativeDir = QDir::toNativeSeparators(u8"D:/中文1.xlsx");
	//workbook->dynamicCall("SaveAs(const QString &)", nativeDir);

	//workbook->dynamicCall("Close (Boolean)", false);
	//excel->dynamicCall("Quit (void)");

	////range->release();
	////worksheet->release();
	////workbook->release();
	////workbooks->release();

	////excel->release();
	//delete excel;

#else
	QApplication a(argc, argv);
	QWidget w;
	w.setWindowTitle("qtTest");
	w.setFixedSize(300, 200);
	w.show();
	return a.exec();
#endif // OS_WIN
}

