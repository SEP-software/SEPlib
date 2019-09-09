#include "floatHyper.h"
namespace SEP {
namespace filter {
/*!
Class fpr stacking (adjoing) or spreading (forward)
*/
class floatStackSpreadReg {
 public:
  /*!
    iaxes - Axes to spread/stack over
    adj  - Whether or not to apply the adjoint
    */

  floatStackSpreadReg(const std::vector<int> iaxes, bool adj) {
    _iaxes = iaxes;
    _adj = adj;
  }

  void applyIt(std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out);

 protected:
  std::vector<int> _iaxes;
  bool _adj;
};

}  //  namespace filter
}  // namespace SEP
