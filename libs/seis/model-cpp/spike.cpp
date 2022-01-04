

#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

#include "spike.h"

#include <algorithm>
#include <thread>
#include "SEPException.h"

void SEP::model::floatSpike::applyOut(std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> outF = std::dynamic_pointer_cast<floatHyper>(out);

  std::vector<int> f(7, 0), n(7, 1);
  std::vector<long long> b(8, 1);
  std::vector<SEP::axis> axesSmall = outF->getHyper()->getAxes(),
                         axesBig = _hyper->getAxes();
  for (int i = 0; i < axesSmall.size(); i++) {
    n[i] = axesSmall[i].n;
    f[i] = (axesSmall[i].o - axesBig[i].o) / axesBig[i].d + .5;
    b[i + 1] = b[i] * (long long)n[i];
  }

  for (int i = axesSmall.size() + 1; i < 8; i++) b[i] = b[i - 1];
  outF->scale(0.);
  for (int ivals = 0; ivals < _vals.size(); ivals++) {
    std::vector<std::vector<int>> set;
    for (int idim = 0; idim < 7; idim++) {
      std::vector<int> setDim;

      if (_vals[ivals]._loc.count(idim) == 1) {
        int ip = _vals[ivals]._loc[idim] - f[idim];
        if (ip >= 0 && ip < n[idim]) setDim.push_back(ip);
      } else {
        for (int i = 0; i < n[idim]; i++) {
          setDim.push_back(i);
        }
      }
      set.push_back(setDim);
    }
    float *v = outF->getVals();
    float mag = _vals[ivals]._mag;

    for (int i6 = 0; i6 < set[6].size(); i6++) {
      long long b6 = set[6][i6] * b[6];
      for (int i5 = 0; i5 < set[5].size(); i5++) {
        long long b5 = b6 + set[5][i5] * b[5];
        for (int i4 = 0; i4 < set[4].size(); i4++) {
          long long b4 = b5 + set[4][i4] * b[4];
          for (int i3 = 0; i3 < set[3].size(); i3++) {
            long long b3 = b4 + set[3][i3] * b[3];
            for (int i2 = 0; i2 < set[2].size(); i2++) {
              long long b2 = b3 + set[2][i2] * b[2];
              for (int i1 = 0; i1 < set[1].size(); i1++) {
                long long b1 = b2 + set[1][i1] * b[1];
                for (int i0 = 0; i0 < set[0].size(); i0++) {
                  v[b1 + set[0][i0]] = mag;
                }
              }
            }
          }
        }
      }
    }
  }
}
