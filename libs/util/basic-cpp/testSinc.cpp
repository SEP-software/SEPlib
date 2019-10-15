#include <gtest/gtest.h>  // googletest header file
#include <cmath>
#include <string>
#include "sinc.h"
using std::string;
using namespace SEP;

TEST(sinc, mksinc) {
  sinc m = sinc(8, .001);

  EXPECT_LE(fabs(m._table[0][0]), .001);
  EXPECT_LE(fabs(m._table[0][1]), .001);
  EXPECT_LE(fabs(m._table[0][2]), .001);
  EXPECT_LE(fabs(1. - m._table[0][3]), .001);
  EXPECT_LE(fabs(m._table[0][4]), .001);
  EXPECT_LE(fabs(m._table[0][5]), .001);
  EXPECT_LE(fabs(m._table[0][6]), .001);
  EXPECT_LE(fabs(m._table[0][7]), .001);

  EXPECT_LE(fabs(-0.0125823 - m._table[500][0]), .001);
  EXPECT_LE(fabs(0.0525434 - m._table[500][1]), .001);
  EXPECT_LE(fabs(-0.15726 - m._table[500][2]), .001);
  EXPECT_LE(fabs(0.616379 - m._table[500][3]), .001);
  EXPECT_LE(fabs(0.616385 - m._table[500][4]), .001);
  EXPECT_LE(fabs(-0.157265 - m._table[500][5]), .001);
  EXPECT_LE(fabs(0.0525462 - m._table[500][6]), .001);
  EXPECT_LE(fabs(-0.0125834 - m._table[500][7]), .001);
}
