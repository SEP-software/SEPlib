#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "floatFilter.h"
using std::string;
using namespace SEP;
using namespace SEP::filter;

TEST(filt1D, oneDConv) {
  std::vector<int> box(1, 3), beg(1, 0);
  std::shared_ptr<rectFilter1D> filt(new rectFilter1D(box, beg));
  (*filt->_mat)[0] = .5;
  (*filt->_mat)[1] = .3;
  (*filt->_mat)[2] = .1;
  floatFilter1D filtOp = floatFilter1D(filt);
  std::shared_ptr<float1DReg> in(new float1DReg(10)), out(new float1DReg(10));
  (*in->_mat)[5] = 1;
  filtOp.applyInOut(in, out);
  float *o = out->getVals();
  for (int i = 0; i < 4; i++) ASSERT_EQ(0, o[i]);

  ASSERT_EQ(o[5], 0.5);
  ASSERT_LE(fabs(o[6] - .3), 0.001);
  ASSERT_LE(fabs(o[7] - .1), 0.001);
  ASSERT_EQ(o[8], .0);
  ASSERT_EQ(o[9], .0);
}
TEST(filt1D, twoDConv) {
  std::vector<int> box(1, 3), beg(1, 0);
  std::shared_ptr<rectFilter1D> filt(new rectFilter1D(box, beg));
  (*filt->_mat)[0] = .5;
  (*filt->_mat)[1] = .3;
  (*filt->_mat)[2] = .1;
  floatFilter1D filtOp = floatFilter1D(filt);
  std::shared_ptr<float2DReg> in(new float2DReg(10, 3)),
      out(new float2DReg(10, 3));
  (*in->_mat)[0][5] = 1;
  (*in->_mat)[1][4] = 1;
  (*in->_mat)[2][3] = 1;

  filtOp.applyInOut(in, out);
  float *o = out->getVals();

  for (int i2 = 0; i2 < 3; i2++) {
    ASSERT_EQ(o[5 - i2 + i2 * 10], 0.5);
    ASSERT_LE(fabs(o[6 - i2 + i2 * 10] - .3), 0.001);
    ASSERT_LE(fabs(o[7 - i2 + i2 * 10] - .1), 0.001);
  }
}