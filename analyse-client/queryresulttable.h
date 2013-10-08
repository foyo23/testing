#ifndef QUERYRESULTTABLE_H
#define QUERYRESULTTABLE_H

#include <QTableWidget>
#include "config.h"

class QueryResultTable : public QTableWidget
{
    Q_OBJECT
public:
    QueryResultTable(QWidget *parent, bool bDevDetail);
    QList<QStringList> getSelectedDatas( bool bThreePhase, int *nCurrIndex );
    QList<int> getDefCounts();
    QList<QStringList> getAllDatas();
private:
    QList<QStringList> mTotalList; //All datas
    QList<QStringList> mSelectedDataList; //Three phase or history
    QList<QStringList> mQueryResultList;
    void loadDatas( bool bDevDetail );
    void setDatasToWidget();
    Config *mpConfig;
public slots:
    void treeItemSelectionChangedSlot( QStringList textList );
};

#endif // QUERYRESULTTABLE_H
