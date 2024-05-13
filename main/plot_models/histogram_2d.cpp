#include "histogram_2d.h"

#include <cmath>

#include "manager/manager.h"

class CustomTicker : public QCPAxisTicker {
 public:
  CustomTicker(double granularity_0) : granularity_(granularity_0 / 10) {}

  QString getTickLabel(double tick, const QLocale& locale, QChar formatChar,
                       int precision) override {
    return QCPAxisTicker::getTickLabel(tick * granularity_, locale, formatChar,
                                       precision);
  }

 private:
  double granularity_ = 1;
};

void Histogram2D::Draw() {
  // The color scheme automatically adjusts to the set of values

  clearPlottables();

  xAxis->setLabel("");
  yAxis->setLabel("");

  if (int(lib::Manager::GetInstance()->GetVariablesCount()) <= std::max(x_, y_))
    return;
  const lib::Variable& variable_x =
      lib::Manager::GetInstance()->GetVariable(x_);

  const lib::Variable& variable_y =
      lib::Manager::GetInstance()->GetVariable(y_);

  if (variable_x.GetMeasurementsCount() == 0 ||
      variable_y.GetMeasurementsCount() == 0)
    return;

  double size_box = 1e-300;

  for (size_t i = 0; i < variable_y.GetMeasurementsCount(); ++i) {
    size_box = std::max(size_box, std::max(abs(variable_x.measurements[i]),
                                           abs(variable_y.measurements[i])));
  }

  QVector<QVector<double>> density(
      2 * int(granularity_) + 2, QVector<double>(2 * int(granularity_) + 2, 0));

  for (size_t i = 0; i < variable_x.GetMeasurementsCount(); ++i) {
    density[std::round(variable_x.measurements[i] * (granularity_ / size_box) +
                       granularity_)]
           [std::round(variable_y.measurements[i] * (granularity_ / size_box) +
                       granularity_)]++;
  }

  QSharedPointer<CustomTicker> customTicker(
      new CustomTicker(int(size_box / (granularity_ / 10))));
  xAxis->setTicker(customTicker);
  yAxis->setTicker(customTicker);

  QCPColorMap* colorMap = new QCPColorMap(xAxis, yAxis);

  colorMap->data()->setSize(2 * granularity_ + 4, 2 * granularity_ + 4);
  colorMap->data()->setRange(QCPRange(-granularity_ - 2, granularity_ + 2),
                             QCPRange(-granularity_ - 2, granularity_ + 2));

  for (int i = 0; i <= 2 * granularity_; ++i) {
    for (int j = 0; j <= 2 * granularity_; ++j) {
      colorMap->data()->setCell(i + 2, j + 2, density[i][j]);
    }
  }

  QCPColorGradient gradient;
  gradient.clearColorStops();
  gradient.setColorStopAt(0, QColor(255, 255, 0));
  gradient.setColorStopAt(0.5, QColor(255, 0, 0));
  gradient.setColorStopAt(1, QColor(128, 0, 128));
  colorMap->setGradient(gradient);

  colorMap->setInterpolate(true);
  colorMap->rescaleDataRange(true);

  moveLayer(layer("grid"), layer("main"), QCustomPlot::limAbove);

  xAxis->setLabel("Axis " + variable_x.naming.title);
  yAxis->setLabel("Axis " + variable_y.naming.title);
  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

void Histogram2D::Options() {
  OptionsHistogram2D a(index_x_, index_y_, index_granularity_);
  a.exec();

  x_ = a.choose_AxisX();
  y_ = a.choose_AxisY();
  granularity_ = a.choose_granularity();

  index_x_ = a.get()->axisXComboBox->currentIndex();
  index_y_ = a.get()->axisYComboBox->currentIndex();
  index_granularity_ = a.get()->granularityComboBox->currentIndex();

  Draw();
}

OptionsHistogram2D::OptionsHistogram2D(int index_x_, int index_y_,
                                       int index_granularity_)
    : ui(new Ui::DialogHistogram2D) {
  ui->setupUi(this);

  setWindowTitle("Histogram2D options");

  for (size_t i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->axisXComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }
  ui->axisXComboBox->setCurrentIndex(index_x_);

  for (size_t i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->axisYComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }
  ui->axisYComboBox->setCurrentIndex(index_y_);

  ui->granularityComboBox->addItem("10");
  ui->granularityComboBox->addItem("50");
  ui->granularityComboBox->addItem("200");
  ui->granularityComboBox->addItem("1000");
  ui->granularityComboBox->setCurrentIndex(index_granularity_);

  connect(ui->confirmPushButton, &QPushButton::clicked, this, &QDialog::close);
}

double OptionsHistogram2D::choose_granularity() {
  switch (ui->granularityComboBox->currentIndex()) {
    case 0:
      return 10;
    case 1:
      return 50;
    case 2:
      return 200;
    case 3:
      return 1000;
    default:
      return 50;
  }
}

int OptionsHistogram2D::choose_AxisX() {
  return ui->axisXComboBox->currentIndex();
}

int OptionsHistogram2D::choose_AxisY() {
  return ui->axisYComboBox->currentIndex();
}

OptionsHistogram2D::~OptionsHistogram2D() { delete ui; }
