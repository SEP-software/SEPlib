#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "basicLoop.h"
#include "calcBlock.h"
#include "float3DReg.h"
#include "genericIO.h"
#include "hypercube.h"
#include "ioModes.h"
#include "memoryFile.h"

#include "spike.h"

using std::string;
using namespace SEP;
using namespace SEP::model;

TEST(spike, singleWhole) {
  std::shared_ptr<float3DReg> out(new float3DReg(10, 10, 10));

  std::map<int, int> loc;
  loc[0] = 5;
  loc[1] = 5;
  loc[2] = 5;
  spikeVal sp(2., loc);
  std::vector<spikeVal> vals;
  vals.push_back(sp);
  std::shared_ptr<hypercube> hyper(new hypercube(10, 10, 10));
  floatSpike op(hyper, vals);
  op.applyOut(out);
  for (int i3 = 0; i3 < 10; i3++) {
    for (int i2 = 0; i2 < 10; i2++) {
      for (int i1 = 0; i1 < 10; i1++) {
        if (i1 == 5 && i2 == 5 && i3 == 5)
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1] - 2.), .01);
        else
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1]), .01);
      }
    }
  }
}

TEST(spike, plane) {
  std::shared_ptr<float3DReg> out(new float3DReg(10, 10, 10));

  std::map<int, int> loc;
  loc[1] = 5;
  loc[2] = 5;
  spikeVal sp(2., loc);
  std::vector<spikeVal> vals;
  vals.push_back(sp);
  std::shared_ptr<hypercube> hyper(new hypercube(10, 10, 10));
  floatSpike op(hyper, vals);
  op.applyOut(out);
  for (int i3 = 0; i3 < 10; i3++) {
    for (int i2 = 0; i2 < 10; i2++) {
      for (int i1 = 0; i1 < 10; i1++) {
        if (i2 == 5 && i3 == 5)
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1] - 2.), .01);
        else
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1]), .01);
      }
    }
  }
}
TEST(spike, singlePart) {
  std::map<int, int> loc;
  loc[0] = 15;
  loc[1] = 15;
  loc[2] = 15;
  spikeVal sp(2., loc);
  std::vector<spikeVal> vals;
  vals.push_back(sp);
  std::vector<axis> axes;
  axes.push_back(axis(10, 10., 1.));
  axes.push_back(axis(10, 10., 1.));
  axes.push_back(axis(10, 10., 1.));

  std::shared_ptr<hypercube> hyper(new hypercube(20, 20, 20)),
      hyperSmall(new hypercube(axes));
  std::shared_ptr<float3DReg> out(new float3DReg(hyperSmall));

  floatSpike op(hyper, vals);
  op.applyOut(out);
  for (int i3 = 0; i3 < 10; i3++) {
    for (int i2 = 0; i2 < 10; i2++) {
      for (int i1 = 0; i1 < 10; i1++) {
        if (i1 == 5 && i2 == 5 && i3 == 5)
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1] - 2.), .01);
        else
          ASSERT_LE(fabs((*out->_mat)[i3][i2][i1]), .01);
      }
    }
  }
}
TEST(spike, loop) {
  std::vector<std::string> pars;
  ioModes mode = ioModes(pars);
  std::shared_ptr<genericIO> io = mode.getIO("memory");

  std::shared_ptr<genericRegFile> outF = io->getRegFile("out", usageOut);
  std::cerr << "what is going on" << std::endl;

  outF->setDataType(DATA_FLOAT);
  std::shared_ptr<hypercube> hyper(new hypercube(20, 20, 20));
  std::shared_ptr<memoryRegFile> outM =
      std::dynamic_pointer_cast<memoryRegFile>(outF);

  std::cerr << "what is going on" << std::endl;
  outF->setHyper(hyper);
  std::cerr << "what is going on" << std::endl;

  std::shared_ptr<hypercube> hyp = outF->getHyper();

  SEP::blocking::blockSizeCalc bl(200);

  std::vector<int> nd(3, 20), fw(3, 0), jw(3, 1);
  bl.addData("output", nd, 1, 4);
  bl.calcBlocks();
  std::vector<int> nb = bl.getBlockSize("output");

  std::map<int, int> loc;
  loc[0] = 15;
  loc[1] = 15;
  loc[2] = 15;
  spikeVal sp(2., loc);
  std::vector<spikeVal> vals;
  vals.push_back(sp);

  floatSpike op(hyper, vals);
  op.storeParams(nd, nd, fw, jw, nb);

  op.loopDataOut(outF);
  std::shared_ptr<memoryRegFile> xx =
      std::dynamic_pointer_cast<memoryRegFile>(outF);
  int ii = 0;
  float *x = (float *)xx->getPtr();
  for (int i3 = 0; i3 < 20; i3++) {
    for (int i2 = 0; i2 < 20; i2++) {
      for (int i1 = 0; i1 < 20; i1++, ii++) {
        if (i1 == 15 && i2 == 15 && i3 == 15)
          ASSERT_LE(fabs(x[ii] - 2.), .01);
        else
          ASSERT_LE(fabs(x[ii]), .01);
      }
    }
  }
}