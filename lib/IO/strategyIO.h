#ifndef STRATEGYIO_H
#define STRATEGYIO_H

#include <QString>

namespace lib {

struct StrategyIO {
  virtual void Save(const QString&) = 0;
  virtual void Load(const QString&) = 0;

  virtual ~StrategyIO() = 0;
};

struct StrategyIO_JSON : public StrategyIO {
  void Save(const QString&) override;
  void Load(const QString&) override;

  virtual ~StrategyIO_JSON() override {}
};

struct StrategyIO_CSV : public StrategyIO {
  void Save(const QString&) override;
  void Load(const QString&) override;

  virtual ~StrategyIO_CSV() override {}
};

}  // namespace lib

#endif  // STRATEGYIO_H
