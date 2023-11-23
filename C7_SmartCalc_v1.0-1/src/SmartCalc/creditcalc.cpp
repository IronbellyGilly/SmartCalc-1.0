#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_calculate_credit_clicked() {
  double summa_kredita = ui->sum_of_credit->text().toDouble();
  double percent = ui->percent->text().toDouble();
  double srok = ui->credit_term->text().toDouble();
  if (ui->ann->isChecked() && summa_kredita > 0 && percent > 0 && srok > 0) {
    double month_stavka = percent / 12 / 100;
    double month_pay =
        summa_kredita *
        (month_stavka + (month_stavka / (pow((1 + month_stavka), srok) - 1)));
    double total_pay = month_pay * srok;
    double pereplata = total_pay - summa_kredita;
    ui->payment->setText(QString::number(month_pay, 'f', 2));
    ui->total_payment->setText(QString::number(total_pay, 'f', 2));
    ui->overpayment->setText(QString::number(pereplata, 'f', 2));
  }
  if (ui->diff->isChecked() && summa_kredita > 0 && percent > 0 && srok > 0) {
    double month_stavka = percent / 12 / 100;
    double total_pay = 0.0;
    double res = 0.0, month = 0.0;
    for (int i = 0; i < srok; i++) {
      month = summa_kredita / srok +
              (summa_kredita - (summa_kredita / srok) * i) * month_stavka;
      if (i == 0) res = month;
      total_pay += month;
    }
    double pereplata = total_pay - summa_kredita;
    ui->payment->setText(QString::number(res, 'f', 2) + "..." +
                         QString::number(month, 'f', 2));
    ui->overpayment->setText(QString::number(pereplata, 'f', 2));
    ui->total_payment->setText(QString::number(total_pay, 'f', 2));
  }
}
