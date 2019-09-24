#include <gtest/gtest.h>  // googletest header file

#include <string>
#include "hypercube.h"
using std::string;
using namespace SEP;

class simpleBlockIOReg1 : public blockIOReg {
 public:
  virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                          std::shared_ptr<SEP::regSpace> out) {
    std::shared_ptr<SEP::float1DReg> in1D = std::dynamic_cast<float1DReg>(in),
                                     out1D = std::dynamic_cast<float1DReg>(out);
  }
};

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