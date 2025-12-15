#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_One_clicked();

    void on_Two_clicked();

    void on_Three_clicked();

    void on_Four_clicked();

    void on_Five_clicked();

    void on_Six_clicked();

    void on_Seven_clicked();

    void on_Eight_clicked();

    void on_Nine_clicked();

    void on_Zero_clicked();

    void on_Plus_clicked();

    void on_Minus_clicked();

    void on_Multiply_clicked();

    void on_Divide_clicked();

    void on_Dort_clicked();

    void on_LeftBracket_clicked();

    void on_RightBracket_clicked();

    void on_Clear_clicked();

    void on_Delete_clicked();

    void on_Equal_clicked();

    void on_Imaginary_Number_clicked();

    void on_Random_clicked();

    void on_File_clicked();

private:
    Ui::Widget *ui;
    QString expression,showExpression;
};
#endif // WIDGET_H
