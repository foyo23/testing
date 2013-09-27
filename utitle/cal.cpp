
#include <QtWidgets>
#include "calculatorform.h"

Cal::Cal(QWidget * parent)
    : QWidget(parent)
{
    setupUi(this);
}

void Cal::on_inputSpinBox1_valueChanged(int arg1)
{
    qDebug()<<this;
    label_3->setText( QString::number( arg1 + inputSpinBox2->value() ));
}

void Cal::on_inputSpinBox2_valueChanged(int arg1)
{
    label_3->setText( QString::number( arg1 + inputSpinBox1->value() ));
}
