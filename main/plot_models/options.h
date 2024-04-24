#ifndef OPTIONS_H
#define OPTIONS_H

#include "ui_options.h"

class Options : public QDialog {
  Q_OBJECT

 public:
  Options(QWidget *parent = nullptr);
  ~Options();

  int choose_variable();
  int choose_column_size();
  void ok();

 private:
  Ui::Dialog *ui;
};

#endif  // OPTIONS_H
