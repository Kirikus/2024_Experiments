#ifndef ODF_FORM_H
#define ODF_FORM_H

#include <QWidget>

#include "QVBoxLayout"

namespace Ui {
class ODF_Form;
}

class ODF_Form : public QWidget {
  Q_OBJECT

 public:
  explicit ODF_Form(QWidget *parent = nullptr);
  ~ODF_Form();

  QVBoxLayout *GetLayout();

 signals:
  void textBtn_is_clicked();
  void plotBtn_is_clicked();
  void tableBtn_is_clicked();
  void AssembleBtn_is_clicked();

 private slots:
  void on_addtextBtn_clicked() { emit textBtn_is_clicked(); }

  void on_addplotBtn_clicked() { emit plotBtn_is_clicked(); }

  void on_addtableBtn_clicked() { emit tableBtn_is_clicked(); }

  void on_assembleBtn_clicked() { emit AssembleBtn_is_clicked(); }

 private:
  Ui::ODF_Form *ui;
};

#endif  // ODF_FORM_H
