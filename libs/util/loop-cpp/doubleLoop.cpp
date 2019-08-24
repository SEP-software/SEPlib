#include "doubleLoop.h"
#include "SEPException.h"
using namespace SEP::loop;
std::shared_ptr<doubleWindP> doubleLoop::createLoop(
    const std::vector<int> nblockOut, const std::vector<int> nblockIn) {
  int ndim = _nw.size();
  std::vector<int> n = create9(_n, 1);
  std::vector<int> nw = create9(_nw, 1);
  std::vector<int> fw = create9(_fw, 1);
  std::vector<int> jw = create9(_jw, 1);
  std::vector<int> b = create9(nblockOut, 1);

  for (auto i = 0; i < n.size(); i++) {
    checkLogic(n[i], nw[i], fw[i], jw[i], b[i]);
  }

  std::vector<int> fin(9), jin(9), nin(9), nd(9, 0);

  std::shared_ptr<doubleWindP> window(new doubleWindP());

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
                    std::vector<int> nt = nin, ft = fin, jt = jw;
                    nt.resize(ndim);
                    ft.resize(ndim);
                    jt.resize(ndim);
                    windP innerLoop = _calc->loopDependParams(nt, ft, jt);
                    std::vector<int> ndf(ndim);
                    for (auto i = 0; i < ndim; i++)
                      ndf[i] = (nt[i] - 1) * jt[i] + ft[i] + 1;
                    basicLoop basic = basicLoop(ndf, innerLoop._nw,
                                                innerLoop._fw, innerLoop._jw);
                    window->innerLoop.push_back(basic.createLoop(nblockIn));

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
    window->outerLoop.push_back(
        windP(windTmp[i]._nw, windTmp[i]._fw, windTmp[i]._jw));
  }
  return window;
}
