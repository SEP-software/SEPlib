#include "basicLoop.h"
#include <thread>
#include "SEPException.h"
#include "regVector.h"
using namespace SEP::loop;
std::vector<windP> basicLoop::createLoop(const std::vector<int> nblock) {
  int ndim = _nw.size();
  std::vector<int> n = create9(_n, 1);
  std::vector<int> nw = create9(_nw, 1);
  std::vector<int> fw = create9(_fw, 1);
  std::vector<int> jw = create9(_jw, 1);
  std::vector<int> b = create9(nblock, 1);

  for (auto i = 0; i < n.size(); i++) {
    checkLogic(n[i], nw[i], fw[i], jw[i], b[i]);
  }

  std::vector<int> fin(9), jin(9), nin(9), nd(9, 0);
  std::vector<windP> windTmp, wind;
  // Loop over input
  fin[8] = fw[8];
  while (nd[8] < nw[8]) {
    nin[8] = std::min(nw[8] - nd[8], b[8]);
    fin[7] = fw[7];

    while (nd[7] < nw[7]) {
      nin[7] = std::min(nw[7] - nd[7], b[7]);
      fin[6] = fw[6];

      while (nd[6] < nw[6]) {
        nin[6] = std::min(nw[6] - nd[6], b[6]);
        fin[5] = fw[5];

        while (nd[5] < nw[5]) {
          nin[5] = std::min(nw[5] - nd[5], b[5]);

          fin[4] = fw[4];
          while (nd[4] < nw[4]) {
            nin[4] = std::min(nw[4] - nd[4], b[4]);

            fin[3] = fw[3];
            while (nd[3] < nw[3]) {
              nin[8] = std::min(nw[3] - nd[3], b[3]);
              fin[2] = fw[2];

              while (nd[2] < nw[2]) {
                nin[2] = std::min(nw[2] - nd[2], b[2]);
                fin[1] = fw[1];

                while (nd[1] < nw[1]) {
                  nin[1] = std::min(nw[1] - nd[1], b[1]);
                  fin[0] = fw[0];

                  while (nd[0] < nw[0]) {
                    nin[0] = std::min(nw[0] - nd[0], b[0]);
                    windTmp.push_back(windP(nin, fin, jw));
                    fin[0] += nin[0] * jw[0];
                  }
                  fin[1] += nin[1] * jw[1];
                }
                fin[2] += nin[2] * jw[2];
              }
              fin[3] += nin[3] * jw[3];
            }
            fin[4] += nin[4] * jw[4];
          }
          fin[5] += nin[5] * jw[5];
        }
        fin[6] += nin[6] * jw[6];
      }
      fin[7] += nin[7] * jw[7];
    }
    fin[8] += nin[8] * jw[8];
  }
  for (auto i = 0; i < windTmp.size(); i++) {
    windTmp[i]._nw.resize(ndim);
    windTmp[i]._fw.resize(ndim);
    windTmp[i]._jw.resize(ndim);
    wind.push_back(windP(windTmp[i]._nw, windTmp[i]._fw, windTmp[i]._jw));
  }
  return wind;
}

void blockIO::storeParams(const std::vector<int> nIn,
                          const std::vector<int> nOut,
                          const std::vector<int> nw, const std::vector<int> fw,
                          const std::vector<int> jw,
                          const std::vector<int> nbIn,
                          const std::vector<int> nbOut) {
  if (nbIn.size() < nIn.size())
    throw SEPException(
        "Blocksize dimension less than data size dimension (input)");

  if (nbOut.size() < nOut.size())
    throw SEPException(
        "Blocksize dimension less than data size dimension (output)");

  int inMaxAll = 0, outMaxAll = 0;
  for (int i = 0; i < nbIn.size(); i++) {
    if (nbIn[i] == nIn[i]) inMaxAll = i;
  }

  for (int i = 0; i < nbOut.size(); i++) {
    if (nbOut[i] == nOut[i]) outMaxAll = i;
  }
  if (nIn.size() - inMaxAll != nOut.size() - outMaxAll)
    throw SEPException("Number of axes beyond block size not equal");

  // We aren't holding entire last axis in memory
  if (nbIn.size() - 1 != inMaxAll) {
    if (nbIn[inMaxAll + 1] != nbOut[outMaxAll + 1])
      throw SEPException(
          "The block size of non complete axis must be the same size");
    if (nIn[inMaxAll + 1] == nOut[outMaxAll + 1])
      throw SEPException("The axis size of non complete axis not the same");
  }
  std::shared_ptr<basicLoop> basic(new SEP::loop::basicLoop(nIn, nw, fw, jw));
  _loopIn = basic->createLoop(nbIn);

  std::shared_ptr<basicLoop> basic2(new SEP::loop::basicLoop(nOut, nw, fw, jw));
  _loopOut = basic2->createLoop(nbOut);
}
std::vector<int> basicLoop::create9(const std::vector<int> x,
                                    const int def) const {
  std::vector<int> xx(9, def);
  for (auto i = 0; i < x.size(); i++) xx[i] = x[i];
  return xx;
}
void basicLoop::checkLogic(const int n, const int nw, const int fw,
                           const int jw, const int b) const {
  if (jw < 1) throw SEPException("J can not be less than 1");
  if (fw < 0) throw SEPException("f can not be less than 0");
  if (fw + jw * (nw - 1) > n - 1)
    throw SEPException("f,j,n window params exceed the n");
}

