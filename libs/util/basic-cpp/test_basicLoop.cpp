#include <gtest/gtest.h>  // googletest header file
#include <string>
#include "basicLoop.h"
#include "calcBlock.h"
#include "float3DReg.h"
#include "genericIO.h"
#include "hypercube.h"
#include "ioModes.h"
#include "memoryFile.h"
using std::string;
using namespace SEP;
class simpleScaling : public SEP::loop::blockIOReg {
 public:
  simpleScaling(const std::vector<int> nd, const std::vector<int> nb) {
    std::vector<int> fw(3, 0), jw(3, 1);
    storeParams(nd, nd, fw, jw, nb);
  }
  virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                          std::shared_ptr<SEP::regSpace> out) {
    std::shared_ptr<SEP::float3DReg> in3D =
                                         std::dynamic_pointer_cast<float3DReg>(
                                             in),
                                     out3D =
                                         std::dynamic_pointer_cast<float3DReg>(
                                             out);
    ASSERT_TRUE(in3D);
    ASSERT_TRUE(out3D);
    float *outv = out3D->getVals(), *inv = in3D->getVals();
    for (auto i = 0; i < in3D->getHyper()->getN123(); i++) {
      outv[i] = inv[i] * 2.;
    }
  }
};

std::vector<float> createArrayF(const int n1, const int n2, const int n3) {
  long long n123 = (long long)n1 * (long long)n2 * (long long)n3;
  std::vector<float> buf(n123);
  long long i = 0;
  for (int i3 = 0; i3 < n3; i3++) {
    for (int i2 = 0; i2 < n2; i2++) {
      for (int i1 = 0; i1 < n1; i1++, i++) {
        buf[i] = i1 + i2 * 100 + i3 * 100 * 100;
      }
    }
  }
  return buf;
}
void checkArrayF(const float *buf, const int n1, const int f1, const int j1,
                 const int n2, const int f2, const int j2, const int n3,
                 const int f3, const int j3) {
  long long i = 0;
  for (int i3 = 0; i3 < n3; i3++) {
    for (int i2 = 0; i2 < n2; i2++) {
      for (int i1 = 0; i1 < n1; i1++, i++) {
        EXPECT_EQ(buf[i], 2 * ((f1 + i1 * j1) + (f2 + i2 * j2) * 00 +
                               (f3 + j3 * i3) * 100 * 100));
      }
    }
  }
}

TEST(calcBlock, simpleAll) {
  std::cerr << "what 1 " << std::endl;
  std::vector<std::string> pars;
  ioModes mode = ioModes(pars);
  std::shared_ptr<genericIO> io = mode.getIO("memory");
  std::cerr << "what 1 " << std::endl;

  std::shared_ptr<genericRegFile> inF = io->getRegFile("in", usageIn);
  std::shared_ptr<genericRegFile> outF = io->getRegFile("out", usageIn);
  std::shared_ptr<memoryRegFile> outM =
      std::dynamic_pointer_cast<memoryRegFile>(outF);
  outF->setDataType(DATA_FLOAT);
  std::shared_ptr<hypercube> hyper(new hypercube(10, 10, 10));
  inF->setHyper(hyper);
  outF->setHyper(hyper);
  std::cerr << "what 1 " << std::endl;

  std::vector<float> buf1 = createArrayF(10, 10, 10);
  inF->writeFloatStream(buf1.data(), 1000);
  std::vector<int> nd(3, 10);
  std::cerr << "what 1 " << std::endl;

  SEP::blocking::blockSizeCalc bl(16000);
  std::cerr << "what 1 " << std::endl;

  bl.addData("input", nd, 1, 4);
  bl.addData("output", nd, 1, 4);
  std::cerr << "what 1 " << std::endl;

  bl.calcBlocks();
  std::cerr << "what 2" << std::endl;

  std::vector<int> nb = bl.getBlockSize("input");
  simpleScaling scale = simpleScaling(nd, nb);
  std::cerr << "what 3 " << std::endl;

  scale.loopData(inF, outF);
  std::vector<float> buf2(1000);

  checkArrayF(buf2.data(), 10, 0, 1, 10, 0, 1, 10, 0, 1);
}

