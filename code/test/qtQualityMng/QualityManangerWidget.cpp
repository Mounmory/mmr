#include "QualityManangerWidget.h"


QualityMangerWgt::QualityMangerWgt(QWidget* parent/* = nullptr*/)
	:QWidget(parent)
{
	this->setWindowTitle(u8"质量问题统计");
	this->setMinimumHeight(600);
	this->setMinimumWidth(800);

	//初始化excelApp
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_excelApp = new QAxObject(qApp);
	m_excelApp->setControl("Excel.Application");
	m_excelApp->setProperty("Visible", true);
	m_workbooks = m_excelApp->querySubObject("Workbooks");

	m_mainLayout = new QGridLayout(this);

	//删除选中行按钮
	m_btnDeleRow = new QPushButton(u8"删除选中行");
	m_mainLayout->addWidget(m_btnDeleRow, 0, 0, 1, 2);

	//添加文件按钮
	m_btnOpenExcel = new QPushButton(u8"添加Excel文件");
	connect(m_btnOpenExcel, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickSlectFile);
	m_mainLayout->addWidget(m_btnOpenExcel, 0, 2, 1, 2);

	//保存统计数据按钮
	m_btnSaveExcel = new QPushButton(u8"保存表格内容");
	connect(m_btnSaveExcel, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickSaveTable);
	m_mainLayout->addWidget(m_btnSaveExcel, 0, 14, 1, 2);

	m_tableFileList = new QTableWidget;
	//表格选中相应
	connect(m_tableFileList, &QTableWidget::itemSelectionChanged, this, &QualityMangerWgt::slot_onFileSelectChanged);

	m_tableFileList->setColumnCount(2);
	m_tableFileList->setRowCount(0); // 初始时不添加任何行
	m_tableFileList->setSelectionMode(QAbstractItemView::SingleSelection); // 设置选择模式为单行选中
	m_tableFileList->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置选择行为为选择整行

																		  // 设置列名称
	m_tableFileList->setHorizontalHeaderLabels({ u8"名称", u8"路径" });
	// 设置列宽（可选）
	m_tableFileList->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
	m_tableFileList->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
	m_tableFileList->setColumnWidth(0, 100);
	m_tableFileList->setColumnWidth(1, 300);

	m_mainLayout->addWidget(m_tableFileList, 1, 0, 4, 8);


	m_tableSheetList = new QTableWidget;
	connect(m_tableSheetList, &QTableWidget::cellChanged, this, &QualityMangerWgt::slot_onCellChanged);

	m_tableSheetList->setColumnCount(3);
	m_tableSheetList->setRowCount(0); // 初始时不添加任何行
	m_tableSheetList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
																		 // 设置列名称
	m_tableSheetList->setHorizontalHeaderLabels({ u8"表单名称", u8"表格位置" , u8"值" });
	// 设置列宽（可选）
	m_tableSheetList->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
	m_tableSheetList->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
	m_tableSheetList->setColumnWidth(0, 100);
	m_tableSheetList->setColumnWidth(1, 100);
	m_tableSheetList->setColumnWidth(2, 150);
	m_mainLayout->addWidget(m_tableSheetList, 1, 8, 4, 8);
	

	this->setLayout(m_mainLayout);
}

QualityMangerWgt::~QualityMangerWgt()
{

}

void QualityMangerWgt::slot_onClickSlectFile()
{
	QString strFilePathName = QFileDialog::getOpenFileName(this, QStringLiteral("选择Excel文件"), "", tr("Exel file(*.xls *.xlsx)"));
	if (strFilePathName.isNull()) 
	{
		return;
	}
	strFilePathName = QDir::toNativeSeparators(strFilePathName);

	if (m_mapAllFile.count(strFilePathName) != 0)
	{
		QMessageBox::warning(this, u8"重复添加", QString(u8"文件 %1 已经添加过了！").arg(strFilePathName));
		return;
	}

	LOG_INFO("add excel file: %s", strFilePathName.toStdString().c_str());
	m_workbooks->dynamicCall("Open (const QString&)", strFilePathName);
	QAxObject *workbook = m_excelApp->querySubObject("ActiveWorkBook");
	if (workbook)
	{
		auto pos = strFilePathName.lastIndexOf('\\');
		if (pos != -1)
		{
			QString fileName = strFilePathName.mid(pos + 1);
			int rowIndex = m_tableFileList->rowCount();
			m_tableFileList->insertRow(rowIndex);
			QTableWidgetItem *nameItem = new QTableWidgetItem(fileName);
			QTableWidgetItem *pathItem = new QTableWidgetItem(strFilePathName);
			m_tableFileList->setItem(rowIndex, 0, nameItem);
			m_tableFileList->setItem(rowIndex, 1, pathItem);
			m_mapAllFile.insert(std::make_pair(strFilePathName, workbook));
		}
	}

}

