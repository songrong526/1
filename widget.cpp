#include "widget.h"
#include "./ui_widget.h"
#include "calculate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Calculator");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_One_clicked()
{
    expression += "1";
    showExpression += "1";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Two_clicked()
{
    expression += "2";
    showExpression += "2";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Three_clicked()
{
    expression += "3";
    showExpression += "3";
    ui->lineEdit->setText(showExpression);
}

void Widget::on_Four_clicked()
{
    expression += "4";
    showExpression += "4";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Five_clicked()
{
    expression += "5";
    showExpression += "5";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Six_clicked()
{
    expression += "6";
    showExpression += "6";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Seven_clicked()
{
    expression += "7";
    showExpression += "7";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Eight_clicked()
{
    expression += "8";
    showExpression += "8";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Nine_clicked()
{
    expression += "9";
    showExpression += "9";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Zero_clicked()
{
    expression += "0";
    showExpression += "0";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Plus_clicked()
{
    expression += "+";
    showExpression += "+";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Minus_clicked()
{
    expression += "-";
    showExpression += "-";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Multiply_clicked()
{
    expression += "*";
    showExpression += "×";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Divide_clicked()
{
    expression += "/";
    showExpression += "÷";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Dort_clicked()
{
    expression += ".";
    showExpression += ".";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_LeftBracket_clicked()
{
    expression += "(";
    showExpression += "(";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_RightBracket_clicked()
{
    expression += ")";
    showExpression += ")";
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Clear_clicked()
{
    expression.clear();
    showExpression.clear();
    ui->lineEdit->clear();
}


void Widget::on_Delete_clicked()
{
    expression.chop(1);
    showExpression.chop(1);
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Equal_clicked()
{
    binary_tree t;
    QString result_str;

    //transform QString to string
    string s = expression.toStdString();
    t.create_tree(s);

    complex_number* _result = t.calculate();

    if (_result->imag == 0) {
        result_str = QString::number(_result->real, 'g', 6);
    } else if (_result->real == 0) {
        result_str = QString::number(_result->imag, 'g', 6) + "i";
    } else {
        result_str = QString::number(_result->real, 'g', 6) + "+" + QString::number(_result->imag, 'g', 6) + "i";
    }
    delete _result; // 释放内存

    //result_str = QString::number(_result->real);

    expression = result_str;
    showExpression = result_str;
    ui->lineEdit->setText(result_str);
}

void Widget::on_Imaginary_Number_clicked()
{
    expression += 'i';
    showExpression += 'i';
    ui->lineEdit->setText(showExpression);
}


void Widget::on_Random_clicked()
{
    expression = QString::fromStdString(random_expression());
    QString temp = expression;
    showExpression = temp.replace("/","÷").replace("*","×");
    ui->lineEdit->setText(showExpression);
}


void Widget::on_File_clicked()
{
    expression = QString::fromStdString(file_expression());
    QString temp = expression;
    showExpression = temp.replace("/","÷").replace("*","×");
    ui->lineEdit->setText(showExpression);
}


void Widget::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);

    qDebug() << event->key() << event->text();

    switch (event->key())
    {
    case Qt::Key_Escape:
        this->close();
        break;
    case Qt::Key_1:
        on_One_clicked();
        break;
    case Qt::Key_2:
        on_Two_clicked();
        break;
    case Qt::Key_3:
        on_Three_clicked();
        break;
    case Qt::Key_4:
        on_Four_clicked();
        break;
    case Qt::Key_5:
        on_Five_clicked();
        break;
    case Qt::Key_6:
        on_Six_clicked();
        break;
    case Qt::Key_7:
        on_Seven_clicked();
        break;
    case Qt::Key_8:
        on_Eight_clicked();
        break;
    case Qt::Key_9:
        on_Nine_clicked();
        break;
    case Qt::Key_0:
        on_Zero_clicked();
        break;
    case Qt::Key_ParenLeft:
        on_LeftBracket_clicked();
        break;
    case Qt::Key_ParenRight:
        on_RightBracket_clicked();
        break;
    case Qt::Key_I:
        on_Imaginary_Number_clicked();
        break;
    case Qt::Key_Plus:
        on_Plus_clicked();
        break;
    case Qt::Key_Minus:
        on_Minus_clicked();
        break;
    case Qt::Key_Asterisk:
        on_Multiply_clicked();
        break;
    case Qt::Key_Slash:
        on_Divide_clicked();
        break;
    case Qt::Key_Enter:
        on_Equal_clicked();
        break;
    case Qt::Key_Backspace:
        on_Delete_clicked();
        break;
    }
}
