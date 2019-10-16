#include "basicLoop.h"
#include "floatHyper.h"
namespace SEP {
namespace model {

class spikeVal {
 public:
  spikeVal(const float mag, std::map<int, int> loc) : _loc{loc}, _mag{mag} { ; }
  std::map<int, int> _loc;
  float _mag;
};

/*!
Class for creating spikes and plane waves
*/

class floatSpike : public SEP::loop::blockIOReg {
 public:
  /*!
    iaxes - Axes to spread/stack over
    adj  - Whether or not to apply the adjoint
    */

  floatSpike(std::shared_ptr<hypercube> hyper, std::vector<spikeVal> &vals)
      : _hyper(hyper), _vals{vals} {
    ;
  }

  virtual void applyOut(std::shared_ptr<regSpace> out);

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
  Get any extra memory used by program
  */
  virtual long long getExtraMem() { return 0; }

  /*!
  Return the maximum input size needed given output size
  \param outP Output dimensions
  */
  virtual SEP::loop::windP getInputSize(const SEP::loop::windP &window) {
    SEP::loop::windP x = window;
    return x;
  }

 protected:
  std::vector<spikeVal> _vals;
  std::shared_ptr<hypercube> _hyper;
};

}  //  namespace model
}  // namespace SEP
