#ifndef DEFLABEL_H
#define DEFLABEL_H

#include <QLabel>
#include <QImage>
#include <QWidget>
#include <QPaintEvent>
#include <QSize>

typedef enum {
    DEF_LEV_URGENT = 0,
    DEF_LEV_SERIOUS,
    DEF_LEV_COMMONLY,
    DEF_LEV_ATTENTION,
    DEF_LEV_NORMAL,
    DEF_LEV_NONE
}E_DEF_LEVEL;
class DefLabel : public QLabel
{
public:    
    DefLabel( QSize parSize, QString sdef, E_DEF_LEVEL def_lev, QWidget *parent);
    DefLabel( E_DEF_LEVEL def_lev, QWidget *parent);
    void setDefLev(E_DEF_LEVEL def_lev);
    QString getString();
private:
    E_DEF_LEVEL m_def_lev;
    QString msDef;
    QSize mParSize;
    void paintEvent(QPaintEvent *);
};

#endif // DEFLABEL_H
