#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QStackedWidget>
#include <QGridLayout>
#include <QResizeEvent>
#include <QToolBar>
#include "irimageview.h"

namespace Ui {
class Dialog;//Dialog
}

class MainWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void resizeEvent(QResizeEvent * event);
private slots:
    void importShootResultSlot();
    void exportSlot();
    void importSlot();
    void batchDiagnoseSlot();
    void helpSlot();
    void aboutSlot();

    void irRadClick(bool bCheck);
    //void treeItemSelectionChangedSlot(QStringList itemList);
private:
    Ui::Dialog *ui;//
    QStackedWidget *mpStackWidget;
    IrImageView * mpIrImageView;
    QGridLayout *mpgLayout;
    QToolBar *mpToolBar;
    bool mbRadioCheckFlag;

    //Toolbar action
    QAction *importShootResultAction;
    QAction *exportAction;
    QAction *importAction;
    QAction *batchDiagnoseAction;
    QAction *helpAction;
    QAction *aboutAction;

    QAction *searchAction;
    QAction *showAllAction;

    void createToolbar();
signals:
    //void treeItemSelectionChangedSlot(QStringList);
};

#endif // MAINWINDOW_H
