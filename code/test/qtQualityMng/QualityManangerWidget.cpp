#include "QualityManangerWidget.h"
#include "util/UtilFunc.h"


QualityMangerWgt::QualityMangerWgt(QWidget* parent/* = nullptr*/)
	: QWidget(parent)
	, m_bChanging(false)
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
	m_btnDeleRow = new QPushButton(u8"移除选中文档");
	connect(m_btnDeleRow, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickDeleteFile);
	m_mainLayout->addWidget(m_btnDeleRow, 0, 0, 1, 2);

	//添加文件按钮
	m_btnOpenExcel = new QPushButton(u8"添加Excel文件");
	connect(m_btnOpenExcel, &QPushButton::clicked, this, &QualityMangerWgt::slot_onClickSlectFile);
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
	connect(m_tableFileList, &QTableWidget::itemSelectionChanged, this, &QualityMangerWgt::slot_onFileSelectChanged);

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

	//获取当前进程路径
	std::string strAppPath, strAppName;
	mmrUtil::getAppPathAndName(strAppPath, strAppName);
	std::string configPath = strAppPath + "config/";
	//if (_access(configPath.c_str(), 0) == -1)//如果数据库文件夹不存在，则创建
	//{
	//	if (CreateDirectory(configPath.c_str(), 0) == false)
	//	{
	//		QMessageBox::warning(this, u8"错误", u8"初始化配置文件夹失败！");
	//	}
	//}

	//获取列索引
	{
		std::string strColDefPath = strAppPath + "config/colDef.json";
		Json::Value jsonCol;
		std::string strErr = Json::json_from_file(strColDefPath, jsonCol);
		if (jsonCol.IsNull() || !strErr.empty())
		{
			LOG_ERROR_PRINT("parse json file [%s] failed! error message is: %s.", m_jsonFilePath.c_str(), strErr.c_str());
		}
		else
		{
			QStringList listHead;
			listHead << u8"表单名称";
			for (const auto& iterCol : jsonCol.ObjectRange())
			{
				m_mapColName.insert(std::make_pair(std::atoi(iterCol.first.c_str()), iterCol.second.ToString()));
			}
			for (const auto& iterMap: m_mapColName) 
			{
				listHead << iterMap.second.c_str();
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
	}


	//读取历史记录
	//读配置文件，加载所有组件
	m_jsonFilePath = strAppPath + "config/history.json";
	if (_access(m_jsonFilePath.c_str(), 0) != -1)//配置文件存在
	{
		std::string strErr = Json::json_from_file(m_jsonFilePath, m_jsonRoot);
		if (m_jsonRoot.IsNull() || !strErr.empty())
		{
			LOG_ERROR_PRINT("parse json file [%s] failed! error message is: %s.", m_jsonFilePath.c_str(), strErr.c_str());
		}
		//解析json到表格
		std::vector<std::string> vecInvalidFile;
		auto iterFile = m_jsonRoot.ObjectRange().begin();
		while (iterFile != m_jsonRoot.ObjectRange().end())
		{
			if (openFile(iterFile->first.c_str()))
			{
				LOG_WARN("file %s open failed!", iterFile->first.c_str());
			}
			else
			{
				vecInvalidFile.emplace_back(iterFile->first);
			}
			++iterFile;
		}
		for (const auto& iterInvalid : vecInvalidFile)
		{
			m_jsonRoot.eraseKey(iterInvalid);
		}
	}
}

QualityMangerWgt::~QualityMangerWgt()
{

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
		QString value = item->text(); // 获取项的值（文本）
		auto iterWork = m_mapAllFile.find(value);
		if (iterWork != m_mapAllFile.end())
		{
			if (m_currentFile == iterWork->second)//正在显示
			{
				m_tableSheetList->clearContents();
				m_tableSheetList->setRowCount(0);
				m_currentFile = nullptr;
			}
			m_tableFileList->removeRow(row);
			iterWork->second->dynamicCall("Close (Boolean)", false);
			m_mapAllFile.erase(value);
			m_jsonRoot.eraseKey(value.toStdString());
			saveJson();

		}
	}
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
	if (openFile(strFilePathName))
	{
		std::string strFilePath = strFilePathName.toStdString();
		m_jsonRoot[strFilePath] = Json::Value();
		saveJson();
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
	AtomicLock lock(m_bChanging);

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
			m_tableSheetList->clearContents();
			m_tableSheetList->setRowCount(0);
			int colNum = m_tableSheetList->columnCount();
			if (m_jsonRoot.hasKey(value.toStdString()) && !m_jsonRoot[value.toStdString()].IsNull())
			{
				auto& jsonPos = m_jsonRoot[value.toStdString()];
				for (int i = 0; i < sheetNum; ++i)
				{
					QAxObject *worksheet = m_currentFile->querySubObject("Worksheets(int)", i + 1);
					m_tableSheetList->insertRow(i);
					QString strSheetName = worksheet->property("Name").toString();
					QTableWidgetItem *sheetName = new QTableWidgetItem(strSheetName);
					m_tableSheetList->setItem(i, 0, sheetName);
					for (int colIndex = 1; colIndex < colNum; ++colIndex)
					{
						QTableWidgetItem *sheetSelect = new QTableWidgetItem();
						m_tableSheetList->setItem(i, colIndex, sheetSelect);
						if (colIndex % 2)//奇数列
						{
							std::string typeIndex = std::to_string((colIndex + 1) / 2);
							if (jsonPos.hasKey(strSheetName.toStdString()) && jsonPos[strSheetName.toStdString()].hasKey(typeIndex))
							{
								QString strText = jsonPos[strSheetName.toStdString()][typeIndex].ToString().c_str();
								sheetSelect->setText(strText);
							}
						}
					}
				}
				slot_onClickUpdateTable();
			}
			else
			{
				for (int i = 0; i < sheetNum; ++i)
				{
					QAxObject *worksheet = m_currentFile->querySubObject("Worksheets(int)", i + 1);
					m_tableSheetList->insertRow(i);
					QString strSheetName = worksheet->property("Name").toString();
					QTableWidgetItem *sheetName = new QTableWidgetItem(strSheetName);
					m_tableSheetList->setItem(i, 0, sheetName);
					for (int colIndex = 1 ; colIndex <colNum; ++colIndex)
					{
						m_tableSheetList->setItem(i, colIndex, new QTableWidgetItem());
					}

				}
			}
		}
	}

}

