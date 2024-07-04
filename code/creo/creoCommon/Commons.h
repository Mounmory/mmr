#ifndef COMMONS_H
#define COMMONS_H

#include <QWidget>
#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QLibrary>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>

//PTCView
#include "interface/IPTCViewWidget.h"

//C++��׼��ͷ�ļ�
#include <io.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>


#define MAX_STRING_LEN 1024

//*************���Pro/Tookitͷ�ļ�
#ifdef PRO_USE_VAR_ARGS
#include <ProToolkit.h>
#include <ProUtil.h>
#include <ProArray.h>
#include <ProDimension.h>
#include <ProWindows.h>
#include <ProSolid.h>
#include <ProParameter.h>
#include <ProParamval.h>
#include <ProMessage.h>
#include <ProMenu.h>
#include <ProMenuBar.h>
#include <ProMdl.h>
#include <ProModelitem.h>
#include <ProDrawing.h>
#include <ProFeature.h>
#include <ProFeatType.h>
#include <ProDrawing.h>
#include <ProNotify.h>
#include <ProRefInfo.h>
#include <ProRelSet.h>
#include <ProSelection.h>
#include <ProUICmd.h>
#include <ProNotify.h>
#include <ProPopupmenu.h>
#include <ProSelbuffer.h>
#include <ProAsmcomp.h>
#include <ProAsmcomppath.h>
#include <afxdisp.h>
#include <afxcontrolbars.h>
//////�������Ŀ¼�ظ��ļ�ר��
#include <ProUICmd.h>
#include <ProUIMessage.h>
#include <ProToolkitDll.h>
////һ����ɫר��
#include <ProSurface.h>
#include <afxdisp.h>
#endif


#ifndef MAX_STR_LEN
#define MAX_STR_LEN 1024
#endif
namespace CommonFunctios 
{
	IPTCViewWidget* createPTCViewWidget(QWidget* parent = nullptr);

	//��ȡ��̬��·��,���ļ��ָ�����\��
	std::string getDllPath();

	std::string getAppFullPath();

	std::string getAppPath();
}

#endif // !COMMONS_H
