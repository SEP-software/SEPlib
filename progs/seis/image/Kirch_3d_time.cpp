

/*$


=head1 NAME

Kirch_3d_time - Kirchhoff 3D migration

=head1 SYNOPSIS

Kirch_3d_time  image=in.H data=out.H  velfile=tfile.H  pars

=cut

>*/
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/tbb.h>

#include <float3DReg.h>
#include <float5DReg.h>
#include <seplib.h>
#include <memory>

#include <float3DReg.h>

#include <genericIO.h>

#include <thread>
#include "ioModes.h"
#include "kirchTime.h"

using namespace SEP;
using namespace SEP::KirchTime;
int main(int argc, char** argv) {
  // Setup IO

  ioModes modes = ioModes(argc, argv);

  std::shared_ptr<genericIO> ioIn = modes.getInputIO(),
                             ioOut = modes.getOutputIO();

  std::shared_ptr<paramObj> par = modes.getParamObj();

  // Amount of memory to use
  long long maxsize =
      (par->getDocInt("maxsize", "Maximum amount of memory to use in GBs", 30) -
       2) *
      (long long)1024 * (long long)1024 * (long long)1024;

  // Initalize files
  std::shared_ptr<vel3d> vel;

  try {
    vel.reset(new vel3d(ioIn->getDocRegFile(
        "velocity", "Velocity file (nt,cmpx,cmpy)", usageIn)));
  } catch (SEPException& e) {
    std::cout << e.what() << std::endl;
    exit(-1);
  }
  bool modelIt = par->getDocBool(
      "model", "Whether to model[true] or migrate[false]", false);

  std::shared_ptr<data5DReg> data, image5;
  std::shared_ptr<data3DReg> image3;
  std::shared_ptr<float1DReg> wave;

  if (!modelIt) {
    std::shared_ptr<genericRegFile> dataF = ioIn->getDocRegFile(
        "data", "Data file (t,ox,oy,cmpx,cmpy)", SEP::usageIn);

    data.reset(new data5DReg(dataF));
    std::vector<axis> axData = data->getHyper()->getAxes();
    axis axX, axY;
    axX.n = par->getDocInt("nx", "Number of CMPs in X for output", axData[3].n);
    axX.o = par->getDocFloat("ox", "First CMPs in X for output", axData[3].o);
    axX.d =
        par->getDocFloat("dx", "Sampling of CMPs in X for output", axData[3].d);
    axY.n = par->getDocInt("ny", "Number of CMPs in Y for output", axData[4].n);
    axY.o = par->getDocFloat("oy", "First  CMPs in y for output", axData[4].o);
    axY.d =
        par->getDocFloat("dy", "Sampling  CMPs in T for output", axData[4].d);
    image5.reset(new data5DReg(data, axX, axY));

    std::shared_ptr<genericRegFile> imageF = ioOut->getDocRegFile(
        "image",
        "Image file (t,cmpx,cmpy)<--modeling migrating-->(t,ox,oy,cmpx,cmpy)",
        SEP::usageOut);
    imageF->setHyper(image5->getHyper());
    image5->setFile(imageF);
  } else {
    std::shared_ptr<genericRegFile> imageF = ioIn->getDocRegFile(
        "image",
        "Image file (t,cmpx,cmpy)<--modeling migrating-->(t,ox,oy,cmpx,cmpy)",
        SEP::usageIn);

    image3.reset(new data3DReg(imageF));

    std::vector<axis> axImage = image3->getHyper()->getAxes();

    axis axX, axY;
    axis axOX, axOY;
    axX.n =
        par->getDocInt("nx", "Number of CMPs in X for output", axImage[1].n);

    axX.o = par->getDocFloat("ox", "First CMPs in X for output", axImage[1].o);
    axX.d = par->getDocFloat("dx", "Sampling of CMPs in X for output",
                             axImage[1].d);
    axY.n =
        par->getDocInt("ny", "Number of CMPs in Y for output", axImage[2].n);
    axY.o = par->getDocFloat("oy", "First CMPs in Y for output", axImage[2].o);
    axY.d = par->getDocFloat("dy", "Sampling of CMPs in Y for output",
                             axImage[2].d);
    axOX.n = par->getDocInt("nox", "Number of Offsets in X for output");
    axOX.o = par->getDocFloat("oox", "First Offsets in X for output");
    axOX.d = par->getDocFloat("dox", "Sampling of Offsets in X for output");
    axOY.n = par->getDocInt("noy", "Number of Offsets in Y for output");
    axOY.o = par->getDocFloat("ooy", "First Offsets in Y for output");
    axOY.d = par->getDocFloat("doy", "Sampling of Offsets in Y for output");
    std::shared_ptr<data5DReg> d(new data5DReg(image3, axOX, axOY, axX, axY));
    data = d;

    std::shared_ptr<genericRegFile> dataF = ioOut->getDocRegFile(
        "data", "Data file (t,ox,oy,cmpx,cmpy)", SEP::usageOut);

    dataF->setHyper(data->getHyper());
    d->setFile(dataF);

    std::shared_ptr<genericRegFile> waveF = ioIn->getDocRegFile(
        "wave", "Wavelet (only needed for modeling)", SEP::usageIn);
    std::shared_ptr<float1DReg> w(new float1DReg(waveF->getHyper()));
    wave = w;

    std::vector<int> fw(1, 0), jw(1, 1), nw(1, waveF->getHyper()->getAxis(1).n);
    try {
      waveF->readWindow(nw, fw, jw, wave);
    } catch (SEPException& x) {
      par->error(x.what());
    }
  }

  // Make sure velocity is at least as big as the output
  data->checkLogic(vel);

  if (!modelIt) {
    // Read velocity
    try {
      maxsize -= vel->readVelocity(image5->getHyper(), maxsize);
    } catch (SEPException& e) {
      std::cout << e.what() << std::endl;
      exit(-1);
    }
  } else {
    try {
      maxsize -= vel->readVelocity(image3->getHyper(), maxsize);

    } catch (SEPException& e) {
      std::cout << e.what() << std::endl;
      exit(-1);
    }
  }
  std::shared_ptr<kirchhoffTime> kir(
      new kirchhoffTime(vel, data, maxsize, par->getFloat("aper")));

  if (modelIt) {
    try {
      kir->modelData(image3, wave);

    } catch (SEPException& e) {
      std::cout << e.what() << std::endl;
      exit(-1);
    }

    data->getFile()->writeDescription();

  } else {
    try {
      kir->migrateData(image5);
    } catch (SEPException& e) {
      std::cout << e.what() << std::endl;
      exit(-1);
    }
    image5->getFile()->writeDescription();
  }
}
