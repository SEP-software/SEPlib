#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>
#include <thread>

#include "SEPException.h"
#include "stack.h"

void SEP::filter::floatStackSpreadReg::applyIt(std::shared_ptr<regSpace> in,
                                               std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_pointer_cast<floatHyper>(in),
                              outF = std::dynamic_pointer_cast<floatHyper>(out);
  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");
  std::vector<axis> inA = inF->getHyper()->getAxes(),
                    outA = outF->getHyper()->getAxes(), smallA, bigA;
  if (_adj) {
    smallA = inF->getHyper()->getAxes();
    bigA = outF->getHyper()->getAxes();
    if (outF->getHyper()->getNdimG1() - inF->getHyper()->getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  } else {
    bigA = outF->getHyper()->getAxes();
    smallA = inF->getHyper()->getAxes();
    if (inF->getHyper()->getNdimG1() - outF->getHyper()->getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  }
  std::vector<int> ns(8, 1);
  long long n123 = 1;
  for (int i = 0; i < smallA.size(); i++) {
    ns[i] = smallA[i].n;
    n123 *= ns[i];
  }
  if (bigA.size() > 5)
    throw SEPException("Can only handle stack over 5 dimensions");

  std::vector<int> n(5, 0), b(5, 0), j(5, 1);
  long long nb = 1;

  int ismall = 0;
  int istack = 0;
  for (auto i = 0; i < bigA.size(); i++) {
    bool found = false;
    for (auto iax = 0; iax < _iaxes.size(); iax++) {
      if (_iaxes[iax] < 0 || _iaxes[iax] >= bigA.size())
        throw SEPException(std::string("Unacceptable axis ") +
                           std::to_string(_iaxes[iax]) +
                           std::string(" is outside axis range"));

      if (i == _iaxes[iax]) found = true;
    }
    if (found) {
      if (bigA[i].n != smallA[ismall].n)
        throw SEPException(std::string("Axis ") + std::to_string(i + 1) +
                           std::string(" of big size not equal to axis ") +
                           std::to_string(ismall + 1) +
                           std::string(" of small "));
      ismall += 1;
    } else {
      n[istack] = bigA[i].n;
      j[istack] = nb;
      istack += 1;
    }
    nb = nb * bigA[i].n;
  }
  float *outV = outF->getVals(), *inV = inF->getVals();
  if (_adj) {
    tbb::parallel_for(tbb::blocked_range<int>(0, n123),
                      [&](const tbb::blocked_range<int> &r) {
                        for (int iy = r.begin(); iy != r.end(); ++iy) {
                          outV[iy] = 0;
                          for (int i4 = 0; i4 < n[4]; i4++) {
                            long long b4 = i4 * j[4];
                            for (int i3 = 0; i3 < n[3]; i3++) {
                              long long b3 = b4 + i3 * j[3];
                              for (int i2 = 0; i2 < n[2]; i2++) {
                                long long b2 = b3 + i2 * j[2];
                                for (int i1 = 0; i1 < n[1]; i1++) {
                                  long long b1 = b2 + j[1];
                                  for (int i0 = 0; i0 < n[0]; i0++) {
                                    outV[iy] += inV[iy + b1 + i0 * j[0]];
                                  }
                                }
                              }
                            }
                          }
                        }
                      });
  } else {
    tbb::parallel_for(tbb::blocked_range<int>(0, n123),
                      [&](const tbb::blocked_range<int> &r) {
                        for (int iy = r.begin(); iy != r.end(); ++iy) {
                          for (int i4 = 0; i4 < n[4]; i4++) {
                            long long b4 = i4 * j[4];
                            for (int i3 = 0; i3 < n[3]; i3++) {
                              long long b3 = b4 + i3 * j[3];
                              for (int i2 = 0; i2 < n[2]; i2++) {
                                long long b2 = b3 + i2 * j[2];
                                for (int i1 = 0; i1 < n[1]; i1++) {
                                  long long b1 = b2 + j[1];
                                  for (int i0 = 0; i0 < n[0]; i0++) {
                                    inV[iy + b1 + i0 * j[0]] = outV[iy];
                                  }
                                }
                              }
                            }
                          }
                        }
                      });
  }
}