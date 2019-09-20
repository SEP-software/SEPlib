#include <gtest/gtest.h>  // googletest header file

#include <string>
#include "calcBlock.h"
using std::string;
using namespace SEP;

TEST(calcBlock, simple) {
  std::vector<int> nd(3, 1000);
  x = blockSizeCalc(4000 * 1000, 1000);
  ASSERT_NO_THROW(x.addData("single", nd, 1, 4));
  std::cerr << x._datas["single"]._nbs[0] << " " << x._datas["single"]._nbs[1]
            << " " << x._datas["single"]._nbs[2] << " " << std::endl;
}
