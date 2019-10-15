#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "nmo.h"
using std::string;
using namespace SEP;
using namespace SEP::velocity;

TEST(nmo, simple) {
  axis axisT = axis(2000, .0, .004);
  axis axisO = axis(2, 0, 4.);
  axis axisC = axis(1, 0, 4.);

  std::shared_ptr<float3DReg> in(new float3DReg(axisT, axisO, axisC)),
      out(new float3DReg(axisT, axisO, axisC));

  (*in->_mat)[0][0][750] = 1.;
  (*in->_mat)[0][1][1250] = 1.;

  std::shared_ptr<vel3DConstant> vel(new vel3DConstant(1.));

  // t^2 =t^0 + off^/vel^2
  //  26 = 9 + 16

  std::vector<int> ioff;
  ioff.push_back(2);

  nmoRegCube nm = nmoRegCube(vel, axisT, ioff, 3, -1);

  nm.applyInOut(in, out);

  ASSERT_LE(fabs((*out->_mat)[0][0][750] - 1.), 0.001);
  ASSERT_LE(fabs((*out->_mat)[0][1][750] - 1.), 0.001);
}
TEST(nmo, inverse) {
  axis axisT = axis(2000, .0, .004);
  axis axisO = axis(2, 0, 4.);
  axis axisC = axis(1, 0, 4.);

  std::shared_ptr<float3DReg> in(new float3DReg(axisT, axisO, axisC)),
      out(new float3DReg(axisT, axisO, axisC));

  (*in->_mat)[0][0][750] = 1.;
  (*in->_mat)[0][1][750] = 1.;

  std::shared_ptr<vel3DConstant> vel(new vel3DConstant(1.));

  // t^2 =t^0 + off^/vel^2
  //  26 = 9 + 16

  std::vector<int> ioff;
  ioff.push_back(2);
  std::cerr << "finished" << std::endl;

  nmoRegCube nm = nmoRegCube(vel, axisT, ioff, 3, -1);
  nm.doInverse(true);
  nm.applyInOut(in, out);
  std::cerr << "finished" << std::endl;

  ASSERT_LE(fabs((*out->_mat)[0][0][750] - 1.), 0.001);
  ASSERT_LE(fabs((*out->_mat)[0][1][1250] - 1.), 0.001);
  std::cerr << "finished" << std::endl;
}
