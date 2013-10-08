#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QImage>
#include <QWidget>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    //void resizeEvent(QResizeEvent *event);
    void loadImage(QString sFileName);
    void clear();
signals:
private:
    QImage mImage;
    bool mbLoaded;
public slots:
    
};

#endif // IMAGELABEL_H