/*
class basicLoop {
 public:
op() { ; }

  basicLoop(const std::vector<int> n, const std::vector<int> nw,
            const std::vector<int> fw, const std::vector<int> jw) {
    storeParams(n, nw, fw, jw);
  }

  void storeParams(const std::vector<int> n, const std::vector<int> nw,
                   const std::vector<int> fw, const std::vector<int> jw) {
    _n = n;
    _nw = nw;
    _fw = fw;
    _jw = jw;
  }


  std::vector<int> create9(const std::vector<int> x, const int def) const;

  std::vector<windP> createLoop(const std::vector<int> nblock);


  void checkLogic(const int n, const int nw, const int fw, const int jw,
                  const int b) const;

  std::vector<int> _n, _fw, _nw, _jw;  ///< Size, window n,f,j

  int _ndata;
};


class blockIO {
 public:
  blockIO() { ; }

  void storeParams(const std::vector<int> n, const std::vector<int> nw,
                   const std::vector<int> fw, const std::vector<int> jw,
                   const std::vector<int> nbIn) {
    std::shared_ptr<SEP::loop::basicLoop> basic(
        new SEP::loop::basicLoop(n, nw, fw, jw));
    _loopIn = basic->createLoop(nbIn);
    _loopOut = basic->createLoop(nbIn);
  }

  void storeParams(const std::vector<int> nIn, const std::vector<int> nOut,
                   const std::vector<int> nw, const std::vector<int> fw,
                   const std::vector<int> jw, const std::vector<int> nbIn,
                   const std::vector<int> nbOut);


  virtual void loopData(std::shared_ptr<SEP::genericRegFile> in,
                        std::shared_ptr<SEP::genericRegFile> out) {
    throw SEPException("Loop through data applying operator");
  }


  virtual void loopDataInOut(std::shared_ptr<SEP::genericRegFile> in,
                             std::shared_ptr<SEP::genericRegFile> out);



  virtual void loopDataIn(std::shared_ptr<SEP::genericRegFile> in) {
    _inF = in;
    _hyperIn = in->getHyper();
    loopData(in, nullptr);
  }


  virtual void applyIn(const std::shared_ptr<SEP::regSpace> in) {
    throw SEPException("Must override applyIn");
  }


  virtual void applyOut(std::shared_ptr<SEP::regSpace> out) {
    throw SEPException("Must override applyOut");
  }

  virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                          std::shared_ptr<SEP::regSpace> out) {
    throw SEPException("Must override applyInOut");
  }

  virtual void loopDataOut(std::shared_ptr<SEP::genericRegFile> out) {
    _outF = out;
    _hyperOut = out->getHyper();
    loopData(nullptr, out);
  }

  virtual std::shared_ptr<hypercube> createHyperOut(
      const std::shared_ptr<hypercube> hyperIn) {
    throw SEPException("Must override createHyperOut");
  }


  virtual int getMinDims() { throw SEPException("Must override getMinDims"); }


  virtual SEP::dataType getDataTypeIn() { return SEP::DATA_FLOAT; }


  virtual SEP::dataType getDataTypeOut() { return SEP::DATA_FLOAT; }

  virtual long long getExtraMem() { return 0; }


  virtual windP getInputSize(const windP &window) {
    throw SEPException("Must override getMaxInputSize");
  }

  std::shared_ptr<SEP::hypercube> getHyperIn() { return _hyperIn; }
  /
  std::shared_ptr<SEP::hypercube> getHyperOut() { return _hyperOut; }

 protected:
  std::shared_ptr<SEP::genericRegFile> _inF, _outF;
  std::shared_ptr<SEP::hypercube> _hyperIn, _hyperOut;
  std::vector<SEP::loop::windP> _loopIn, _loopOut;
};
class blockIOReg : public blockIO {
 public:
  blockIOReg() { ; }


  virtual void loopData(std::shared_ptr<SEP::genericRegFile> in,
                        std::shared_ptr<SEP::genericRegFile> out);

  virtual std::shared_ptr<SEP::hypercube> createSubset(
      std::shared_ptr<SEP::hypercube> hyper, const std::vector<int> nw,
      const std::vector<int> fw, const std::vector<int> jw);
};

class blockIORegPipe : public blockIOReg {
 public:
  blockIORegPipe() { ; }

  void setupPipe(std::shared_ptr<SEP::genericRegFile> inF,
                 std::shared_ptr<SEP::genericRegFile> outF,
                 std::vector<std::shared_ptr<blockIOReg>> &ops,
                 const long long maxM);

  virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                          std::shared_ptr<SEP::regSpace> out);


  long long testHoldInMemory(const long long mem, std::vector<int> outputSize);

 private:
  std::vector<std::shared_ptr<blockIOReg>> _ops;
  std::vector<std::vector<SEP::loop::windP>> _loopMid;
};


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
*/