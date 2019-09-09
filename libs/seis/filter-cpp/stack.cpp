#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>
#include <thread>

#include "SEPException.h"
#include "stack.h"

SEP::floatStackSpreadReg::applyIt(std::shared_ptr<regSpace> in,
                                  std::shared_ptr<regSpace> out) {
  std::shared_ptr<floatHyper> inF = std::dynamic_pointer_cast<floatHyper>(in),
                              outF = std::dynamic_pointer_cast<floatHyper>(out);
  if (!inF || !outF) throw SEPException("Could not cast to floatHypers");
  std::vector<axis> inA = inF->getHyper()->getAxes(),
                    outA = outF->getHyper()->getAxes(), smallA, bigA;
  if (adj) {
    smallA = inF->getHyper()->getAxes();
    bigA = outF->getHyper()->getAxes();
    if (outF->getHyper()->‭getNdimG1() - inF->getHyper()->‭getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  } else {
    bigA = outF->getHyper()->getAxes();
    smallA = inF->getHyper()->getAxes();
    if (inF->getHyper()->‭getNdimG1() - outF->getHyper()->‭getNdimG1() !=
        _iaxes.size())
      throw SEPException(
          "Non-stacked dimensions not size of stack axes + stacked size");
  }

  for (auto i = 0; i < bigA.size(); i++) {
    bool found = false;
    for (auto iax = 0; iax < _iaxes.size(); iax++) {
      if (_iaxes[iax] < 0 || _iaxes[iax] >= bigA.size())
        throw SEPException(std::string("Unacceptable axis ") +
                           std::to_string(_iaxes[iax]) +
                           std::string(" is outside axis range"))

            if (i == _iaxes[iax]) found = true;
    }
    if (found) {
      if (i < smallA.size()) {
        if () }
    }
  }
}

// Create image from file
data3DReg::data3DReg(std::shared_ptr<genericRegFile> file) {
  _hyper = file->getHyper();
  _file = file;

  if (_hyper->getNdim() != 3) throw SEPException("Input must be 3-D");
}

// Create data from file
data5DReg::data5DReg(std::shared_ptr<genericRegFile> file) {
  _file = file;
  _hyper = _file->getHyper();
  if (_hyper->getNdim() != 5) throw SEPException("Input must be 5-D");
}

void data3DReg::setWindow(std::shared_ptr<hypercube> hyper, const float aper) {
  std::vector<axis> axesD = hyper->getAxes();
  std::vector<axis> axesI = _hyper->getAxes();

  int bx = std::max((int)((axesD[3].o - aper - axesI[1].o) / axesI[1].d), 0);
  int by = std::max((int)((axesD[4].o - aper - axesI[2].o) / axesI[2].d), 0);

  int ex = std::min(
      (int)((axesD[3].o + axesD[3].d * (axesD[3].n - 1) + aper - axesI[1].o) /
            axesI[1].d),
      axesI[1].n - 1);
  int ey = std::min(
      (int)((axesD[4].o + axesD[4].d * (axesD[4].n - 1) + aper - axesI[2].o) /
            axesI[2].d),
      axesI[2].n - 1);

  _fw.push_back(0);
  _fw.push_back(bx);
  _fw.push_back(by);
  _nw.push_back(axesD[0].n);
  _nw.push_back(ex - bx + 1);
  _nw.push_back(ey - by + 1);
}

std::shared_ptr<float3DReg> data3DReg::read() {
  std::vector<int> jw(3, 1);
  std::vector<axis> axes(3), ain = _hyper->getAxes();
  for (int i = 0; i < 3; i++) {
    axes[i].o = _fw[i] * ain[i].d + ain[i].o;
    axes[i].d = ain[i].d;
    axes[i].n = _nw[i];
  }
  std::shared_ptr<float3DReg> buf(new float3DReg(axes[0], axes[1], axes[2]));

  _file->readFloatWindow(_nw, _fw, jw, buf);

  return buf;
}

// Create image from file and parameters
data5DReg::data5DReg(std::shared_ptr<data5DReg> input, const axis aX,
                     const axis aY) {
  std::shared_ptr<hypercube> hypIn = input->getHyper();

  std::vector<axis> axes = hypIn->getAxes();
  axes[3] = aX;
  axes[4] = aY;
  _hyper.reset(new hypercube(axes));
}

// Create data from image then paremters
data5DReg::data5DReg(std::shared_ptr<data3DReg> input, const axis aOX,
                     const axis aOY, const axis aX, const axis aY) {
  std::shared_ptr<hypercube> hypIn = input->getHyper();

  std::vector<axis> axes = hypIn->getAxes();
  axes[1] = aOX;
  axes[2] = aOY;
  axes.push_back(aX);
  axes.push_back(aY);
  std::shared_ptr<hypercube> x(new hypercube(axes));
  _hyper = x;
}
void data5DReg::setFile(std::shared_ptr<genericRegFile> fle) { _file = fle; }
void data5DReg::checkLogic(std::shared_ptr<SEP::velocity::vel3DFromFile> vrms) {
  std::vector<axis> vaxes = vrms->getHyper()->getAxes();

  std::vector<axis> oaxes = _hyper->getAxes();

  if (vaxes[0].o > oaxes[0].o ||
      vaxes[0].o + vaxes[0].d * (vaxes[0].n - 1) <
          (oaxes[0].o + oaxes[0].d * (oaxes[0].n - 1)))
    throw SEPException("Velocity does not span output along time axis");

  if (vaxes[1].o > oaxes[3].o ||
      vaxes[1].o + vaxes[1].d * (vaxes[1].n - 1) <
          (oaxes[3].o + oaxes[3].d * (oaxes[3].n - 1)))
    throw SEPException("Velocity does not span migration volume along X axis");

  if (vaxes[2].o > oaxes[4].o ||
      vaxes[2].o + vaxes[2].d * (vaxes[2].n - 1) <
          (oaxes[4].o + oaxes[4].d * (oaxes[4].n - 1)))

    throw SEPException(
        std::string(
            "Velocity does not span output along Y axis Mins(v,domain)=") +
        std::to_string(vaxes[2].o) + std::string(",") +
        std::to_string(oaxes[4].o) + std::string("  maxs(vel,domain=") +
        std::to_string(vaxes[2].o + vaxes[2].d * (vaxes[2].n - 1)) +
        std::string(",") +
        std::to_string(oaxes[4].o + oaxes[4].d * (oaxes[4].n - 1)));
}

std::shared_ptr<float5DReg> data5DReg::createWindow(
    const std::vector<int> nwind, const std::vector<int> fwind) {
  std::vector<int> jwind(5, 1);
  std::vector<axis> axes;
  for (int i = 0; i < 5; i++) {
    axis a = _hyper->getAxis(i + 1);
    axes.push_back(axis(nwind[i], a.o + a.d * fwind[i], a.d));
  }

  std::shared_ptr<hypercube> hyper(new hypercube(axes));

  std::shared_ptr<float5DReg> buf(new float5DReg(hyper));

  return buf;
}
void data5DReg::readWindow(const std::vector<int> nwind,
                           const std::vector<int> fwind,
                           std::shared_ptr<float5DReg> buf) {
  std::vector<int> jwind(5, 1);
  _file->readFloatWindow(nwind, fwind, jwind, buf);
}

void data5DReg::writeWindow(const std::vector<int> nwind,
                            const std::vector<int> fwind,
                            std::shared_ptr<float5DReg> buf) {
  std::vector<int> jwind(5, 1);

  _file->writeFloatWindow(nwind, fwind, jwind, buf);
}

void basicTime::calcInputWindow(const std::vector<int> nout,
                                const std::vector<int> fout) {
  std::vector<int> nin(5, 1), fin(5, 0), bin(5, 1);
  for (int i = 0; i < 3; i++) {
    fin[i] = fout[i];
    nin[i] = nout[i];
  }
  fin[3] = std::max(0, (int)(fout[3] - _aper / _hyperData->getAxis(4).d));
  fin[4] = std::max(0, (int)(fout[4] - _aper / _hyperData->getAxis(5).d));
  nin[3] =
      std::min(
          _hyperData->getAxis(4).n - 1,
          (int)((fout[4] + (nout[3] - 1) * _hyperData->getAxis(4).d + _aper) /
                _hyperData->getAxis(4).d) +
              1 - fin[3]) +
      1;
  nin[4] =
      std::min(
          _hyperData->getAxis(5).n - 1,
          (int)((fout[4] + (nout[4] - 1) * _hyperData->getAxis(5).d + _aper) /
                _hyperData->getAxis(5).d) +
              1 - fin[4]) +
      1;
  // Find out how much input we can read

  int iax = 0;
  bool found = false;
  int nelem = 4;
  while (iax < 5 && !found) {
    if (nelem * nin[iax] < _mem) {
      bin[iax] = nin[iax];
      nelem *= bin[iax];
    } else {
      bin[iax] = _mem / nelem;
      found = true;
    }
    iax++;
  }
  _nin = nin;
  _bin = bin;
  _fin = fin;
}

model::model(std::shared_ptr<data5DReg> inp,
             std::shared_ptr<SEP::velocity::vel3DFromFile> vel,
             std::shared_ptr<float1DReg> wave, const float aper,
             const long long mem) {
  _vel = vel;
  _aper = aper;
  _mem = mem;
  _wave = wave;
  _hyperData = inp->getHyper();
}

migrate::migrate(std::shared_ptr<data5DReg> inp,
                 std::shared_ptr<SEP::velocity::vel3DFromFile> vel,
                 const float aper, const long long mem) {
  _vel = vel;
  _aper = aper;
  _mem = mem;
  _hyperData = inp->getHyper();
}

void migrate::apply(std::shared_ptr<float5DReg> data,
                    std::shared_ptr<float5DReg> image) {
  std::vector<axis> aimage = image->getHyper()->getAxes(),
                    adata = data->getHyper()->getAxes();

  std::vector<float> offx(adata[1].n), offy(adata[2].n);
  for (auto i = 0; i < offx.size(); i++) {
    offx[i] = adata[1].o + adata[1].d * i;
  }
  for (auto i = 0; i < offy.size(); i++) {
    offy[i] = adata[2].o + adata[2].d * i;
  }
  std::vector<float> cxd(adata[3].n), cyd(adata[4].n), tmsq(adata[0].n);
  for (auto i = 0; i < cxd.size(); i++) cxd[i] = adata[3].o + adata[3].d * i;
  for (auto i = 0; i < cyd.size(); i++) cyd[i] = adata[4].o + adata[4].d * i;
  std::vector<float> cxi(adata[3].n), cyi(adata[4].n);
  for (auto i = 0; i < cxi.size(); i++) cxi[i] = aimage[3].o + aimage[3].d * i;
  for (auto i = 0; i < cyi.size(); i++) cyi[i] = aimage[4].o + aimage[4].d * i;

  for (auto i = 0; i < tmsq.size(); i++)
    tmsq[i] = (adata[0].o + adata[0].d * i) * (adata[0].o + adata[0].d * i);

  for (int i5 = 0; i5 < aimage[4].n; i5++) {
    float y = aimage[4].o + aimage[4].d * i5;
    for (int i4 = 0; i4 < aimage[3].n; i4++) {
      float x = aimage[3].o + aimage[3].d * i4;

      std::vector<float> vel =
          _vel->getVelocity(aimage[0].n, aimage[0].o, aimage[0].d, x, y);

      // for (auto iy = 0; iy < cyi.size(); iy++) {
      // for (auto ix = 0; ix < cyi.size(); ix++) {

      tbb::parallel_for(
          tbb::blocked_range<int>(0, cyi.size()),
          [&](const tbb::blocked_range<int> &r) {
            for (int iy = r.begin(); iy != r.end(); ++iy) {
              tbb::parallel_for(
                  tbb::blocked_range<int>(0, cxi.size()),
                  [&](const tbb::blocked_range<int> &r) {
                    for (int ix = r.begin(); ix != r.end(); ++ix) {
                      for (int i3 = 0; i3 < adata[2].n; i3++) {
                        float disty2 = (cyi[i5] - cyd[iy] - offy[i3]) *
                                       (cyi[i5] - cyd[iy] - offy[i3]);

                        for (int i2 = 0; i2 < adata[1].n; i2++) {
                          float distx2 = (cxi[i4] - cxd[ix] - offx[i2]) *
                                         (cxi[i4] - cxd[ix] - offx[i2]);

                          int it = -1;
                          bool done = false;
                          while (it < aimage[0].n && !done) {
                            it++;
                            float tm =
                                (sqrtf(tmsq[it] * vel[it] * vel[it] + disty2) +
                                 sqrtf(tmsq[it] * vel[it] * vel[it] + distx2)) /
                                vel[it] / 2.;
                            float f_t = (tm - adata[0].o) / adata[0].d + .5;

                            int i_t = f_t;

                            f_t -= i_t;
                            if (i_t < adata[0].n - 1)
                              (*image->_mat)[i5][i4][i3][i2][it] +=
                                  (1. - f_t) *
                                      (*data->_mat)[iy][ix][i3][i2][i_t] +
                                  f_t * (*data->_mat)[iy][ix][i3][i2][i_t + 1];
                            else
                              done = true;
                          }
                        }
                      }
                    }
                  });
            }
          });
    }
  }
}

void model::apply(std::shared_ptr<float3DReg> image,
                  std::shared_ptr<float5DReg> data) {
  std::vector<axis> aimage = image->getHyper()->getAxes(),
                    adata = data->getHyper()->getAxes();

  int nw = _wave->getHyper()->getAxis(1).n;

  int fw =
      (int)((_wave->getHyper()->getAxis(1).o) / data->getHyper()->getAxis(1).d +
            .5);

  std::vector<int> ix(aimage[2].n * aimage[1].n), iy(aimage[2].n * aimage[1].n);

  std::vector<float> offx(adata[1].n), offy(adata[2].n);
  for (auto i = 0; i < offx.size(); i++) offx[i] = adata[1].o + adata[1].d * i;
  for (auto i = 0; i < offy.size(); i++) {
    offy[i] = adata[2].o + adata[2].d * i;
  }
  std::vector<float> cxd(adata[3].n), cyd(adata[4].n), tmsq(adata[0].n);
  for (auto i = 0; i < cxd.size(); i++) cxd[i] = adata[3].o + adata[3].d * i;
  for (auto i = 0; i < cyd.size(); i++) cyd[i] = adata[4].o + adata[4].d * i;
  std::vector<float> cxi(aimage[1].n), cyi(aimage[2].n);
  for (auto i = 0; i < cxi.size(); i++) {
    cxi[i] = aimage[1].o + aimage[1].d * i;
  }
  for (auto i = 0; i < cyi.size(); i++) cyi[i] = aimage[2].o + aimage[2].d * i;

  for (auto i = 0; i < tmsq.size(); i++)
    tmsq[i] = (adata[0].o + adata[0].d * i) * (adata[0].o + adata[0].d * i);

  std::cerr << adata[1].n << " " << adata[2].n << " " << adata[3].n << " "
            << adata[4].n << "data";
  std::cerr << aimage[1].n << " " << aimage[2].n << "image";

  std::cerr << "check loops " << cyi.size() << " " << cxi.size() << " "
            << adata[1].n << " " << adata[2].n << " " << adata[3].n << " "
            << adata[4].n << std::endl;
  tbb::parallel_for(
      tbb::blocked_range<int>(0, adata[4].n),
      [&](const tbb::blocked_range<int> &s) {
        for (int i5 = s.begin(); i5 != s.end(); ++i5) {
          // for (int i5 = 0; i5 < adata[4].n; i5++) {
          float y = adata[4].o + adata[4].d * i5;

          //  tbb::parallel_for(
          //    tbb::blocked_range<int>(0, adata[3].n),
          //  [&](const tbb::blocked_range<int> &r) {
          //  for (int i4 = r.begin(); i4 != r.end(); ++i4) {
          for (int i4 = 0; i4 < adata[3].n; i4++) {
            float x = adata[3].o + adata[3].d * i4;

            std::vector<float> vel =
                _vel->getVelocity(adata[0].n, adata[0].o, adata[0].d, x, y);

            std::vector<float> vtsq(adata[0].n), iv(adata[0].n);
            for (auto it = 0; it < vtsq.size(); it++) {
              vtsq[it] = tmsq[it] * vel[it] * vel[it];
              iv[it] = vel[it] * 2.;
              iv[it] = 1. / vel[it];
            }
            std::cerr << i4 << " of " << adata[3].n << " " << i5 << " of "
                      << adata[4].n << std::endl;
            for (int iy = 0; iy < cyi.size(); iy++) {
              for (int ix = 0; ix < cxi.size(); ix++) {
                for (int i3 = 0; i3 < adata[2].n; i3++) {
                  float disty2 = (cyd[i5] - cyi[iy] - offy[i3]) *
                                 (cyd[i5] - cyi[iy] - offy[i3]);

                  for (int i2 = 0; i2 < adata[1].n; i2++) {
                    float distx2 = (cxd[i4] - cxi[ix] - offx[i2]) *
                                   (cxd[i4] - cxi[ix] - offx[i2]);
                    bool end = false;
                    int it = -1;

                    while (!end && it < adata[0].n - 1) {
                      it++;
                      float tm =
                          (sqrt7(tmsq[it] * vel[it] * vel[it] + disty2) +
                           sqrt7(tmsq[it] * vel[it] * vel[it] + distx2)) *
                          iv[it];

                      int i_t = (tm - adata[0].o) / adata[0].d + .5;

                      if (i_t < adata[0].n)
                        (*data->_mat)[i5][i4][i3][i2][i_t] +=
                            (*image->_mat)[iy][ix][it];
                      else {
                        end = true;
                      }
                    }
                  }
                }
              }
            }
          }
          //  });
        }
      });
  tbb::parallel_for(
      tbb::blocked_range<int>(0, adata[4].n),
      [&](const tbb::blocked_range<int> &r) {
        for (int i5 = r.begin(); i5 != r.end(); ++i5) {
          tbb::parallel_for(
              tbb::blocked_range<int>(0, adata[3].n),
              [&](const tbb::blocked_range<int> &r) {
                for (int i4 = r.begin(); i4 != r.end(); ++i4) {
                  std::vector<float> tmp(adata[0].n);
                  for (int i4 = r.begin(); i4 != r.end(); ++i4) {
                    for (int i3 = 0; i3 < adata[2].n; i3++) {
                      for (int i2 = 0; i2 < adata[1].n; i2++) {
                        for (int it = 0; it < adata[0].n; it++) {
                          tmp[it] = (*data->_mat)[i5][i4][i3][i2][it];
                          (*data->_mat)[i5][i4][i3][i2][it] = 0;
                        }
                        for (int it = 0; it < adata[0].n; it++) {
                          for (int iw = 0; iw < nw; iw++) {
                            if (it - iw + fw >= 0 && it - iw + fw) {
                              (*data->_mat)[i5][i4][i3][i2][it] +=
                                  tmp[it - iw + fw] * (*_wave->_mat)[iw];
                            }
                          }
                        }
                      }
                    }
                  }
                }
              });
        }
      });
}
void kirchhoffTime::modelData(std::shared_ptr<data3DReg> image,
                              std::shared_ptr<float1DReg> wave) {
  long long maxsize = maxs;

  image->setWindow(data->getHyper(), aper);

  std::vector<int> nwind(5, 1), fwind(5, 0), jwind(5, 1);
  std::vector<axis> aimage = image->getHyper()->getAxes(),
                    adata = data->getHyper()->getAxes();

  long long nblockIn = 4 * image->getSize();

  // We want to be able  to hold entire image volume in memory
  if (nblockIn > maxsize / 2)
    throw SEPException("Want to be able to hold entire image size in memory ");

  maxsize -= nblockIn;

  long long nblockOut =
      (long long)adata[0].n * (long long)adata[1].n * (long long)adata[2].n * 8;

  // Figure if we can hold more of output space
  long long blockX, blockY = 1;
  blockX = maxsize / nblockOut;
  if (blockX > adata[3].n) {
    blockX = adata[3].n;
    blockY = std::min((long long)adata[4].n,
                      (long long)(maxsize / blockX / nblockOut));
  }
  if (blockY != adata[4].n)
    std::cerr << "Suboptimal parameters can't hold entire output volume "
                 "in memory"
              << std::endl;

  std::vector<axis> ain = image->getHyper()->getAxes();

  // Setup modeling object

  std::shared_ptr<model> mod(new model(data, vel, wave, aper, maxsize));

  nwind[0] = adata[0].n;
  nwind[1] = adata[1].n;
  nwind[2] = adata[2].n;
  std::vector<windP> windOut;

  /* Figure out the read/write pattern

       We are basically going through the entire migration loop
     recordig our window parameters.

      The advantage of this approach is for the overlapping of IO and
     compute used below
  */

  // Loop over output space
  int ndoneX = 0, ndoneY = 0;
  while (ndoneY != adata[4].n) {
    fwind[4] = ndoneY;
    nwind[4] = std::min((int)blockY, adata[4].n - ndoneY);
    while (ndoneX != adata[3].n) {
      fwind[3] = ndoneX;
      nwind[3] = std::min((int)blockX, adata[3].n - ndoneX);
      windOut.push_back(windP(nwind, fwind));
      ndoneX += nwind[3];
    }
    ndoneY += nwind[4];
  }

  // Thread objects
  std::thread writeT;

  std::shared_ptr<float3DReg> in = image->read();

  // Lambda function for writing dataset in the background
  auto writeDataF = [&](std::shared_ptr<float5DReg> dat, std::vector<int> nw,
                        std::vector<int> fw) {
    std::shared_ptr<float5DReg> tmp = dat->clone();
    data->writeWindow(nw, fw, tmp);
  };

  std::shared_ptr<float3DReg> tmp;

  // Loop over output space
  for (int iout = 0; iout < windOut.size(); iout++) {
    // Create  the output
    std::shared_ptr<float5DReg> out =
        data->createWindow(windOut[iout]._nw, windOut[iout]._fw);

    // MOdel this volume
    mod->apply(in, out);

    if (iout != 0) {
      // If this isn't the first volume wait for the last write to be
      // finished

      writeT.join();
    }

    // Write out the next portion
    writeT = std::thread(writeDataF, out, windOut[iout]._nw, windOut[iout]._fw);
  }

  // Wait for the last write to be finished
  writeT.join();
}

void kirchhoffTime::migrateData(std::shared_ptr<data5DReg> image) {
  long long maxsize = maxs;
  std::vector<int> nwind(5, 1), fwind(5, 0), jwind(5, 1);
  std::vector<axis> aimage = image->getHyper()->getAxes(),
                    adata = data->getHyper()->getAxes();

  long long nblock = (long long)aimage[0].n * (long long)aimage[1].n *
                     (long long)aimage[2].n * 8;

  // We want to be able  to hold at least time,offsetx,offsety
  if (nblock > maxsize / 2) {
    throw SEPException(std::string("Can not hold single output CMP in "
                                   "memory, increase memory or  ") +
                       std::string("decrease migration size"));
  }

  nwind[0] = aimage[0].n;
  nwind[1] = aimage[1].n;
  nwind[2] = aimage[2].n;

  // Figure if we can hold more of output space
  long long blockX, blockY = 1;
  blockX = maxsize / nblock;
  maxsize -= nblock;
  if (blockX > aimage[3].n) {
    blockX = aimage[3].n;
    blockY = std::min(aimage[4].n, (int)(maxsize / blockX / nblock));
  }
  if (blockY != aimage[4].n)
    std::cerr << "Suboptimal parameters can't hold entire output volume "
                 "in memory"
              << std::endl;
  std::vector<axis> ain = image->getHyper()->getAxes();
  maxsize = maxsize - nblock * blockX * blockY + nblock;

  // Setup migration object

  std::shared_ptr<migrate> mig(new migrate(data, vel, aper, maxsize));

  std::vector<windP> windOut;
  std::vector<std::vector<windP>> windIn;

  /* Figure out the read/write pattern

       We are basically going through the entire migration loop
     recordig our window parameters.

      The advantage of this approach is for the overlapping of IO and
     compute used below
  */

  // Loop over output space

  int ndoneX = 0, ndoneY = 0;
  while (ndoneY != aimage[4].n) {
    fwind[4] = ndoneY;
    nwind[4] = std::min((int)blockY, aimage[4].n - ndoneY);
    while (ndoneX != aimage[3].n) {
      fwind[3] = ndoneX;
      nwind[3] = std::min((int)blockX, aimage[3].n - ndoneX);
      windOut.push_back(windP(nwind, fwind));
      mig->calcInputWindow(nwind, fwind);
      std::vector<int> nin = mig->getNin(), f = mig->getFin(), fin(5, 0),
                       block = mig->getBin();

      std::vector<windP> windTmp;

      // Loop over input
      fin[4] = f[4];

      while (fin[4] < nin[4]) {
        nin[4] = std::min(ain[4].n - fin[4], block[4]);
        fin[3] = f[3];
        while (fin[3] < nin[3]) {
          nin[3] = std::min(ain[3].n - fin[3], block[3]);
          fin[2] = f[2];
          while (fin[2] < nin[2]) {
            nin[2] = std::min(ain[2].n - fin[2], block[2]);
            fin[1] = f[1];
            while (fin[1] < nin[1]) {
              nin[1] = std::min(ain[1].n - fin[1], block[1]);
              fin[0] = f[0];
              while (fin[0] < nin[0]) {
                nin[0] = std::min(ain[0].n - fin[0], block[0]);
                windTmp.push_back(windP(nin, fin));
                fin[0] += nin[0];
              }
              fin[1] += nin[1];
            }
            fin[2] += nin[2];
          }
          fin[3] += nin[3];
        }
        fin[4] += nin[4];
      }
      windIn.push_back(windTmp);
      ndoneX += nwind[3];
    }
    ndoneY += nwind[4];
  }

  // Thread objects
  std::thread readT, writeT;

  // Lambda function for writing dataset in the background
  auto writeImageF = [&](std::shared_ptr<float5DReg> dat, std::vector<int> nw,
                         std::vector<int> fw) {
    std::shared_ptr<float5DReg> tmp = dat->clone();
    image->writeWindow(nw, fw, tmp);
  };

  // Lambda function for reading dataset in the background
  auto readDataF = [&](std::shared_ptr<float5DReg> dat, std::vector<int> nw,
                       std::vector<int> fw) {
    std::shared_ptr<float5DReg> tmp = dat;
    data->readWindow(nw, fw, tmp);
  };

  std::shared_ptr<float5DReg> tmp;

  // Begin by starting a read for the first section
  tmp = data->createWindow(windIn[0][0]._nw, windIn[0][0]._fw);

  readT = std::thread(readDataF, tmp, windIn[0][0]._nw, windIn[0][0]._fw);

  // Loop over output space
  for (int iout = 0; iout < windOut.size(); iout++) {
    // Create  the output
    std::shared_ptr<float5DReg> out =
        image->createWindow(windOut[iout]._nw, windOut[iout]._fw);

    // Loop over input space
    for (int iin = 0; iin < windIn[iout].size(); iin++) {
      // Wait for the read for this block to be finished

      readT.join();

      // Copy the read volume
      std::shared_ptr<float5DReg> in = tmp->clone();

      // Start the read of the next volume if we aren't at the end
      if (iin < windIn[iout].size() - 1) {
        tmp = data->createWindow(windIn[iout][iin + 1]._nw,
                                 windIn[iout][iin + 1]._fw);

        readT = std::thread(readDataF, in, windIn[iout][iin + 1]._nw,
                            windIn[iout][iin + 1]._fw);
      } else if (iout < windIn.size() - 1) {
        readT = std::thread(readDataF, in, windIn[iout + 1][0]._nw,
                            windIn[iout + 1][0]._fw);
        tmp = data->createWindow(windIn[iout + 1][0]._nw,
                                 windIn[iout + 1][0]._fw);
      }

      // Migration this volume
      mig->apply(in, out);
    }

    if (iout != 0) {
      // If this isn't the first volume wait for the last write to be
      // finished

      writeT.join();
    }
    // Write out the next portion
    writeT =
        std::thread(writeImageF, out, windOut[iout]._nw, windOut[iout]._fw);
  }

  // Wait for the last write to be finished
  writeT.join();
  }