void blockIO::loopDataInOut(std::shared_ptr<SEP::genericRegFile> in,
                            std::shared_ptr<SEP::genericRegFile> out) {
  std::shared_ptr<SEP::hypercube> _hyper = in->getHyper();

  loopData(in, out);
}

/*!
  Create hypercube given window parameters */
std::shared_ptr<SEP::hypercube> blockIOReg::createSubset(
    const std::vector<int> nw, const std::vector<int> fw,
    const std::vector<int> jw) {
  std::vector<SEP::axis> axes = _hyper->getAxes();
  for (int i = 0; i < axes.size(); i++) {
    axes[i].o += axes[i].d * fw[i];
    axes[i].n = nw[i];
    axes[i].d *= jw[i];
  }
  std::shared_ptr<SEP::hypercube> hyp(new SEP::hypercube(axes));
  return hyp;
}

void blockIOReg::loopData(std::shared_ptr<SEP::genericRegFile> in,
                          std::shared_ptr<SEP::genericRegFile> out) {
  bool doIn = false, doOut = false;
  if (in) doIn = true;
  if (out) doOut = true;

  std::thread readT, writeT;
  std::shared_ptr<SEP::regSpace> windIn, windOut, tmp;

  auto readF = [&](std::shared_ptr<SEP::regSpace> array,
                   const std::vector<int> nw, const std::vector<int> fw,
                   const std::vector<int> jw) {
    _inF->readWindow(nw, fw, jw, array);
  };
  auto writeF = [&](std::shared_ptr<SEP::regSpace> array,
                    const std::vector<int> nw, const std::vector<int> fw,
                    const std::vector<int> jw) {
    std::shared_ptr<SEP::regSpace> tmp = SEP::cloneRegSpace(array);

    _outF->writeWindow(nw, fw, jw, tmp);
  };

  if (doIn) {
    // Begin by starting a read for the first section
    tmp = SEP::vecFromHyper(
        createSubset(_loopIn[0]._nw, _loopIn[0]._fw, _loopIn[0]._jw),
        in->getDataType());
    readT =
        std::thread(readF, tmp, _loopIn[0]._nw, _loopIn[0]._fw, _loopIn[0]._jw);
  }

  // Loop over output space
  for (int iout = 0; iout < _loopIn.size(); iout++) {
    if (doOut) {
      // Create  the output
      std::shared_ptr<SEP::regSpace> windOut =
          SEP::vecFromHyper(createSubset(_loopOut[iout]._nw, _loopOut[iout]._fw,
                                         _loopOut[iout]._jw),
                            out->getDataType());
    }
    if (doIn) {
      readT.join();
      windIn = SEP::cloneRegSpace(tmp);
      if (iout + 1 != _loopIn.size()) {
        tmp = vecFromHyper(
            createSubset(_loopIn[iout + 1]._nw, _loopIn[iout + 1]._fw,
                         _loopIn[iout + 1]._jw),
            in->getDataType());
        readT = std::thread(readF, tmp, _loopIn[iout + 1]._nw,
                            _loopIn[iout + 1]._fw, _loopIn[iout + 1]._jw);
      }

      if (doOut) {
        applyInOut(windIn, windOut);
      } else
        applyIn(windIn);
    } else
      applyOut(windOut);

    if (doOut) {
      if (iout != 0) writeT.join();
      writeT = std::thread(writeF, windOut, _loopOut[iout]._nw,
                           _loopOut[iout]._fw, _loopOut[iout]._jw);
    }
  }
  if (doOut) writeT.join();
}
