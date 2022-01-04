
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <thread>

#include "floatFilter.h"

#include "SEPException.h"

void SEP::filter::floatFilter1D::applyInOut(std::shared_ptr<regSpace> in,
                                            std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_pointer_cast<floatHyper>(in),
                              outF = std::dynamic_pointer_cast<floatHyper>(out);
  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");
  std::vector<axis> inA = inF->getHyper()->getAxes(),
                    outA = outF->getHyper()->getAxes();

  if (inA.size() != outA.size())
    throw SEPException(
        "Expecting the same number dimensions for input and output");
  long long n123 = 1;
  std::vector<int> ns(8, 1);
  for (int i = 0; i < inA.size(); i++) {
    if (inA[i].n != outA[i].n)
      throw SEPException(std::string("Axis ") + std::to_string(i + 1) +
                         std::string(" not the same size"));
    n123 *= (long long)outA[i].n;
  }

  long long n23 = n123 / (long long)outA[0].n;

  float *inV = inF->getVals(), *outV = outF->getVals(),
        *filtV = _filt->getVals();
  long long n0 = _filt->_n[0], f0 = _filt->_f[0], e0 = _filt->_e[0];
  tbb::parallel_for(tbb::blocked_range<int>(0, n23),
                    [&](const tbb::blocked_range<int> &r) {
                      for (int iy = r.begin(); iy != r.end(); ++iy) {
                        for (long long i0 = e0 + iy * outA[0].n;
                             i0 < outA[0].n - f0 + iy * outA[0].n; i0++) {
                          for (long long i_f = 0; i_f < n0; i_f++) {
                            outV[i0] += filtV[i_f] * inV[i0 - i_f - f0];
                          }
                        }
                      }
                    });
}
