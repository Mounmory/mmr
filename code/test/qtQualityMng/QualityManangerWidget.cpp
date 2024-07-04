#include "QualityManangerWidget.h"
#include "util/UtilFunc.h"


QualityMangerWgt::QualityMangerWgt(const QString& strTitle, const std::string& jsonFilePath, Json::Value& jsonRoot, QAxObject* axBooks, QWidget* parent/* = nullptr*/)
	: QWidget(parent)
	, m_strTitle(strTitle)
	, m_jsonFilePath(jsonFilePath)
	, m_jsonRoot(jsonRoot)
	, m_workbooks(axBooks)
	, m_bChanging(false)
{
	//this->setWindowTitle(u8"质量问题统计");
	this->setMinimumHeight(600);
	this->setMinimumWidth(800);

	m_mainLayout = new QGridLayout(this);

	//删除选中行按钮
	m_btnDeleRow = new QPushButton(u8"移除选中文档");
	connect(m_btnDeleRow, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickDeleteFile);
	m_mainLayout->addWidget(m_btnDeleRow, 0, 0, 1, 2);

	//添加文件按钮
	m_btnOpenExcel = new QPushButton(u8"添加Excel文件");
	connect(m_btnOpenExcel, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickAddFile);
	m_mainLayout->addWidget(m_btnOpenExcel, 0, 2, 1, 2);

	m_btnUpdate = new QPushButton(u8"更新当前表格");
	connect(m_btnUpdate, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickUpdateTable);
	m_mainLayout->addWidget(m_btnUpdate, 0, 12, 1, 2);


	//保存统计数据按钮
	m_btnSaveExcel = new QPushButton(u8"保存表格内容");
	connect(m_btnSaveExcel, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickSaveTable);
	m_mainLayout->addWidget(m_btnSaveExcel, 0, 14, 1, 2);

	m_tableFileList = new QTableWidget;
	//表格选中相应
	connect(m_tableFileList, &QTableWidget::cellDoubleClicked, this, &QualityMangerWgt::slot_onFileDoubleClicked);

	m_tableFileList->setColumnCount(2);
	m_tableFileList->setRowCount(0); // 初始时不添加任何行
	m_tableFileList->setSelectionMode(QAbstractItemView::SingleSelection); // 设置选择模式为单行选中
	m_tableFileList->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置选择行为为选择整行
	m_tableFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为双击不可编辑

																		  // 设置列名称
	m_tableFileList->setHorizontalHeaderLabels({ u8"名称", u8"路径" });
	// 设置列宽（可选）
	m_tableFileList->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
	m_tableFileList->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
	m_tableFileList->setColumnWidth(0, 100);
	m_tableFileList->setColumnWidth(1, 300);

	m_mainLayout->addWidget(m_tableFileList, 1, 0, 4, 6);


	m_tableSheetList = new QTableWidget;
	m_tableSheetList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为双击不可编辑
	//connect(m_tableSheetList, &QTableWidget::cellChanged, this, &QualityMangerWgt::slot_onCellChanged);
	m_mainLayout->addWidget(m_tableSheetList, 1, 6, 4, 10);
	

	this->setLayout(m_mainLayout);

	//获取列索引
	{
		const Json::Value& jsonCol = m_jsonRoot.at(m_strTitle.toStdString()).at("pos");
		QStringList listHead;
		listHead << u8"表单名称";
		for (const auto& iterCol : jsonCol.ObjectRange())
		{
			std::string strValue = iterCol.second.ToString();
			auto pos = strValue.find("_");
			if (pos != std::string::npos)
			{
				std::string colName(strValue.begin(), strValue.begin() + pos);
				std::string colPos(strValue.begin() + pos + 1, strValue.end());
				m_mapColName.insert(std::make_pair(std::atoi(iterCol.first.c_str()), std::make_pair(colName, colPos)));
			}
				
		}
		for (const auto& iterMap: m_mapColName) 
		{
			listHead << iterMap.second.first.c_str();
		}
		int colCount = listHead.size();//总列数
		m_tableSheetList->setColumnCount(colCount);
		m_tableSheetList->setRowCount(0); // 初始时不添加任何行
		m_tableSheetList->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
		// 设置列名称
		m_tableSheetList->setHorizontalHeaderLabels(listHead);
		// 设置列宽（可选）
		m_tableSheetList->setColumnWidth(0, 60);
		for (int colIndex = 1 ; colIndex < colCount ; ++ colIndex)
		{
			m_tableSheetList->horizontalHeaderItem(colIndex)->setTextAlignment(Qt::AlignCenter);
			m_tableSheetList->setColumnWidth(colIndex, 70);
		}
	}

	//读取历史记录
	Json::Value& jsonHisFile = m_jsonRoot.at(m_strTitle.toStdString()).at("files");
	if (jsonHisFile.JSONType() == Json::Value::emJsonType::Array)
	{
		//解析json到表格
		std::vector<std::string> vecValidFile;
		auto iterFile = jsonHisFile.ArrayRange().begin();
		while (iterFile != jsonHisFile.ArrayRange().end())
		{
			QString strFile = iterFile->ToString().c_str();
			auto pos = strFile.lastIndexOf('/');
			if (pos == -1)
			{
				pos = strFile.lastIndexOf('\\');
			}
			if (pos != -1)
			{
				QString fileName = strFile.mid(pos + 1);
				int rowIndex = m_tableFileList->rowCount();
				m_tableFileList->insertRow(rowIndex);
				QTableWidgetItem *nameItem = new QTableWidgetItem(fileName);
				QTableWidgetItem *pathItem = new QTableWidgetItem(strFile);
				m_tableFileList->setItem(rowIndex, 0, nameItem);
				m_tableFileList->setItem(rowIndex, 1, pathItem);
				m_mapAllFile.insert(std::make_pair(strFile, fileName));
				vecValidFile.emplace_back(strFile.toStdString());
			}
			++iterFile;
		}
		jsonHisFile.clear();
		for (const auto& iterInvalid : vecValidFile)
		{
			jsonHisFile.append(iterInvalid);
		}
		saveJson();
	}
}

