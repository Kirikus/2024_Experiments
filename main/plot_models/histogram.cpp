#include "histogram.h"

#include "manager.h"

void Histogram::Draw() {
  clearPlottables();

  xAxis->setLabel("");
  yAxis->setLabel("");

  if (lib::Manager::GetInstance()->GetVariablesCount() == 0) return;

  const lib::Variable& variable =
      lib::Manager::GetInstance()->GetVariable(var_);

  if (variable.GetMeasurementsCount() == 0) return;

  double max_value = variable.measurements[0],
         min_value = variable.measurements[0];

  for (int j = 0; j < variable.GetMeasurementsCount(); ++j) {
    max_value = std::max(max_value, variable.measurements[j]);
    min_value = std::min(min_value, variable.measurements[j]);
  }

  QVector<double> xAxis_data;
  QVector<double> yAxis_data;

  double column_size_ = std::max(0.001, (max_value - min_value) / granularity_);

  for (double i = min_value; i <= max_value; i += column_size_) {
    int count = 0;
    for (int j = 0; j < variable.GetMeasurementsCount(); ++j) {
      if (i <= variable.measurements[j] &&
          variable.measurements[j] < i + column_size_) {
        count++;
      }
    }
    xAxis_data.push_back(i + column_size_ / 2.0);
    yAxis_data.push_back(count);
  }

  QCPBars* bar = new QCPBars(xAxis, yAxis);

  bar->setWidth(column_size_);
  bar->setData(xAxis_data, yAxis_data);
  bar->setBrush(QBrush(variable.visual.color));

  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

void Histogram::Options() {
  OptionsHistogram a;
  a.exec();

  var_ = a.choose_variable();
  granularity_ = a.choose_granularity();

  Draw();
}

OptionsHistogram::OptionsHistogram(QWidget* parent)
    : QDialog(parent), ui(new Ui::DialogHistogram) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->VariableComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  ui->GranularityComboBox->addItem(QString("10"));
  ui->GranularityComboBox->addItem(QString("100"));
  ui->GranularityComboBox->addItem(QString("1000"));

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram::choose_variable() {
  return ui->VariableComboBox->currentIndex();
}

int OptionsHistogram::choose_granularity() {
  return std::pow(10, ui->GranularityComboBox->currentIndex() + 1);
}

OptionsHistogram::~OptionsHistogram() { delete ui; }
