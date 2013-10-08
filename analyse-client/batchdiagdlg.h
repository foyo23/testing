#ifndef BATCHDIAGDLG_H
#define BATCHDIAGDLG_H

#include <QDialog>
#include <QProgressBar>
#include <QListWidget>
#include <QPushButton>

namespace Ui {
class BatchDiagDlg;
}

class BatchDiagDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit BatchDiagDlg(QWidget *parent = 0);
    ~BatchDiagDlg();
    
private:
    Ui::BatchDiagDlg *ui;
    QPushButton *mpFinishBtn;
    QListWidget *mpMsgListWid;
    QProgressBar *mpDiagProgBar;
};

#endif // BATCHDIAGDLG_H
