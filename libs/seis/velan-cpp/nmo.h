#ifndef NMO_H
#define NMO_H 1
#include "basicLoop.h"
#include "calcBlock.h"
#include "floatHyper.h"
#include "sinc.h"
#include "vel3D.h"

#include "SEPException.h"
namespace SEP {
namespace velocity {

/*!
Basic class to nmo*/
class nmo {
 public:
  nmo() { ; }
  /*!
    Ge offset squared for each trace
    \param input dataset
    */

  virtual std::vector<float> getOffSq(const std::shared_ptr<regSpace> in) {
    throw SEPException("getOffSq must be overwritten");
  }
  /*!
  Get CMPX location

    \param input dataset
  */
  virtual std::vector<float> getCmpX(const std::shared_ptr<regSpace> in) {
    throw SEPException("getCmpX must be overwritten");

  }  // namespace velocity
     /*!
      Ge CMPY location
   
        \param input dataset
   
      */

  virtual std::vector<float> getCmpY(const std::shared_ptr<regSpace> in) {
    throw SEPException("getCmpY must be overwritten");
  }
  /*!
   Make sinc table for NMO */
  void mkSinc() { _sinc = sinc(8, .0001); }
  /*!
    \param input array
    \param output array
   */
  virtual void applyIt(std::shared_ptr<regSpace> in,
                       std::shared_ptr<regSpace> out);

  /*!
   Return whether 2 or 3-D
   */
  virtual bool is3D() { throw SEPException("Must override is3D"); }

  /*!
  Whether or not to run a stretch mute
  */
  void stretchMute(const bool muteIt) { _muteIt = muteIt; }
  /*!
  Set the stretch mute parameter
  */

  void setSmute(const float smute) { _osmute = 1. / smute; }
  /*!
  Whether or not to do the inverse
  */
  void doInverse(const bool st) { _inverse = st; }

  /*!
    Create output hypercube, given input hypercube
     */
  virtual std::shared_ptr<hypercube> createHyperOut(
      const std::shared_ptr<hypercube> hyperIn) {
    return hyperIn->clone();
  }

  /*!
    Minimum number of dimensions that need to be held in memory */
  virtual int getMinDims() { return 1; }


  /*!
  Return the maximum input size needed given output size
  \param outP Output dimensions
  */
  virtual SEP::loop::windP getInputSize(const SEP::loop::windP &window) {
    SEP::loop::windP x = window;
    return x;
  }

 protected:
  std::shared_ptr<SEP::velocity::vel3D> _vel;  ///< Velocity
  int _nt;                                     ///< Number of samples in time
  float _ot;                                   ///< First sample in time
  float _dt;                                   ///< Sampling in time
  float _osmute;                               ///< Invese stretch mute
  sinc _sinc;                                  ///< Sinc table
  bool _muteIt = true;                         ///< Whether or not mute
  bool _inverse = false;                       ///< Whether or not to do inverse
};                                             // namespace velocity

class nmoRegCube : public SEP::loop::blockIO, public nmo {
 public:
  nmoRegCube() { ; }

  nmoRegCube(std::shared_ptr<SEP::velocity::vel3D> vel, const axis &aTime,
             const std::vector<int> ioffAxes, const int cmpXAxis,
             const int cmpYAxis);
  /*!
    \param input array
    \param output array
   */
  virtual void applyInOut(std::shared_ptr<regSpace> in,
                          std::shared_ptr<regSpace> out) override {
    applyIt(in, out);
  }
  virtual std::vector<float> getOffSq(
      const std::shared_ptr<regSpace> in) override;
  virtual std::vector<float> getCmpX(
      const std::shared_ptr<regSpace> in) override;
  virtual std::vector<float> getCmpY(
      const std::shared_ptr<regSpace> in) override;
  /*!
  Get any extra memory used by program
  */
  virtual long long getExtraMem() override { return _vel->getVelSize(); }
  virtual bool is3D() override {
    if (_cmpYAxis > 0) return true;
    return false;
  }

 private:
  std::vector<int> _ioffAxes;
  int _cmpXAxis, _cmpYAxis;
};

}  // namespace velocity
}  // namespace SEP

#endif
