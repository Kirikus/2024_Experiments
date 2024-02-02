#include "test_module.h"

#include <QApplication>

#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>

namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE(test_rho_w)

BOOST_AUTO_TEST_CASE(ground_level) { BOOST_TEST(rho_w(0, 0.5, 42) == 21); }

BOOST_AUTO_TEST_CASE(rho_w_2000m) {
  BOOST_TEST(rho_w(2000 - 1e-6) == rho_w(2000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_CASE(rho_w_8000m) {
  BOOST_TEST(rho_w(8000 - 1e-6) == rho_w(8000 + 1e-6), tt::tolerance(1e-6));
}

BOOST_AUTO_TEST_SUITE_END()
