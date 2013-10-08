/* copyright: ms
 * author: ZhouJinWei
 * Function: 实现图片文件用QLabel部件的展示
 */
#include "imagelabel.h"
#include <QSizePolicy>
#include <QFrame>
#include <QPixmap>
#include <QResizeEvent>

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
    QSizePolicy policy = QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );//QSizePolicy::Maximum Fixed

    this->setSizePolicy( policy );
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->setAutoFillBackground( true );
    this->setScaledContents( true );
    //this->setFixedSize( );
    mbLoaded = false;
}

void ImageLabel::loadImage(QString sFileName)
{
    //this->setText("");
    if( mbLoaded ) {
        mImage.load( sFileName );
        //QImage img = mImage.scaled( this->sizeHint() );
        //this->setPixmap( QPixmap::fromImage(img) );
    } else {
        mbLoaded = true;
        QImage *pImg = new QImage( sFileName );
        mImage = *pImg;

        //QImage img = mImage.scaled( this->sizeHint() );
        //this->setPixmap( QPixmap::fromImage(img) );
        this->setPixmap( QPixmap::fromImage(mImage) );
        delete pImg;
    }
}

void ImageLabel::clear()
{
    mbLoaded = false;
    QLabel::clear();
}

/*void ImageLabel::resizeEvent(QResizeEvent *event)
{
    qDebug() << "window width:" << event->size().width() << " height:" << event->size().height();
    mpIrImageView->setFixedHeight( event->size().height()*2/5);
}*/
