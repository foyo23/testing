#ifndef CALCULATORFORM_H
#define CALCULATORFORM_H
#include "ui_form.h"
class Cal : public QWidget ,private  Ui::Form
{
    Q_OBJECT
public:
    Cal(QWidget *parent = 0);
private slots :
    void on_inputSpinBox1_valueChanged(int arg1);
    void on_inputSpinBox2_valueChanged(int arg1);
};
#endif // CALCULATORFORM_H
