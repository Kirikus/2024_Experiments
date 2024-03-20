#ifndef STRATEGYIO_H
#define STRATEGYIO_H

#include "manager.h"

struct StrategyIO {
  virtual void save(const QString&) = 0;
  virtual void load(const QString&) = 0;
};

struct StrategyIO_JSON : public StrategyIO {
  void save(const QString&) override;
  void load(const QString&) override;
};

struct StrategyIO_DB : public StrategyIO {
  void save(const QString&) override;
  void load(const QString&) override;
};

struct StrategyIO_CSV : public StrategyIO {
  void save(const QString&) override;
  void load(const QString&) override;
};

#endif  // STRATEGYIO_H
