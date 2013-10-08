#ifndef DEVTREEVIEW_H
#define DEVTREEVIEW_H

#include <QTreeWidget>
#include <QJsonObject>
#include <QTreeWidgetItem>
#include <QList>

class DevTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    DevTreeView(QWidget *parent);
private:    
    void parseJsonObj( QList<QJsonObject> jobjl, QTreeWidgetItem **ppItem );
    void init_top_level();
    void item_expanded( QTreeWidgetItem * item );
    void init_tree_show();
private slots:
    void itemSelectionChangedSlot();
signals:
    void treeItemSelectionChanged(QStringList);
};

#endif // DEVTREEVIEW_H
