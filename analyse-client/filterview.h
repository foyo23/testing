#ifndef FILTERVIEW_H
#define FILTERVIEW_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "queryresulttable.h"

class FilterView : public QWidget
{
    Q_OBJECT
public:
    FilterView( QWidget *parent, bool bDevDetail );
    void setDevTypeVolComboData( FilterView *pFilterView );
private:
    QWidget *mpDatesWidget;
    QRadioButton *mpIrRadionBtn;
    QRadioButton *mpDevDetailRadBtn;
    QueryResultTable *mpTable;
    QLineEdit *mpCountEdit;
    QLabel *mpdevnameLab;
    QRadioButton *mpPhaseRadBtn;
    QComboBox *mpDevTypeCom;
    QComboBox *mpDevRegVolCom;
#define DEFCHECKBOX_COUNT 6
    QCheckBox * mpCheckBox[DEFCHECKBOX_COUNT];
    QLabel *mpTotalLab;

    void setDefCount();    
signals:
    void tableSelectionChanged( QueryResultTable*pTable, bool bPhaseContrast );
    void treeItemSelectionChanged(QStringList);
private slots:
    void tableSelectionChanged();
    void phaseRadClick(bool bChecked);
public:
    void setIrRadioChecked( bool bCheck );
public slots:
    void treeItemSelectionChangedSlot( QStringList textList );
};

#endif // FILTERVIEW_H
