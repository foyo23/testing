#ifndef EXPORTSETTINGDLG_H
#define EXPORTSETTINGDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QListWidget>

namespace Ui {
class ExportSettingDlg;
}

class ExportSettingDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportSettingDlg(QWidget *parent = 0);
    ~ExportSettingDlg();
    
private:
    Ui::ExportSettingDlg *ui;

    QCheckBox *mpFilterDataCheck;
    QLabel *mpFilterDataLab;
    QListWidget *mpListWid;
    QCheckBox *mpBaseCheck;
    QCheckBox *mpRuleCheck;
    QCheckBox *mpRecCheck;
    QCheckBox *mpImgCheck;

private slots:
    void okBtnSlot();
};

#endif // EXPORTSETTINGDLG_H
