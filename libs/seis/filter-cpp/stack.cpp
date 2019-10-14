#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>
#include <algorithm>
#include <thread>
#include "SEPException.h"

#include "stack.h"

void SEP::filter::floatStackSpreadReg::applyInOut(
    std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_pointer_cast<floatHyper>(in),
                              outF = std::dynamic_pointer_cast<floatHyper>(out);

  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");

  std::vector<axis> inA = inF->getHyper()->getAxes(),
                    outA = outF->getHyper()->getAxes(), smallA, bigA;

  if (!_adj) {
    smallA = inF->getHyper()->getAxes();
    bigA = outF->getHyper()->getAxes();

    if (outF->getHyper()->getNdimG1() - inF->getHyper()->getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  } else {
    bigA = inF->getHyper()->getAxes();
    smallA = outF->getHyper()->getAxes();
    if (inF->getHyper()->getNdimG1() - outF->getHyper()->getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  }

  //We are going to paralleize over axis after the last stacked\
//Figure out the last stacked axis and the parallelization loop
  int stackMax = *max_element(_iaxes.begin(), _iaxes.end());
  int stackMin = *min_element(_iaxes.begin(), _iaxes.end());

  if (stackMax >= bigA.size())
    throw SEPException(std::string("Maximum stack axis ") +
                       std::to_string(stackMax) +
                       std::string("larger then number of dimensions"));

  if (stackMin < 0) throw SEPException("Illegal stack axis < 0");

  long long n123 = 1;
  for (int i = stackMax + 1; i < bigA.size(); i++) n123 *= (long long)bigA[i].n;

  // Loop over stacking up to six directions
  std::vector<int> jsmall(6, 1), jbig(6, 1);
  std::vector<int> n(6, 1);

  long long n123Big = 1, n123Small = 1;
  int istack = 0;
  for (int iax = 0; iax <= stackMax; iax++) {
    bool found = false;
    for (auto iaxS : _iaxes) {
      if (iax == iaxS) found = true;
    }
    if (!found) {
      // We are not stacking over this axis

      if (bigA[iax].n != smallA[istack].n)
        throw SEPException(std::string("Axis ") + std::to_string(iax + 1) +
                           std::string(" of big size not equal to axis ") +
                           std::to_string(istack + 1) +
                           std::string(" of small "));
      jsmall[iax] = n123Small;
      n123Small *= (long long)smallA[istack].n;
      istack++;
    } else {
      // Stacking over this axis
      jsmall[iax] = 0;
    }
    n[iax] = bigA[iax].n;

    jbig[iax] = n123Big;
    n123Big *= (long long)bigA[iax].n;
  }

  float *outV = outF->getVals(), *inV = inF->getVals();
  outF->scale(0.);

  if (_adj) {
    tbb::parallel_for(tbb::blocked_range<int>(0, n123),
                      [&](const tbb::blocked_range<int> &r) {
                        for (int iy = r.begin(); iy != r.end(); ++iy) {
                          long long bbig = n123Big * iy;
                          long long bSmall = n123Small * iy;
                          for (int i5 = 0; i5 < n[5]; i5++) {
                            long long b5B = bbig + i5 * jbig[5];
                            long long b5S = bSmall + i5 * jsmall[5];
                            for (int i4 = 0; i4 < n[4]; i4++) {
                              long long b4B = b5B + i4 * jbig[4];
                              long long b4S = b5S + i4 * jsmall[4];
                              for (int i3 = 0; i3 < n[3]; i3++) {
                                long long b3B = b4B + i3 * jbig[3];
                                long long b3S = b4S + i3 * jsmall[3];
                                for (int i2 = 0; i2 < n[2]; i2++) {
                                  long long b2B = b3B + i2 * jbig[2];
                                  long long b2S = b3S + i2 * jsmall[2];
                                  for (int i1 = 0; i1 < n[1]; i1++) {
                                    long long b1B = b2B + i1 * jbig[1];
                                    long long b1S = b2S + i1 * jsmall[1];
                                    for (int i0 = 0; i0 < n[0]; i0++) {
                                      long long b0B = b1B + i0 * jbig[0];
                                      long long b0S = b1S + i0 * jsmall[0];
                                      outV[b1S + i0 * jsmall[0]] +=
                                          inV[b1B + i0 * jbig[0]];
                                    }
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
                          long long bbig = n123Big * iy;
                          long long bSmall = n123Small * iy;
                          for (int i5 = 0; i5 < n[5]; i5++) {
                            long long b5B = bbig + i5 * jbig[5];
                            long long b5S = bSmall + i5 * jsmall[5];
                            for (int i4 = 0; i4 < n[4]; i4++) {
                              long long b4B = b5B + i4 * jbig[4];
                              long long b4S = b5S + i4 * jsmall[4];
                              for (int i3 = 0; i3 < n[3]; i3++) {
                                long long b3B = b4B + i3 * jbig[3];
                                long long b3S = b4S + i3 * jsmall[3];
                                for (int i2 = 0; i2 < n[2]; i2++) {
                                  long long b2B = b3B + i2 * jbig[2];
                                  long long b2S = b3S + i2 * jsmall[2];
                                  for (int i1 = 0; i1 < n[1]; i1++) {
                                    long long b1B = b2B + i1 * jbig[1];
                                    long long b1S = b2S + i1 * jsmall[1];
                                    for (int i0 = 0; i0 < n[0]; i0++) {
                                      long long b0B = b1B + i0 * jbig[0];
                                      long long b0S = b1S + i0 * jsmall[0];
                                      outV[b1B + i0 * jbig[0]] +=
                                          inV[b1S + i0 * jsmall[0]];
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      });
  }
}