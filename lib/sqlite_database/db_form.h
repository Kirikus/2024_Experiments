#ifndef DB_FORM_H
#define DB_FORM_H

#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class DB_Form;
}

class DB_Form : public QMainWindow {
  Q_OBJECT

 public:
  explicit DB_Form(QWidget *parent = nullptr);
  ~DB_Form();

  QTableWidget *GetMeasurementsTableWidget();
  QTableWidget *GetVisualTableWidget();
  QTableWidget *GetNamingTableWidget();
  QTableWidget *GetErrorTableWidget();

 public slots:
  void on_uploadBtn_clicked();
  void on_deleteBtn_clicked();

 signals:
  void uploadBtn_is_clicked();
  void deleteBtn_is_clicked();

 private:
  Ui::DB_Form *ui;
};

#endif  // DB_FORM_H
