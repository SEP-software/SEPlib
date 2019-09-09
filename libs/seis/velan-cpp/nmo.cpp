#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>

#include "maps.h"
#include "nmo.h"

using namespace SEP::velocity;

nmoRegCube::nmoRegCube(std::shared_ptr<SEP::velocity::vel3D> vel,
                       const axis &aTime, const std::vector<int> ioffAxes,
                       const int cmpXAxis, const int cmpYAxis) {
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
      throw SEPException("Offset axis beyond dataset size");
    std::vector<float> offset = in->axisToKey(_ioffAxes[ioff]);
    offs.push_back(offset);
  }
  std::vector<float> offsq = offs[0];

  for (int i = 0; i < offs[0].size(); i++) {
    offsq[i] *= offsq[i];
    for (int ioff = 1; ioff < offs.size(); ioff++)
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

void nmo::applyIt(std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_pointer_cast<floatHyper>(in),
                              outF = std::dynamic_pointer_cast<floatHyper>(out);
  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");

  std::vector<axis> axes = inF->getHyper()->getAxes();
  long long n123 = inF->getHyper()->getN123();

  std::vector<float> offsq = getOffSq(in);

  std::vector<float> cmpx = getCmpX(in), cmpy;

  std::vector<float> mfunc(10, 0.);
  for (int i = 0; i < 10; i++) mfunc[i] = (float)i / 10.;

  float *inv = inF->getVals(), *outv = outF->getVals();

  if (is3D()) cmpy = getCmpY(in);
  tbb::parallel_for(
      tbb::blocked_range<long long>(0, n123 / (long long)_nt),
      [&](const tbb::blocked_range<long long> &r) {
        std::vector<float> vsq;
        float oldx = cmpx[r.begin()], oldy;
        std::vector<float> ttn(_nt);
        if (is3D()) {
          oldy = cmpy[r.begin()];
          vsq = _vel->getVelocity(_nt, _ot, _dt, oldx, oldy);
        } else
          vsq = _vel->getVelocity(_nt, _ot, _dt, oldx);
        for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];

        std::vector<float> inp(_nt + 8, 0.);
        for (long long itr = r.begin(); itr != r.end(); ++itr) {
          if (is3D()) {
            if (oldx != cmpx[itr] || oldy != cmpy[itr]) {
              oldx = cmpx[itr];
              oldy = cmpy[itr];
              vsq = _vel->getVelocity(_nt, _ot, _dt, oldx, oldy);
              for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];
            }
          } else {
            oldx = cmpx[itr];
            vsq = _vel->getVelocity(_nt, _ot, _dt, oldx);
            for (auto i = 0; i < vsq.size(); i++) vsq[i] *= vsq[i];
          }
          for (int it = 0; it < _nt; it++) inp[it] = inv[_nt * itr + it + 4];

          float *outp = &outv[itr * _nt];
          *outp = 0;

          float tm = _ot;
          for (int it = 0; it < _nt; it++, tm += _dt)
            ttn[it] = sqrtf(tm * tm + offsq[itr] * vsq[it] - _ot) / _dt;
          int itmute;
          for (itmute = 0;
               itmute < _nt - 1 && ttn[itmute + 1] - ttn[itmute] < _osmute;
               ++itmute)
            ;

          if (!_inverse) {
            for (int it = 0; it < _nt; it++) {
              int ig = ttn[it];
              float f = ttn[it] - ig;
              int itable = (int)(f / _sinc._dsamp + .5);
              if (ig < _nt) {
                for (int i8 = 0; i8 < 8; i8++)
                  *outp = inp[i8 + ig + 4] * _sinc._table[itable][i8];
              }
              outp++;
            }
            if (itmute != -1 && _muteIt) {
              if (itmute >= 10) {
                for (int i = 0; i < itmute - 10; i++) outv[itr * _nt + i] = 0.;
                for (int i = 0; i < 10; i++)
                  outv[itr * _nt + itmute - 10 + i] *= mfunc[i];
              }
            }
          } else {
            axis aX = axis(_nt, 0., 1.);
            std::vector<float> tti =
                SEP::maps::invert1DMap(aX, aX, ttn, -1, _nt + 1);
            for (int it = 0; it < _nt; it++) {
              int ig = tti[it];
              if (ig >= 0 && ig < _nt) {
                float f = tti[it] - ig;
                int itable = (int)(tti[it] / _sinc._dsamp + .5);

                for (int i8 = 0; i8 < 8; i8++)
                  *outp = inp[i8 + ig + 4] * _sinc._table[itable][i8];
              }
              outp++;
            }
          }
        }
      });
}
