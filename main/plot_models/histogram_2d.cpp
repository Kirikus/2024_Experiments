#include "histogram_2d.h"

#include "manager.h"

void Histogram2D::Draw() {
  // The color scheme automatically adjusts to the set of values

  clearPlottables();

  xAxis->setLabel("");
  yAxis->setLabel("");

  if (lib::Manager::GetInstance()->GetVariablesCount() == 0) return;

  int size_box = 200;

  const lib::Variable& variable_x =
      lib::Manager::GetInstance()->GetVariable(x_);

  QCPGraph* graph = addGraph();

  setFont(QFont("Helvetica", 9));

  const lib::Variable& variable_y =
      lib::Manager::GetInstance()->GetVariable(y_);

  for (int i = 0; i < variable_y.GetMeasurementsCount(); ++i) {
    size_box =
        std::max(size_box, 2 * std::max(abs(int(variable_x.measurements[i])),
                                        abs(int(variable_y.measurements[i]))) +
                               20);
  }

  QVector<QVector<double>> density(size_box, QVector<double>(size_box));
  QVector<QVector<bool>> flags(size_box, QVector<bool>(size_box, true));

  for (int i = 0; i < variable_y.GetMeasurementsCount(); ++i) {
    for (int j = -size_box / 2; j <= size_box / 2; ++j) {
      if (j <= variable_y.measurements[i] &&
          variable_y.measurements[i] < j + 1) {
        density[variable_x.measurements[i] + size_box / 2][j + size_box / 2]++;
      }
    }
  }

  QCPColorMap* colorMap = new QCPColorMap(xAxis, yAxis);

  colorMap->data()->setSize(size_box, size_box);
  colorMap->data()->setRange(QCPRange(-size_box / 2, size_box / 2),
                             QCPRange(-size_box / 2, size_box / 2));

  for (int i = 0; i < size_box; ++i) {
    for (int j = 0; j < size_box; ++j) {
      if (flags[i][j]) {
        double med = 0;
        for (int l1 = 0; l1 < square_size_; ++l1) {
          for (int l2 = 0; l2 < square_size_; ++l2) {
            med += density[std::min(i + l1, size_box - 1)]
                          [std::min(j + l2, size_box - 1)];
            flags[std::min(i + l1, size_box - 1)]
                 [std::min(j + l2, size_box - 1)] = false;
          }
        }
        for (int l1 = 0; l1 < square_size_; ++l1) {
          for (int l2 = 0; l2 < square_size_; ++l2) {
            colorMap->data()->setCell(std::min(i + l1, size_box - 1),
                                      std::min(j + l2, size_box - 1),
                                      med / (square_size_ * square_size_));
          }
        }
      }
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
  OptionsHistogram2D a;
  a.exec();

  x_ = a.choose_AxisX();
  y_ = a.choose_AxisY();
  square_size_ = a.choose_AxisY();

  Draw();
}

OptionsHistogram2D::OptionsHistogram2D(QWidget* parent)
    : QDialog(parent), ui(new Ui::DialogHistogram2D) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisXComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisYComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  ui->SquareSizeComboBox->addItem("1");
  ui->SquareSizeComboBox->addItem("2");
  ui->SquareSizeComboBox->addItem("4");

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram2D::choose_square_size() {
  return std::pow(2, ui->SquareSizeComboBox->currentIndex());
}

int OptionsHistogram2D::choose_AxisX() {
  return ui->AxisXComboBox->currentIndex();
}

int OptionsHistogram2D::choose_AxisY() {
  return ui->AxisYComboBox->currentIndex();
}

OptionsHistogram2D::~OptionsHistogram2D() { delete ui; }
