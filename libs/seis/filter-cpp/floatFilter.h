#include "floatHyper.h"
#include "rectFilter.h"

namespace SEP {
namespace filter {
/*!
Class fpr stacking (adjoing) or spreading (forward)
*/
class floatfilter1D {
 public:
  /*!
    iaxes - Axes to spread/stack over
    adj  - Whether or not to apply the adjoint
    */

  floatfilter1D(std::shared_ptr<rectFilter1D> filt) { _filt = filt; }

  void applyIt(std::shared_ptr<regSpace> in, std::shared_ptr<regSpace> out);

 protected:
  std::shared_ptr<rectFilter1D> _filt;
};

}  //  namespace filter
}  // namespace SEP
