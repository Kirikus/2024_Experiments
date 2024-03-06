#ifndef STRATEGYIO_H
#define STRATEGYIO_H

#include "manager.h"

class StrategyIO {
  virtual void save(lib::Manager&) = 0;
  virtual void load(lib::Manager&) = 0;
};

class StrategyIO_JSON : public StrategyIO {
  void save(lib::Manager&) override;
  void load(lib::Manager&) override;
};

class StrategyIO_BD : public StrategyIO {
  void save(lib::Manager&) override;
  void load(lib::Manager&) override;
};

class StrategyIO_Custom : public StrategyIO {
  void save(lib::Manager&) override;
  void load(lib::Manager&) override;
};

#endif  // STRATEGYIO_H
