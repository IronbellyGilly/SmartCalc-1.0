#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qtimer.h>

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "../s21_SmartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digits_numbers();
  void on_pushButton_point_clicked();
  void operations();
  void math_functions();
  void on_pushButton_backspace_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_equally_clicked();
  void on_Graph_build_clicked();
  void on_credit_clicked();
  void on_deposit_clicked();
};
#endif  // MAINWINDOW_H
