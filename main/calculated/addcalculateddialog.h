#ifndef ADDCALCULATEDDIALOG_H
#define ADDCALCULATEDDIALOG_H

#include <QDialog>

namespace Ui {
class AddCalculatedDialog;
}

class AddCalculatedDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddCalculatedDialog(QWidget* parent = nullptr);
  ~AddCalculatedDialog();

private slots:

  void on_addCalculatedPushButton_clicked();

  void on_varnameLineEdit_editingFinished();

private:
  QString varname;
  QList<double> values;

  Ui::AddCalculatedDialog* ui;

signals:
  void calculated_is_added();
};

#endif  // ADDCALCULATEDDIALOG_H
