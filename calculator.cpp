#include "calculator.h"
#include "ui_calculator.h"


double calc_val = 0.0;
double first_num;
bool typing;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  /* seting the initial value of the display screen to 0*/
  ui->Display->setText(QString::number(calc_val));

  /*
   * Connecting Numpad to the function NumPressed
   */
  QPushButton *buttons[10];
  for (int i = 0; i < 10; i++) {
    QString button_num = "button" + QString::number(i);
    buttons[i] = Calculator::findChild<QPushButton *>(button_num);
    connect(buttons[i], SIGNAL(released()), this, SLOT(NumPressed()));
  }

  /*
   * Connectine the Unary Operators to the  on_unary_operation_pressed function
   */
  connect(ui->percent, SIGNAL(released()), this,SLOT(on_unary_operation_pressed()));
  connect(ui->plus_minus, SIGNAL(released()), this,SLOT(on_unary_operation_pressed()));

  /*
   * Connectine the Binary Operators to the  on_binary_operation_pressedfunction
   */
  connect(ui->plus, SIGNAL(released()), this,SLOT(on_binary_operation_pressed()));
  connect(ui->minus, SIGNAL(released()), this,SLOT(on_binary_operation_pressed()));
  connect(ui->multiply, SIGNAL(released()), this,SLOT(on_binary_operation_pressed()));
  connect(ui->division, SIGNAL(released()), this,SLOT(on_binary_operation_pressed()));

  ui->plus->setCheckable(true);
  ui->minus->setCheckable(true);
  ui->multiply->setCheckable(true);
  ui->division->setCheckable(true);
}

Calculator::~Calculator() {
    delete ui;
}
/*----------------------------------------NumPad--------------------------------------------*/
void Calculator::NumPressed() {
  QPushButton *button = (QPushButton *)sender();
  double new_val;
  QString new_disp;
  if ( (ui->plus->isChecked() || ui->minus->isChecked() || ui->multiply->isChecked() ||ui->division->isChecked())&& !typing) {
      new_val = button->text().toDouble();
      typing =true;
      new_disp = QString::number(new_val, 'g', 10);
  } else {
      if(ui->Display->text().contains('.') && button->text() == "0"){
          new_disp = ui->Display->text() + button->text();
      }else{
        new_val = (ui->Display->text() + button->text()).toDouble();
        new_disp = QString::number(new_val, 'g', 10);
      }
  }
  ui->Display->setText(new_disp);
}

/*------------------------------------Unary Operations-----------------------------------*/
void Calculator::on_unary_operation_pressed() {
  QPushButton *button = (QPushButton *)sender();
  double val = ui->Display->text().toDouble();
  if (button->text() == '%') {
    double newval = val * 0.01;
    ui->Display->setText(QString::number(newval, 'g', 10));
  }
  if (button->text() == "±") {
    double newval = val * -1;
    ui->Display->setText(QString::number(newval, 'g', 10));
  }
}

/*----------------------------------------Comma-----------------------------------------------*/
void Calculator::on_comma_released() {
    if(!ui->Display->text().contains('.')){
        ui->Display->setText(ui->Display->text() + ".");
    }
}
/*----------------------------------------clear-----------------------------------------------*/

void Calculator::on_clear_released() {
  ui->Display->clear();
  ui->Display->setText("0");
  ui->plus->setChecked(false);
  ui->minus->setChecked(false);
  ui->multiply->setChecked(false);
  ui->division->setChecked(false);
  typing = false;
}
/*----------------------------------------equal operation-----------------------------------------------*/

void Calculator::on_equal_released() {
    double second_num;
    second_num = ui->Display->text().toDouble();
    if(ui->plus->isChecked()){
        calc_val = first_num + second_num;
        ui->Display->setText(QString::number(calc_val, 'g', 10));
        ui->plus->setChecked(false);
    }
    if(ui->minus->isChecked()){
        calc_val = first_num - second_num;
        ui->Display->setText(QString::number(calc_val, 'g', 10));
        ui->minus->setChecked(false);

    }
    if(ui->multiply->isChecked()){
        calc_val = first_num * second_num;
        ui->Display->setText(QString::number(calc_val, 'g', 10));
        ui->multiply->setChecked(false);

    }
    if(ui->division->isChecked()){
        calc_val = first_num / second_num;
        ui->Display->setText(QString::number(calc_val, 'g', 10));
        ui->division->setChecked(false);

    }
    typing = false;
}
/*----------------------------------------binary operations-----------------------------------------------*/

void Calculator::on_binary_operation_pressed() {
  QPushButton *button = (QPushButton *)sender();
  first_num = ui->Display->text().toDouble();
  button->setChecked(true);
}


void Calculator::on_actionAbout_triggered()
{
    QString msg = "@project: \tBasic Calculator\n@author: \tBelaid Abdelhadi\n@email: \tbelaidabdelhadi@gmail.com\n@social: \thttps://web.facebook.com/belaid.B.D.T.A.2010/\n@github: \thttps://github.com/Abdelhad1Belaid\n@linkedin: \thttps://www.linkedin.com/in/abdelhadi-belaid/";
    QMessageBox info ;
    info.setIcon(QMessageBox::Information);
    info.setText(msg);
    info.exec();
}