QualityMangerWgt::~QualityMangerWgt()
{

}

void QualityMangerWgt::release()
{
	if (!m_ptrFileHandle.isEmpty())
	{
		m_ptrFileHandle.clear();//关闭不保存
	}
}

void QualityMangerWgt::slot_onClickDeleteFile()
{
	QList<QTableWidgetItem*> selectedItems = m_tableFileList->selectedItems();
	if (selectedItems.isEmpty()) {
		return;
	}

	// 假设我们只对整行选中感兴趣，并且只处理第一行选中的情况（通常是用户通过点击行号选择的整行）
	QTableWidgetItem *firstSelectedItem = selectedItems.first();
	int row = firstSelectedItem->row(); // 获取选中项所在的行号
	AtomicLock lock(m_bChanging);

	// 获取这一行的所有值
	QTableWidgetItem *item = m_tableFileList->item(row, 1);
	if (item)
	{ // 确保项存在
		QString fileFullPath = item->text(); // 获取项的值（文本）
		auto iterWork = m_mapAllFile.find(fileFullPath);
		if (iterWork != m_mapAllFile.end())
		{
			if (m_ptrFileHandle.strFileFullPath == iterWork->first)//正在显示
			{
				m_tableSheetList->clearContents();
				m_tableSheetList->setRowCount(0);
				m_ptrFileHandle.clear();
			}
			m_tableFileList->removeRow(row);
			m_mapAllFile.erase(fileFullPath);

			//更新Json文件
			Json::Value& jsonHisFile = m_jsonRoot.at(m_strTitle.toStdString()).at("files");
			jsonHisFile.clear();
			for (const auto& iterFile : m_mapAllFile)
			{
				jsonHisFile.append(iterFile.first.toStdString());
			}
			saveJson();

		}
	}
}

