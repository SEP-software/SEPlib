#include "vel3D.h"
using namespace SEP::velocity;
std::vector<float> vel3D::getVelocity(const int n1, const float o1,
                                      const float d1, const float x) {
  return getVelocity(n1, o1, d1, x, _axes[2].o);
}

vel3DConstant::vel3DConstant(const float vel) {
  _val = vel;
  _axes.push_back(axis(1, 0., 1.));
  _axes.push_back(axis(1, 0., 1.));
  _axes.push_back(axis(1, 0., 1.));
}

std::vector<float> vel3D::getVelocity(const int n1, const float o1,
                                      const float d1, const float x,
                                      const float y) {
  return getVelocity(n1, o1, d1, x, y);
}

std::vector<float> vel3DCube::getVelocity(const int n1, const float o1,
                                          const float d1, const float x,
                                          const float y) {
  std::vector<float> vel(n1);
  float fx = (x - _axes[1].o) / _axes[1].d;
  float fy = (y - _axes[2].o) / _axes[2].d;
  int ix = fx, iy = fy;
  fx = fx - ix;
  fy = fy - iy;
  if (ix == _axes[1].n - 1) {
    ix = _axes[1].n - 2;
    fx = 1;
  }
  if (iy == _axes[2].n - 1) {
    iy = _axes[2].n - 2;
    fy = 1;
  }

  for (int i1 = 0; i1 < n1; i1++) {
    float t = o1 + d1 * i1;
    float ft = (t - _axes[0].o) / _axes[0].d;
    int it = ft;
    ft = ft - it;
    if (it == _axes[0].n - 1) {
      it = _axes[0].n - 2;
      ft = 1;
    }
    vel[i1] = (1. - ft) * (1. - fx) * (1. - fy) * (*_values->_mat)[iy][ix][it] +
              (ft) * (1. - fx) * (1. - fy) * (*_values->_mat)[iy][ix][it + 1] +
              (1. - ft) * (fx) * (1. - fy) * (*_values->_mat)[iy][ix + 1][it] +
              (ft) * (fx) * (1. - fy) * (*_values->_mat)[iy][ix + 1][it + 1] +
              (1. - ft) * (1. - fx) * (fy) * (*_values->_mat)[iy + 1][ix][it] +
              (ft) * (1. - fx) * (fy) * (*_values->_mat)[iy + 1][ix][it + 1] +
              (1. - ft) * (fx) * (fy) * (*_values->_mat)[iy + 1][ix + 1][it] +
              (ft) * (fx) * (fy) * (*_values->_mat)[iy + 1][ix + 1][it + 1];
  }
  return vel;
}

vel3DFromArray::vel3DFromArray(std::shared_ptr<float3DReg> vals) {
  _values = vals;
  _axes = vals->getHyper()->getAxes();
}

vel3DFromFile::vel3DFromFile(std::shared_ptr<genericRegFile> file) {
  _file = file;
  _axes = file->getHyper()->getAxes();
  if (file->getHyper()->getNdimG1() != 3)
    throw SEPException("Velocity must be 3-D");
}

long long vel3DFromFile::readVelocity(std::shared_ptr<hypercube> output,
                                      const long long maxMem) {
  std::vector<int> fwind(3), jwind(3, 1), nwind(3);
  std::vector<axis> axes = output->getAxes();

  std::vector<int> mat(3, 0);
  if (output->getNdimG1() == 5) {
    mat[1] = 3;
    mat[2] = 4;
  } else {
    mat[1] = 1;
    mat[2] = 2;
  }
  long long tot = 4;
  for (int i = 0; i < 3; i++) {
    fwind[i] = (axes[mat[i]].o - _axes[i].o) / _axes[i].d;

    int mx = std::min(
        axes[mat[i]].n - 1,
        (int)(((axes[mat[i]].o + axes[mat[i]].d * (axes[mat[i]].n - 1)) -
               _axes[i].o) /
              _axes[i].d));

    nwind[i] = mx + 1 - fwind[i];
    _axes[i].o += fwind[i] * _axes[i].d;
    _axes[i].n = nwind[i];
  }
  if (maxMem < tot)
    throw SEPException("output velocity size larger than total memory allowed");
  _values.reset(new float3DReg(nwind[0], nwind[1], nwind[2]));

  _file->readFloatWindow(nwind, fwind, jwind, _values);
  return tot;
}
