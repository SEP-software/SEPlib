#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "stack.h"
using std::string;
using namespace SEP;
using namespace SEP::filter;

TEST(stackF, inner) {
  std::shared_ptr<float2DReg> in(new float2DReg(10, 3));
  std::shared_ptr<float1DReg> out(new float1DReg(3));
  for (int i2 = 0; i2 < 3; i2++) {
    for (int i1 = 0; i1 < 10; i1++) {
      (*in->_mat)[i2][i1] = i1 + 100 * i2;
    }
  }

  std::vector<int> iax(1, 0);
  floatStackSpreadReg stack(iax, true);

  stack.applyInOut(in, out);
  float *o = out->getVals();

  ASSERT_LE(fabs(o[0] - 45), .01);
  ASSERT_LE(fabs(o[1] - 1045), .01);
  ASSERT_LE(fabs(o[2] - 2045), .01);
}
TEST(stackF, outer) {
  std::shared_ptr<float2DReg> in(new float2DReg(10, 3));
  std::shared_ptr<float1DReg> out(new float1DReg(10));
  for (int i2 = 0; i2 < 3; i2++) {
    for (int i1 = 0; i1 < 10; i1++) {
      (*in->_mat)[i2][i1] = i1 + 100 * i2;
    }
  }

  std::vector<int> iax(1, 1);
  floatStackSpreadReg stack(iax, true);

  stack.applyInOut(in, out);
  float *o = out->getVals();
  for (int i = 0; i < 10; i++) {
    ASSERT_LE(fabs(o[i] - 300 - i * 3), .01);
  }
}

TEST(fourD, inner) {
  std::shared_ptr<float4DReg> in(new float4DReg(3, 3, 3, 3));
  std::shared_ptr<float3DReg> out(new float3DReg(3, 3, 3));
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i3 = 0; i3 < 3; i3++) {
      for (int i2 = 0; i2 < 3; i2++) {
        for (int i1 = 0; i1 < 3; i1++) {
          (*in->_mat)[i4][i3][i2][i1] = i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
      }
    }
  }

  std::vector<int> iax(1, 0);
  floatStackSpreadReg stack(iax, true);

  stack.applyInOut(in, out);
  float *o = out->getVals();

  int ii = 0;
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i3 = 0; i3 < 3; i3++) {
      for (int i2 = 0; i2 < 3; i2++, ii++) {
        float t = 0;
        for (int i1 = 0; i1 < 3; i1++) {
          t += i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
        ASSERT_LE(fabs(o[ii] - t), .01);
      }
    }
  }
}
TEST(fourD, inner2) {
  std::shared_ptr<float4DReg> in(new float4DReg(3, 3, 3, 3));
  std::shared_ptr<float2DReg> out(new float2DReg(3, 3));
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i3 = 0; i3 < 3; i3++) {
      for (int i2 = 0; i2 < 3; i2++) {
        for (int i1 = 0; i1 < 3; i1++) {
          (*in->_mat)[i4][i3][i2][i1] = i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
      }
    }
  }

  std::vector<int> iax(2, 0);
  iax[1] = 1;
  floatStackSpreadReg stack(iax, true);

  stack.applyInOut(in, out);
  float *o = out->getVals();

  int ii = 0;
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i3 = 0; i3 < 3; i3++, ii++) {
      float t = 0;
      for (int i2 = 0; i2 < 3; i2++) {
        for (int i1 = 0; i1 < 3; i1++) {
          t += i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
      }
      ASSERT_LE(fabs(o[ii] - t), .01);
    }
  }
}

TEST(fourD, in2) {
  std::shared_ptr<float4DReg> in(new float4DReg(3, 3, 3, 3));
  std::shared_ptr<float2DReg> out(new float2DReg(3, 3));
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i3 = 0; i3 < 3; i3++) {
      for (int i2 = 0; i2 < 3; i2++) {
        for (int i1 = 0; i1 < 3; i1++) {
          (*in->_mat)[i4][i3][i2][i1] = i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
      }
    }
  }

  std::vector<int> iax(2, 0);
  iax[1] = 2;
  floatStackSpreadReg stack(iax, true);

  stack.applyInOut(in, out);
  float *o = out->getVals();

  int ii = 0;
  for (int i4 = 0; i4 < 3; i4++) {
    for (int i2 = 0; i2 < 3; i2++, ii++) {
      float t = 0;
      for (int i3 = 0; i3 < 3; i3++) {
        for (int i1 = 0; i1 < 3; i1++) {
          t += i1 + 10 * i2 + i3 * 100 + i4 * 1000;
        }
      }
      ASSERT_LE(fabs(o[ii] - t), .01);
    }
  }
}
