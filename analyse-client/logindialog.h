#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "curllibport.h"

namespace Ui {
class LoginDialog;
}


class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog( QWidget *parent = 0, CurllibPort *pCurl = 0 );
    ~LoginDialog();    
private:
    Ui::LoginDialog *ui;

    QLineEdit *mpUserEmailEdit;
    QLineEdit *mpPasswordEdit;
    //QCheckBox *mpAutoLoginCheckBox;
    QPushButton *mpLoginBtn;
    CurllibPort *mpCurl;    
private slots:
    void loginBtnSlot();
};

#endif // LOGINDIALOG_H