void QualityMangerWgt::slot_onFileSelectChanged()
{
	QList<QTableWidgetItem*> selectedItems = m_tableFileList->selectedItems();
	if (selectedItems.isEmpty()) {
		return;
	}

	// 假设我们只对整行选中感兴趣，并且只处理第一行选中的情况（通常是用户通过点击行号选择的整行）
	QTableWidgetItem *firstSelectedItem = selectedItems.first();
	int row = firstSelectedItem->row(); // 获取选中项所在的行号

	// 获取这一行的所有值
	QTableWidgetItem *item = m_tableFileList->item(row, 1);
	if (item) 
	{ // 确保项存在
		QString value = item->text(); // 获取项的值（文本）
		auto iterWork = m_mapAllFile.find(value);
		if (iterWork != m_mapAllFile.end())
		{
			m_currentFile = iterWork->second;
			QAxObject *sheets = m_currentFile->querySubObject("Sheets");
			int sheetNum = sheets->property("Count").toInt();
			m_tableSheetList->clear();
			for (int i = 0 ; i < sheetNum; ++i)
			{
				QAxObject *worksheet = m_currentFile->querySubObject("Worksheets(int)", i + 1);
				m_tableSheetList->insertRow(i);
				QString strSheetName = worksheet->property("Name").toString();
				QTableWidgetItem *sheetName = new QTableWidgetItem(strSheetName);
				QTableWidgetItem *sheetSelect = new QTableWidgetItem();
				QTableWidgetItem *selectValue = new QTableWidgetItem();
				m_tableSheetList->setItem(i, 0, sheetName);
				m_tableSheetList->setItem(i, 1, sheetSelect);
				m_tableSheetList->setItem(i, 2, selectValue);
			}
		}
	}

}

void QualityMangerWgt::slot_onClickSaveTable()
{
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Excel Files (*.xlsx)"));
	if (filePath.isEmpty()) {
		// 用户取消了操作，不做任何事情
		return;
	}
	QAxObject *workbook = m_workbooks->querySubObject("Add()");

	QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
	int rowCount = m_tableSheetList->rowCount();
	//int colCount = m_tableSheetList->colorCount();
	QAxObject *cell = worksheet->querySubObject("Cells(int, int)", 1, 1);
	cell->dynamicCall("SetValue(const QVariant&)", u8"日期");
	cell = worksheet->querySubObject("Cells(int, int)", 1, 2);
	cell->dynamicCall("SetValue(const QVariant&)", u8"数量");
	for (int i = 0 ; i < rowCount ; ++i)
	{
		QTableWidgetItem *itemName = m_tableSheetList->item(i, 0);
		QTableWidgetItem *itemValue = m_tableSheetList->item(i, 2);
		cell = worksheet->querySubObject("Cells(int, int)", i + 2, 1);
		cell->dynamicCall("SetValue(const QVariant&)", itemName->text());
		cell = worksheet->querySubObject("Cells(int, int)", i + 2, 2);
		cell->dynamicCall("SetValue(const QVariant&)", itemValue->text());
	}

	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
	//workbook->dynamicCall("Close (Boolean)", false);
	//workbook->dynamicCall("Release (void)");
}

void QualityMangerWgt::slot_onCellChanged(int row, int column)
{
	if (column != 1)//仅处理第二列
	{
		return;
	}

	QTableWidgetItem *itemPos = m_tableSheetList->item(row, column);
	if (itemPos)
	{
		// 获取并打印编辑完成的值
		QString value = itemPos->text();
		QAxObject *worksheet = m_currentFile->querySubObject("Worksheets(int)", row + 1);
		if (worksheet)
		{
			QAxObject *range = worksheet->querySubObject("Range(const QString&)", value);
			if (range)
			{
				QVariant var = range->dynamicCall("Value");
				QTableWidgetItem *itemValue = m_tableSheetList->item(row, column + 1);
				itemValue->setText(var.toString());
			}
		}
	}
}

void QualityMangerWgt::closeEvent(QCloseEvent *event)
{
	int ret = QMessageBox::question(this, u8"关闭窗口",
		u8"确定要关闭窗口吗？",
		QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes) 
	{

		for (const auto& iterBook : m_mapAllFile)
		{
			iterBook.second->dynamicCall("Close (Boolean)", false);
		}
		m_excelApp->dynamicCall("Quit (void)");
		event->accept(); // 接受关闭事件
	}
	else 
	{
		event->ignore(); // 忽略关闭事件，窗口保持打开状态
	}
}
