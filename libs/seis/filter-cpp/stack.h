#include "basicLoop.h"
#include "floatHyper.h"
namespace SEP {
namespace filter {
/*!
Class fpr stacking (adjoing) or spreading (forward)
*/
class floatStackSpreadReg : public SEP::loop::blockIOReg {
 public:
  /*!
    iaxes - Axes to spread/stack over
    adj  - Whether or not to apply the adjoint
    */

  floatStackSpreadReg(const std::vector<int> iaxes, bool adj) {
    for (auto ax : iaxes) _iaxes.push_back(ax);
    _adj = adj;
  }

  void applyInOut(std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out);

  /*!
    Create output hypercube, given input hypercube
     */
  virtual std::shared_ptr<hypercube> createHyperOut(
      const std::shared_ptr<hypercube> hyperIn) {
    return hyperIn->clone();
  }

  /*!
    Minimum number of dimensions that need to be held in memory */
  virtual int getMinDims() {
    int imin = 99;
    for (auto i : _iaxes) imin = std::min(imin, i);
    return imin;
  }

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
  std::vector<int> _iaxes;
  bool _adj;
};

}  //  namespace filter
}  // namespace SEP
