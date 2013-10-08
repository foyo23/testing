/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现缺陷色标
 */
#include "deflabel.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QFontMetrics>

DefLabel::DefLabel(QSize parSize, QString sdef, E_DEF_LEVEL def_lev, QWidget *parent):QLabel(parent)
{
    m_def_lev = def_lev;
    msDef = sdef;
    mParSize = parSize;
}

DefLabel::DefLabel(E_DEF_LEVEL def_lev, QWidget *parent):QLabel(parent)
{
    m_def_lev = def_lev;
    msDef = "";
    mParSize.setWidth( 0 );
    this->setFixedWidth( 20 );
}

void DefLabel::setDefLev(E_DEF_LEVEL def_lev)
{
    m_def_lev = def_lev;
    this->repaint();
}

QString DefLabel::getString()
{
    return msDef;
}

void DefLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor clr;
    bool bNeedPaintImg = true;

    //qDebug() << "paintEvent:" << this->rect();
    if( m_def_lev == DEF_LEV_URGENT ) {
        clr = Qt::red;
    } else if( m_def_lev == DEF_LEV_SERIOUS ) {
        clr = QColor(239,134,77);
    }  else if( m_def_lev == DEF_LEV_COMMONLY ) {
        clr = QColor(252,216,14);//Qt::yellow;
    }  else if( m_def_lev == DEF_LEV_ATTENTION ) {
        clr = QColor(236,14,132);//Qt::magenta;
    }  else if( m_def_lev == DEF_LEV_NORMAL ) {
        clr = Qt::green;
    }  else  {
        bNeedPaintImg = false ;
    }

    int x = 3;
    if( bNeedPaintImg ) {
        painter.setPen( QPen(clr) );
        painter.setBrush( QBrush(clr) );
        if( !msDef.isEmpty() ) {
            QFontMetrics *pfontMetr = new QFontMetrics( this->font() );
            int nTextWid = pfontMetr->boundingRect( msDef ).width();
            //qDebug() << "nTextWid:" << nTextWid;
            x = (mParSize.width()-22-nTextWid)/2;
            //qDebug() << "x:" << x;
        }
        painter.drawEllipse( x, 0, 15, 15 );//this->width()-5, this->width()-5
    }

    if( !msDef.isEmpty() ) {
        painter.setPen( QPen(Qt::black ) );
        painter.drawText( x+22, 12, msDef );
    }
}
