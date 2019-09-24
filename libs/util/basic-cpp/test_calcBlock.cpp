#include <gtest/gtest.h>  // googletest header file

#include <string>
#include "calcBlock.h"
using std::string;
using namespace SEP;
using namespace SEP::blocking;

TEST(calcBlock, simpleAll) {
  std::vector<int> nd(3, 1000);
  blockSizeCalc x = blockSizeCalc(99000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd, 1, 4));
  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 1000);
}
TEST(calcBlock, simpleSome) {
  std::vector<int> nd(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd, 1, 4));
  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 125);
}
TEST(calcBlock, simpleSome2) {
  std::vector<int> nd(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd, 2, 4));
  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 125);
}

TEST(calcBlock, error) {
  std::vector<int> nd(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd, 3, 4));
  ASSERT_ANY_THROW(x.calcBlocks());
}

TEST(calcBlock, multi1) {
  std::vector<int> nd1(3, 1000), nd2(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  ASSERT_NO_THROW(x.addData("single", nd1, 1, 4));
  ASSERT_NO_THROW(x.addData("second", nd2, 1, 4));

  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 62);
}

TEST(calcBlock, multi2) {
  std::vector<int> nd1(3, 1000), nd2(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  nd2[0] = 500;
  ASSERT_NO_THROW(x.addData("single", nd1, 1, 4));
  ASSERT_NO_THROW(x.addData("second", nd2, 1, 4));

  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 83);
}
TEST(calcBlock, multi3) {
  std::vector<int> nd1(3, 1000), nd2(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  nd2[0] = 500;
  nd2[0] = 400;
  ASSERT_NO_THROW(x.addData("single", nd1, 2, 4));
  ASSERT_NO_THROW(x.addData("second", nd2, 2, 4));

  ASSERT_NO_THROW(x.calcBlocks());
  std::vector<int> nv = x.getBlockSize(std::string("single"));
  ASSERT_EQ(nv.size(), 3);
  ASSERT_EQ(nv[0], 1000);
  ASSERT_EQ(nv[1], 1000);
  ASSERT_EQ(nv[2], 89);
}

TEST(calcBlock, multi4) {
  std::vector<int> nd1(3, 1000), nd2(3, 1000);
  blockSizeCalc x = blockSizeCalc(1000l * 1000l * 1000l);
  nd2[1] = 500;
  ASSERT_NO_THROW(x.addData("single", nd1, 1, 4));
  ASSERT_NO_THROW(x.addData("second", nd2, 1, 4));

  ASSERT_ANY_THROW(x.calcBlocks());
}