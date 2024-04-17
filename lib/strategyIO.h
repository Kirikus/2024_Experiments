#ifndef STRATEGYIO_H
#define STRATEGYIO_H

#include "manager.h"

namespace lib {

struct StrategyIO {
  virtual void Save(const QString&) = 0;
  virtual void Load(const QString&) = 0;
};

struct StrategyIO_JSON : public StrategyIO {
  void Save(const QString&) override;
  void Load(const QString&) override;
};

struct StrategyIO_CSV : public StrategyIO {
  void Save(const QString&) override;
  void Load(const QString&) override;
};

struct StrategyIO_DB : public StrategyIO {
  void Save(const QString&) override;
  void Load(const QString&) override;
};

}  // namespace lib

#endif  // STRATEGYIO_H
