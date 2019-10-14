#include "basicLoop.h"
#include "floatHyper.h"
#include "rectFilter.h"
#ifndef FILTER_H
#define FILTER_H 1
namespace SEP {
namespace filter {
/*!
Class fpr stacking (adjoing) or spreading (forward)
*/
class floatFilter1D : public SEP::loop::blockIOReg {
 public:
  /*!
    iaxes - Axes to spread/stack over
    adj  - Whether or not to apply the adjoint
    */

  floatFilter1D(std::shared_ptr<rectFilter1D> filt) { _filt = filt; }

  virtual std::shared_ptr<hypercube> createHyperOut(
      const std::shared_ptr<hypercube> hyperIn) {
    throw SEPException("Must override createHyperOut");
  }

  /*!
    Minimum number of dimensions that need to be held in memory */
  virtual int getMinDims() { return 1; }

  /*!
  Return the maximum input size needed given output size
  \param outP Output dimensions
  */
  virtual SEP::loop::windP getInputSize(const SEP::loop::windP &window) {
    SEP::loop::windP w = window;
    return w;
  }

  virtual void applyInOut(std::shared_ptr<regSpace> in,
                          std::shared_ptr<regSpace> out) override;

 protected:
  std::shared_ptr<rectFilter1D> _filt;
};

}  //  namespace filter
}  // namespace SEP
#endif