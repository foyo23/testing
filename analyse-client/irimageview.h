#ifndef IRIMAGEVIEW_H
#define IRIMAGEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QRadioButton>
#include "queryresulttable.h"
#include "imagelabel.h"
#include "config.h"
#include "deflabel.h"

#define SHOW_IMAGE_COUNT 3
class IrImageView : public QWidget
{
    Q_OBJECT
public:
    explicit IrImageView(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
private:
    QLabel *mpLab[SHOW_IMAGE_COUNT];
    DefLabel *mpDefColorLab[SHOW_IMAGE_COUNT];
    QLabel *mpPhaseLab[SHOW_IMAGE_COUNT];
    QTableWidget *mpTable[SHOW_IMAGE_COUNT];
    ImageLabel *mpTextLab[SHOW_IMAGE_COUNT];
    ImageLabel *mpImgLab[SHOW_IMAGE_COUNT];
    QRadioButton *mpIrImgRadBtn[SHOW_IMAGE_COUNT];
    bool mbPhaseContrast;
    QueryResultTable *mpQueryResultTab;
    void processImgRadClick( int seq, bool bChecked );
    Config *mpConfig;
signals:
private slots:
    void irImgARadClickSlot(bool bChecked);
    void irImgBRadClickSlot(bool bChecked);
    void irImgCRadClickSlot(bool bChecked);
public slots:
    void tableSelectionChangedSlot(QueryResultTable*pTable, bool bPhaseContrast);
};

#endif // IRIMAGEVIEW_H
