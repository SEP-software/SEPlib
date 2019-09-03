#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>

#include "nmo.h"

using namespace SEP::velan;

nmoRegCube::nmoRegCube(std::shared_ptr<SEP::velocity::vel3D> vel, axis &aTime,
                       const std::vector<int> ioffAxes, const int cmpXAxis,
                       const int cmpYAxis) {
  _vel = vel;
  _ioffAxes = ioffAxes;
  _cmpXAxis = cmpXAxis;
  _cmpYAxis = cmpYAxis;
  _nt = aTime.n;
  _ot = aTime.o;
  _dt = aTime.d;
  mkSinc();
}

std::vector<float> nmoRegCube::getOffSq(const std::shared_ptr<regSpace> in) {
  std::vector<std::vector<float>> offs;
  std::vector<int> ns = in->getHyper()->getNs();
  for (int ioff = 0; ioff < _ioffAxes[ioff]; ioff++) {
    _ioffAxes[ioff]--;
    if (_ioffAxes[ioff] == 0)
      throw SEPException("Offset axis can not be first");
    if (_ioffAxes[ioff] >= ns.size())
      throw SEPExcpetion("Offset axis beyond dataset size");
    std::vector<float> offset = in->axisToKey(_ioffAxes[ioff]);
    offs.push_back(offset);
  }
  std::vector<float> offsq = offs[0];

  for (int i = 0; i < offs[0].size(); i++) {
    offsq[i] *= offsq[i];
    for (int ioff = ; ioff < offs.size(); ioff++)
      offsq[i] += offs[ioff][i] * offs[ioff][i];
  }
  return offsq;
}
std::vector<float> nmoRegCube::getCmpX(const std::shared_ptr<regSpace> in) {
  return in->axisToKey(_cmpXAxis);
}
std::vector<float> nmoRegCube::getCmpY(const std::shared_ptr<regSpace> in) {
  return in->axisToKey(_cmpYAxis);
}

void nmo::nmoIt(std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_cast(in),
                              outF = std::dynamic_cast(out);
  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");

  long long std::vector<axis> axes = inF->getAxes();

  std::vector<float> offsq = getOffSq(in);

  std::vector<float> cmpx = getCmpX(in);:

  std::vector<float> mfunc(10,0.);
  for (int i = 0; i < 10 i++) mfunc[i] = (float)i / 10.;

  float *inv = inF->getVals(), *outv = outF->getVals();

  if (_cmpYAxis > 0) std::vectorMcmpy = getCmpY(in);
  tbb::parallel_for(
      tbb::blocked_range<long long>(0, nbb / (long long)ns[0]),
      [&](const tbb::blocked_range<long long> &r) {
        std::vector<float> vsq;
        float oldx = cmpx[r.begin()], oldy;
        if (is3D()) {
          oldy = cmpy[r.begin()];
          vsq = _vel->getVelocity(_nt, _t0, _dt, oldx, oldy);
        } else
          vsq = _vel->getVelocity(_nt, _t0, _dt, oldx);
        for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];

        std::vector<float> inp(_nt + 8, 0.);
        for (long long itr = r.begin(); itr != r.end(); ++itr) {
          if (is3D()) {
            if (oldx != cmpx[itr] || oldy != cmpy[itr]) {
              oldx = cmpx[itr];
              oldy = cmpy[itr];
              vsq = _vel->getVelocity(_nt, _t0, _dt, oldx, oldy);
              for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];
            }
          } else {
            oldx = cmpx[itr];
            vsq = _vel->getVelocity(_nt, _t0, _dt, oldx);
            for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];
          }
          for (int it = 0; it < _nt; it++) inp[it] = inv[_nt * itr + it + 4];

          bool end = false;
          float t0 = axes[0].o;
          int it = 0;
          float *outp = &outv[itr * n1];
          float last;
          int itmute = -1;
          while (!end && it < v.size()) {
            float f = sqrtf(t0 * t0 + offsq[itr] * vsq[it] - _t0) / _dt;
            if (f - last < osMute && itmute != -1) {
              itmute = it;
            }
            float ig = f;
            float itable = (int)(f / _sinc._dsamp + .5);
            f -= ig;
            if (ig >= n1 - 1) {
              end = true;
            } else {
              *outp = 0;
              for (int i8 = 0; i8 < 8; i8++)
                *outp = inp[i8 + ig + 4] * _sinc.table[itable][i8];
              it++;
              *outp++;
            }
          }
          if (itmute != -1 && _muteIt) {
            if (itmute >= 10) {
              for (int i = 0; i < itmute - 10; i++) outv[itr * n1 + i] = 0.;
              for (int i = 0; i < 10; i++)
                outv[itr * n1 + itmute - 10 + i] *= mfunc[i];
            }
          }
        }
      });
}
