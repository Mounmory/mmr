#include "cfileselect.h"
#include <QCloseEvent>

CFileSelect::CFileSelect(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);//总保持在顶部
    setWindowTitle(u8"置顶对话框");
    setFixedSize(300, 200);
}
void CFileSelect::closeEvent(QCloseEvent *event)
{
        hide(); //隐藏主窗口
        event->ignore(); //忽略这个消息
}
