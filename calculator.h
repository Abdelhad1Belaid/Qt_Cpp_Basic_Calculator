#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void NumPressed();
    void on_unary_operation_pressed();
    void on_binary_operation_pressed();
    void on_comma_released();
    void on_clear_released();
    void on_equal_released();
    void on_actionAbout_triggered();
};
#endif // CALCULATOR_H
