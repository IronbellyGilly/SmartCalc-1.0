#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:

  void on_calculate_credit_clicked();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
