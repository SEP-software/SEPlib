#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "vel3D.h"
using std::string;
using namespace SEP;
using namespace SEP::velocity;

TEST(vel3dconstant, getVel) {
  vel3DConstant vel(2.);

  std::vector<float> v = vel.getVelocity(10, 0., .004, 1., 1.);

  for (int i = 0; i < 10; i++) ASSERT_EQ(v[i], 2.);
}
