#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_onTimeOut();

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void openMainPanel();
    void messageClicked();
    void showMainPanel();


    void on_showMessageButton_clicked();

private:
    void InitUI();
    void createTrayIcon();

    QSystemTrayIcon *m_trayIcon;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