void QualityMangerWgt::slot_onClickUpdateTable()
{
	if (!m_currentFile)
	{
		return;
	}
	int colNum = m_tableSheetList->columnCount();
	for (size_t rowIndex = 0; rowIndex < m_tableSheetList->rowCount(); rowIndex++)
	{
		for (size_t colIndex = 1; colIndex < colNum; colIndex++)
		{
			if (colIndex % 2)//奇数列
			{
				QTableWidgetItem *itemPos = m_tableSheetList->item(rowIndex, colIndex);
				if (itemPos && !itemPos->text().isEmpty())
				{
					// 获取并打印编辑完成的值
					QString value = itemPos->text();
					QAxObject *worksheet = m_currentFile->querySubObject("Worksheets(int)", rowIndex + 1);
					if (worksheet)
					{
						QAxObject *range = worksheet->querySubObject("Range(const QString&)", value);
						if (range)
						{
							QVariant var = range->dynamicCall("Value");
							m_tableSheetList->item(rowIndex, colIndex + 1)->setText(var.toString());
						}
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
	for (const auto& iterMap : m_mapColName) 
	{
		cell = worksheet->querySubObject("Cells(int, int)", iterMap.first + 1, 1);
		cell->dynamicCall("SetValue(const QVariant&)", iterMap.second.c_str());
	}

	int colCount = m_tableSheetList->columnCount();
	for (int rowIndex = 0 ; rowIndex < rowCount ; ++rowIndex)
	{
		QTableWidgetItem *itemName = m_tableSheetList->item(rowIndex, 0);
		cell = worksheet->querySubObject("Cells(int, int)", 1, rowIndex + 2);
		cell->dynamicCall("SetValue(const QVariant&)", itemName->text());//设置第一列表单名

		for (int colIndex = 1 ; colIndex < colCount ; ++colIndex)
		{
			if ((colIndex % 2) == 0)//值列
			{
				QTableWidgetItem *itemValue = m_tableSheetList->item(rowIndex, colIndex);
				cell = worksheet->querySubObject("Cells(int, int)", colIndex / 2 + 1, rowIndex + 2);
				cell->dynamicCall("SetValue(const QVariant&)", itemValue->text());
			}
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

	for (int sheetRow = 1; sheetRow < sheetRowNum; ++sheetRow)
	{
		QAxObject * newSheet = workbook->querySubObject("Add()");
		worksheet->dynamicCall("SetName(const QString&)", vecTable[sheetRow][0]);
		for (int sheetCol = 0; sheetCol < sheetColNum; ++sheetCol)
		{
		}
	}
	

	workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
	//workbook->dynamicCall("Close (Boolean)", false);
	//workbook->dynamicCall("Release (void)");
}

void QualityMangerWgt::slot_onCellChanged(int row, int column)
{
	if ((column % 2)!= 1 || m_bChanging.load(std::memory_order_relaxed))//仅处理第二列
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
			//更新Json
			Json::Value jvalue;
			int colNum = m_tableSheetList->columnCount();
			for (size_t rowNum = 0; rowNum < m_tableSheetList->rowCount(); rowNum++)
			{
				Json::Value jsonColPos;
				QTableWidgetItem *itemSheet = m_tableSheetList->item(rowNum, 0);
				for (const auto& iterCol :m_mapColName)
				{
					QTableWidgetItem *itemCol = m_tableSheetList->item(rowNum, 2 * iterCol.first - 1);
					jsonColPos[std::to_string(iterCol.first)] = itemCol->text().toStdString();
				}
				jvalue[itemSheet->text().toStdString()] = jsonColPos;
			}
			for (const auto iterFile : m_mapAllFile)
			{
				if (iterFile.second == m_currentFile)
				{
					m_jsonRoot[iterFile.first.toStdString()] = jvalue;
				}
			}
			saveJson();
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

void QualityMangerWgt::saveJson()
{
	std::ofstream output;
	output.open(m_jsonFilePath, std::ofstream::out);
	if (output.is_open())
	{
		output << m_jsonRoot.dump() << std::endl;
		output.close();
	}
}

bool QualityMangerWgt::openFile(QString strPath)
{
	m_workbooks->dynamicCall("Open (const QString&)", strPath);
	QAxObject *workbook = m_excelApp->querySubObject("ActiveWorkBook");
	if (workbook)
	{
		auto pos = strPath.lastIndexOf('\\');
		if (pos != -1)
		{
			QString fileName = strPath.mid(pos + 1);
			int rowIndex = m_tableFileList->rowCount();
			m_tableFileList->insertRow(rowIndex);
			QTableWidgetItem *nameItem = new QTableWidgetItem(fileName);
			QTableWidgetItem *pathItem = new QTableWidgetItem(strPath);
			m_tableFileList->setItem(rowIndex, 0, nameItem);
			m_tableFileList->setItem(rowIndex, 1, pathItem);
			m_mapAllFile.insert(std::make_pair(strPath, workbook));
			return true;
		}
	}
	return false;
}
