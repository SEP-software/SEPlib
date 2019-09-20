#include <gtest/gtest.h>  // googletest header file

#include <string>
#include "hypercube.h"
using std::string;
using namespace SEP;

TEST(axisCreate, baisc) {
  axis a = axis(3);

  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 0.);
  EXPECT_EQ(a.d, 1.);
  EXPECT_EQ(a.label, std::string(""));
  EXPECT_EQ(a.unit, std::string(""));

  a = axis(axis(3, 2.));
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 2.);
  EXPECT_EQ(a.d, 1.);
  EXPECT_EQ(a.label, std::string(""));
  EXPECT_EQ(a.unit, std::string(""));

  a = axis(axis(3, 2., 4.));
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 2.);
  EXPECT_EQ(a.d, 4.);
  EXPECT_EQ(a.label, std::string(""));
  EXPECT_EQ(a.unit, std::string(""));
  a = axis(axis(3, 2., 4., "time"));
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 2.);
  EXPECT_EQ(a.d, 4.);
  EXPECT_EQ(a.label, std::string("time"));
  EXPECT_EQ(a.unit, std::string(""));

  a = axis(axis(3, 2., 4., "time", "seconds"));
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 2.);
  EXPECT_EQ(a.d, 4.);
  EXPECT_EQ(a.label, std::string("time"));
  EXPECT_EQ(a.unit, std::string("seconds"));
}
TEST(axisFunc, equal) {
  axis b = axis(axis(3, 2., 4., "time", "seconds"));
  axis a = b;
  EXPECT_EQ(a.n, 3);
  EXPECT_EQ(a.o, 2.);
  EXPECT_EQ(a.d, 4.);
  EXPECT_EQ(a.label, std::string("time"));
  EXPECT_EQ(a.unit, std::string("seconds"));
}
