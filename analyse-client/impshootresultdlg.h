#ifndef IMPSHOOTRESULTDLG_H
#define IMPSHOOTRESULTDLG_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>

namespace Ui {
class ImpShootResultDlg;
}

typedef enum {
    DESKBTN_CLICK,
    MYDOCBTN_CLICK,
    MYCOMPUTERBTN_CLICK,
    BACKBTN_CLICK
}BTN_EVENT_E;

typedef enum {
    DIALOG_FLAG_IMPORT,
    DIALOG_FLAG_IMPORT_SHOOT_RESULT
}DIALOG_FLAG_E;
class ImpShootResultDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImpShootResultDlg( DIALOG_FLAG_E flag, QWidget *parent = 0);
    ~ImpShootResultDlg();
    
private:
    Ui::ImpShootResultDlg *ui;
    QListWidget *mpListWid;
    QLineEdit *mpFileNameEdit;
    DIALOG_FLAG_E m_dlg_flag;

    void loadListData(BTN_EVENT_E);
};

#endif // IMPSHOOTRESULTDLG_H
