// author: killer
// blog: blog.csdn.net/sabcdefg
// netpt.net
// 武林秘籍 ^^^ 目录 ^^^

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cfileselect.h"
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    //系统托盘相关
    //
    createTrayIcon();

	//setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);//总保持在顶部

	ui->iconComboBox->addItem(QIcon(":/images/bad.svg"), u8"坏的");
    ui->iconComboBox->addItem(QIcon(":/images/heart.svg"), u8"比心");
    ui->iconComboBox->addItem(QIcon(":/images/trash.svg"), u8"垃圾桶");

	//ui->iconComboBox->addItem(QIcon("D:/VMs/mmrCode/code/test/qtTray/images/bad.svg"), u8"垃圾桶");
	//ui->iconComboBox->addItem(QIcon("D:/VMs/mmrCode/code/test/qtTray/images/heart.svg"), u8"垃圾桶");
	//ui->iconComboBox->addItem(QIcon("D:/VMs/mmrCode/code/test/qtTray/images/trash.svg"), u8"垃圾桶");

    connect(ui->showIconCheckBox, SIGNAL(toggled(bool)), m_trayIcon, SLOT(setVisible(bool)));
    connect(ui->iconComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setIcon(int)));
    connect(m_trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));



    //
    //气泡消息相关
    //
    ui->typeComboBox->addItem(u8"没有图标", QSystemTrayIcon::NoIcon);
    ui->typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxInformation), u8"信息",
            QSystemTrayIcon::Information);
    ui->typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxWarning), u8"警告",
            QSystemTrayIcon::Warning);
    ui->typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxCritical), u8"停止",
            QSystemTrayIcon::Critical);
    ui->typeComboBox->setCurrentIndex(1);

    ui->durationSpinBox->setRange(5, 60);
    ui->durationSpinBox->setValue(15);
    //
    //初始化UI
    //
    InitUI();

    //QTimer* temTimer = new QTimer(this);
    //connect(temTimer,&QTimer::timeout,this,&MainWindow::slot_onTimeOut);
    //temTimer->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitUI()
{
    int nCurIndex = ui->iconComboBox->currentIndex();
    setIcon(nCurIndex);

    if(ui->showIconCheckBox->isChecked())
    {
        m_trayIcon->show();
    }
}

void MainWindow::createTrayIcon()
{
    //菜单项--打开主面板
    QAction* openMainPanel = new QAction(u8"打开主面板", this);
    connect(openMainPanel, SIGNAL(triggered()), this, SLOT(showMainPanel()));

	QAction* childDlg = new QAction(u8"打开子对话框", this);
	connect(childDlg, SIGNAL(triggered()), this, SLOT(slot_onTimeOut()));

    //菜单项--退出
    QAction* quitAction = new QAction(u8"退出", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    //菜单
    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openMainPanel);
	trayIconMenu->addAction(childDlg);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    //创建系统托盘图标
    m_trayIcon = new QSystemTrayIcon(this);
    //设置托盘图标的右键菜单
    m_trayIcon->setContextMenu(trayIconMenu);

}

void MainWindow::setIcon(int index)
{
    //从ComboBox里取出图标
    QIcon icon = ui->iconComboBox->itemIcon(index);
    //设置托盘的图标
    m_trayIcon->setIcon(icon);
    //设置主窗口的图标
    setWindowIcon(icon);

    //当鼠标悬停在托盘图标上,显示的消息
    m_trayIcon->setToolTip(ui->iconComboBox->itemText(index));
}

void MainWindow::openMainPanel()
{

}

void MainWindow::on_showMessageButton_clicked()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(
            ui->typeComboBox->itemData(ui->typeComboBox->currentIndex()).toInt());
    m_trayIcon->showMessage(ui->titleEdit->text(), ui->bodyEdit->toPlainText(), icon,
                          ui->durationSpinBox->value() * 1000);
}

void MainWindow::messageClicked()
{
    showMainPanel();
    QMessageBox::information(0, u8"系统托盘",
							u8"不好意思, 我已经尽力而为了.\n"
                                u8"也许,你需要人工服务?");
}


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger: //鼠标左键点击图标
    {
        showMainPanel();
        break;
    }
    case QSystemTrayIcon::DoubleClick: //鼠标左键双击图标
        ui->iconComboBox->setCurrentIndex((ui->iconComboBox->currentIndex() + 1)
                                      % ui->iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick: //鼠标中键点击图标
        on_showMessageButton_clicked();
        break;
    default:
        ;
    }
}

CFileSelect* g_ptrFileSelet = nullptr;
void MainWindow::slot_onTimeOut()
{
    if(g_ptrFileSelet == nullptr)
    {
        g_ptrFileSelet = new CFileSelect(this);
        g_ptrFileSelet->show();
    }
    if(g_ptrFileSelet->isHidden())
        g_ptrFileSelet->show();


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_trayIcon->isVisible())
    {
        hide(); //隐藏主窗口
        event->ignore(); //忽略这个消息
    }
}

void MainWindow::showMainPanel()
{
    showNormal();
    activateWindow();
    setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    raise();//必须加，不然X11会不起作用
//#ifdef Q_OS_WIN32 //windows必须加这个，不然windows10 会不起作用，具体参看activateWindow 函数的文档
#if 0
    HWND hForgroundWnd = GetForegroundWindow();
    DWORD dwForeID = ::GetWindowThreadProcessId(hForgroundWnd, NULL);
    DWORD dwCurID = ::GetCurrentThreadId();

    ::AttachThreadInput(dwCurID, dwForeID, TRUE);
    ::SetForegroundWindow((HWND)winId());xcsc_jnx
    ::AttachThreadInput(dwCurID, dwForeID, FALSE);
#endif // MAC_OS
}
