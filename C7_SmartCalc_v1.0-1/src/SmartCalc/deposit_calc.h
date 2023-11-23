#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QDialog>

namespace Ui {
class deposit_calc;
}

class deposit_calc : public QDialog {
  Q_OBJECT

 public:
  explicit deposit_calc(QWidget *parent = nullptr);
  ~deposit_calc();

 private slots:
  void on_calculate_clicked();
  int check_cap();
  int period_to_pay();
  int div_rate(int *period_viplat, double *deposit_term);
  void annual_tax_calc(int period_viplat, double accrued_interest,
                       int *count_tax, int i, double *tax_buffer);
  double tax_calc(double tax_buffer, double accrued_interest,
                  double interest_edge, int count_tax, double nalog_stavka);

 private:
  Ui::deposit_calc *ui;
};

#endif  // DEPOSIT_CALC_H