void QualityMangerWgt::slot_onClickAddFile()
{
	QString strFilePathName = QFileDialog::getOpenFileName(this, QStringLiteral("选择Excel文件"), "", tr("Exel file(*.xls *.xlsx)"));
	if (strFilePathName.isNull()) 
	{
		return;
	}
	//strFilePathName = QDir::toNativeSeparators(strFilePathName);

	if (m_mapAllFile.count(strFilePathName) != 0)
	{
		QMessageBox::warning(this, u8"重复添加", QString(u8"文件 %1 已经添加过了！").arg(strFilePathName));
		return;
	}

	LOG_INFO("add excel file: %s", strFilePathName.toStdString().c_str());

	auto pos = strFilePathName.lastIndexOf('/');
	if (pos == -1)
	{
		pos = strFilePathName.lastIndexOf('\\');
	}
	if (pos != -1)
	{
		QString fileName = strFilePathName.mid(pos + 1);
		int rowIndex = m_tableFileList->rowCount();
		m_tableFileList->insertRow(rowIndex);
		QTableWidgetItem *nameItem = new QTableWidgetItem(fileName);
		QTableWidgetItem *pathItem = new QTableWidgetItem(strFilePathName);
		m_tableFileList->setItem(rowIndex, 0, nameItem);
		m_tableFileList->setItem(rowIndex, 1, pathItem);
		m_mapAllFile.insert(std::make_pair(strFilePathName, fileName));
		Json::Value& jsonHisFile = m_jsonRoot.at(m_strTitle.toStdString()).at("files");
		jsonHisFile.append(strFilePathName.toStdString());
		saveJson();
	}
}

void QualityMangerWgt::slot_onFileDoubleClicked(int row, int column)
{
	AtomicLock lock(m_bChanging);

	// 获取这一行的所有值
	QTableWidgetItem *item = m_tableFileList->item(row, 1);
	if (item) 
	{ // 确保项存在
		QString filePath = item->text(); // 获取项的值（文本）
		auto iterWork = m_mapAllFile.find(filePath);
		if (iterWork != m_mapAllFile.end())
		{
			if (!m_ptrFileHandle.isEmpty())
			{
				m_ptrFileHandle.clear();
			}
			
			m_ptrFileHandle.ptrFileHandle = m_workbooks->querySubObject("Open (const QString&)", QDir::toNativeSeparators(iterWork->first));
			if (nullptr == m_ptrFileHandle.ptrFileHandle)
			{
				QMessageBox::warning(this, u8"错误", u8"打开文件失败！");
				return;
			}
			m_ptrFileHandle.strFileFullPath = iterWork->first;
			QAxObject *sheets = m_ptrFileHandle.ptrFileHandle->querySubObject("Sheets");
			int sheetNum = sheets->property("Count").toInt();
			m_tableSheetList->clearContents();
			m_tableSheetList->setRowCount(0);
			int colNum = m_tableSheetList->columnCount();

			for (int i = 0; i < sheetNum; ++i)
			{
				QAxObject *worksheet = m_ptrFileHandle.ptrFileHandle->querySubObject("Worksheets(int)", i + 1);
				m_tableSheetList->insertRow(i);
				QString strSheetName = worksheet->property("Name").toString();
				QTableWidgetItem *sheetName = new QTableWidgetItem(strSheetName);
				m_tableSheetList->setItem(i, 0, sheetName);
				for (int colIndex = 1; colIndex < colNum; ++colIndex)
				{
					QTableWidgetItem *sheetSelect = new QTableWidgetItem();
					m_tableSheetList->setItem(i, colIndex, sheetSelect);
				}
			}
			slot_onClickUpdateTable();
			QMessageBox::information(this, u8"提示", u8"文件打开完成！");
		}
	}

}

