#include <gtest/gtest.h>  // googletest header file

#include <string>
#include "calcBlock.h"
using std::string;
using namespace SEP;
using namespace SEP::blocking;

TEST(calcBlock, simple) {
  std::vector<int> nd(3, 1000);
  blockSizeCalc x = blockSizeCalc(4000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd, 1, 4));

  std::vector<int> nv = x.getBlockSize(std::string("single"));
  std::cerr << nv[0] << " " << nv[1] << " " << nv[2] << " " << std::endl;
}
