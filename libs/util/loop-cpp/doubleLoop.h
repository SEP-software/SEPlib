#ifndef DOUBLE_LOOP_H
#define DOUBLE_LOOP_H 1

#include <SEPException.h>
#include <float1DReg.h>
#include <float3DReg.h>
#include <float5DReg.h>
#include <memory>
#include "basicLoop.h"

namespace SEP {
namespace loop {

/*!
  Simple class to contain windowing parameters for double (inner loop depends on
  outer loop)
*/

class doubleWindP {
 public:
  /*!
   Default class
   */
  doubleWindP() { ; }

  std::vector<std::vector<windP>> innerLoop;  ///< Inner loop parameters
  std::vector<windP> outerLoop;               ///< Outer Loop parameters
};

/*!
  Virtual loop class. From outer loop window parameter return inner loop
  parameters
  */
class loopCalc {
 public:
  /*!
   Default constructor
   */
  loopCalc() { ; }

  /*!
     \param nw  Outer number of samples

     \param fw First sample


     \param jw  Skip parameters

     @return Window to loop through given input
     */
  virtual windP loopDependParams(const std::vector<int> nw,
                                 const std::vector<int> fw,
                                 const std::vector<int> jw) {
    throw SEPException(std::string("Must override loopDependParams"));
  }
};
/*
  Class where the loop of one dataset isn't simple the same as the other dataset
  (think Kirchhoff migration)
  */
class doubleLoop : public basicLoop {
 public:
  /*! Create Basic looping operator

\param n Data size

\param nw Number of samples

\param fw First sample along each axis

\param jw Skip parameter along each axis

\param class definng how second dataset window relates to first dataset window

*/

  doubleLoop(const std::vector<int> n, const std::vector<int> nw,
             const std::vector<int> fw, const std::vector<int> jw,
             std::shared_ptr<loopCalc> calc) {
    storeParams(n, nw, fw, jw);
    _calc = calc;
  }

  /*! Create a loop given blocksize

  \param nblockOut Maximum block size output

    \param nblockIn Maximum block size input


  @return Windowing parameters to go through both datasets
  */

  std::shared_ptr<doubleWindP> createLoop(const std::vector<int> nblockOut,
                                          const std::vector<int> nblockIn);

 private:
  std::shared_ptr<loopCalc> _calc;  ///< Class relating looping od datasets
};

}  // namespace loop
}  // namespace SEP
#endif