void QualityMangerWgt::slot_onClickUpdateTable()
{
	if (m_ptrFileHandle.isEmpty())
	{
		return;
	}
	int colNum = m_tableSheetList->columnCount();
	for (size_t rowIndex = 0; rowIndex < m_tableSheetList->rowCount(); rowIndex++)
	{
		for (size_t colIndex = 1; colIndex < colNum; colIndex++)
		{
			QTableWidgetItem *itemPos = m_tableSheetList->item(rowIndex, colIndex);
			if (itemPos)
			{
				// 获取并打印编辑完成的值
				QAxObject *worksheet = m_ptrFileHandle.ptrFileHandle->querySubObject("Worksheets(int)", rowIndex + 1);
				if (worksheet)
				{
					QAxObject *range = worksheet->querySubObject("Range(const QString&)", m_mapColName[colIndex].second.c_str());
					if (range)
					{
						QVariant var = range->dynamicCall("Value");
						m_tableSheetList->item(rowIndex, colIndex)->setText(var.toString());
					}
				}
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
	worksheet->dynamicCall("SetName(const QString&)", u8"总表");
	int rowCount = m_tableSheetList->rowCount();
	//int colCount = m_tableSheetList->colorCount();
	QAxObject *cell = worksheet->querySubObject("Cells(int, int)", 1, 1);
	//cell->dynamicCall("SetValue(const QVariant&)", u8"日期");
	cell->dynamicCall("SetValue(const QVariant&)", "");

	//设置质量问题列类型
	for (const auto& iterMap : m_mapColName) 
	{
		cell = worksheet->querySubObject("Cells(int, int)", iterMap.first + 1, 1);
		cell->dynamicCall("SetValue(const QVariant&)", iterMap.second.first.c_str());
	}

	int colCount = m_tableSheetList->columnCount();
	for (int rowIndex = 0 ; rowIndex < rowCount ; ++rowIndex)
	{
		QTableWidgetItem *itemName = m_tableSheetList->item(rowIndex, 0);
		cell = worksheet->querySubObject("Cells(int, int)", 1, rowIndex + 2);
		cell->dynamicCall("SetValue(const QVariant&)", itemName->text());//设置第一列表单名

		for (int colIndex = 1 ; colIndex < colCount ; ++colIndex)
		{
			QTableWidgetItem *itemValue = m_tableSheetList->item(rowIndex, colIndex);
			cell = worksheet->querySubObject("Cells(int, int)", colIndex + 1, rowIndex + 2);
			cell->dynamicCall("SetValue(const QVariant&)", itemValue->text());
		}
	}

	int sheetRowNum = m_mapColName.size() + 1;
	int sheetColNum = rowCount + 1;
	std::vector<std::vector<QString>> vecTable;
	vecTable.resize(sheetRowNum);
	for (auto& iterCol : vecTable)
	{
		iterCol.resize(sheetColNum);
	}

	for (int sheetRow = 0 ; sheetRow < sheetRowNum; ++sheetRow)
	{
		for (int sheetCol = 0 ; sheetCol < sheetColNum; ++sheetCol)
		{
			QAxObject *cell = worksheet->querySubObject("Cells(int,int)", sheetRow + 1, sheetCol + 1);
			vecTable[sheetRow][sheetCol] = cell->property("Value").toString();
		}
	}

	QAxObject *worksheets = workbook->querySubObject("Worksheets");
	for (int sheetRow = 1; sheetRow < sheetRowNum; ++sheetRow)
	{
		QAxObject * newSheet = worksheets->querySubObject("Add()");
		//QAxObject * newSheet = workbook->querySubObject("Worksheets(int)", sheetRow + 1);
		newSheet->dynamicCall("SetName(const QString&)", vecTable[sheetRow][0]);
		//设置质量问题列类型
		for (int sheetColIndex = 0; sheetColIndex < sheetColNum; ++sheetColIndex)
		{
			//第一行
			cell = newSheet->querySubObject("Cells(int, int)", 1, sheetColIndex + 1);
			cell->dynamicCall("SetValue(const QVariant&)", vecTable[0][sheetColIndex]);
			cell = newSheet->querySubObject("Cells(int, int)", 2, sheetColIndex + 1);
			cell->dynamicCall("SetValue(const QVariant&)", vecTable[sheetRow][sheetColIndex]);
		}
	}

	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
	QMessageBox::information(this, u8"提示", QString(u8"文件成功保存到：%1").arg(filePath));
	//workbook->dynamicCall("Close (Boolean)", false);
	//workbook->dynamicCall("Release (void)");
}


void QualityMangerWgt::saveJson()
{
	std::ofstream output;
	output.open(m_jsonFilePath, std::ofstream::out);
	if (output.is_open())
	{
		output << m_jsonRoot.dumpStyle() << std::endl;
		output.close();
	}
}
