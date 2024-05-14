#include "addcalculateddialog.h"

#include "parser/formula_parser.h"
#include "parser/parser_ast.h"
#include "manager/manager.h"
#include "ui_addcalculateddialog.h"

AddCalculatedDialog::AddCalculatedDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::AddCalculatedDialog) {
  ui->setupUi(this);

  setFixedSize(400, 140);
  setWindowTitle("Data Handler");
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));

  ui->varnameLineEdit->setFixedSize(QSize(85, 30));
  ui->expressionLineEdit->setFixedSize(QSize(200, 30));
  ui->infoLabel->setStyleSheet("QLabel {color : red; }");
  ui->infoLabel->setVisible(false);
  ui->addCalculatedPushButton->setDisabled(true);
}

AddCalculatedDialog::~AddCalculatedDialog() { delete ui; }

void AddCalculatedDialog::on_addCalculatedPushButton_clicked() {
  std::string str = ui->expressionLineEdit->text().toStdString();
  boost::spirit::ascii::space_type space;

  typedef std::string::const_iterator iterator_type;
  typedef client::parser<iterator_type> parser;
  typedef client::ast::program ast_program;
  typedef client::ast::eval ast_eval;

  parser pars;
  ast_program program;
  ast_eval eval;

  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();
  try {
    bool r = phrase_parse(iter, end, pars, space, program);

    if (r && iter == end) {
      if (!lib::Manager::GetInstance()->IsVariableExisting(varname)) {
        lib::Manager::GetInstance()->AddVariable(lib::Variable(
            eval(program).values, varname, lib::Variable::VisualOptions(false),
            lib::Variable::ErrorOptions(), true));
        ui->infoLabel->setStyleSheet("QLabel {color : green; }");
        ui->infoLabel->setText("Calculated has been added");
        ui->infoLabel->setVisible(true);
      } else if (lib::Manager::GetInstance()
                     ->GetVariable(varname)
                     .is_calculated) {
        lib::Manager::GetInstance()->GetVariable(varname).measurements =
            eval(program).values;
        ui->infoLabel->setStyleSheet("QLabel {color : gray; }");
        ui->infoLabel->setText("Calculated has been changed");
        ui->infoLabel->setVisible(true);
      } else {
        throw std::logic_error("Redefining a not calculated variable");
      }
    } else
      throw std::logic_error("Uncorrect formula");
  } catch (...) {
    ui->infoLabel->setText("The formula is written incorrectly");
    ui->infoLabel->setStyleSheet("QLabel {color : red; }");
    ui->infoLabel->setVisible(true);
  }
}

void AddCalculatedDialog::on_varnameLineEdit_editingFinished() {
  if (ui->varnameLineEdit->text() != "") {
    varname = ui->varnameLineEdit->text();
    ui->addCalculatedPushButton->setDisabled(false);
  } else
    ui->addCalculatedPushButton->setDisabled(true);
}
