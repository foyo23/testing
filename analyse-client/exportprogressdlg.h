#ifndef EXPORTPROGRESSDLG_H
#define EXPORTPROGRESSDLG_H

#include <QDialog>
#include <QProgressBar>
#include <QListWidget>
#include <QPushButton>

namespace Ui {
class ExportProgressDlg;
}

class ExportProgressDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportProgressDlg(QWidget *parent = 0);
    ~ExportProgressDlg();
    
private:
    Ui::ExportProgressDlg *ui;

    QProgressBar *mpTabProgBar;
    QProgressBar *mpZipProgBar;
    QListWidget *mpMsgListWid;
    QPushButton *mpFinishBtn;
    QPushButton *mpCancelBtn;
};

#endif // EXPORTPROGRESSDLG_H
