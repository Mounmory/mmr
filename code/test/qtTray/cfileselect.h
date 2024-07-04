#ifndef CFILESELECT_H
#define CFILESELECT_H

#include <QWidget>

class CFileSelect : public QWidget
{
    Q_OBJECT
public:
    explicit CFileSelect(QWidget *parent = nullptr);

protected:
    virtual void closeEvent(QCloseEvent *event);
signals:

};

#endif // CFILESELECT_H
