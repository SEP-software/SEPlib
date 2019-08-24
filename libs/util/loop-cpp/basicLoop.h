#ifndef BASIC_LOOP_H
#define BASIC_LOOP_H 1

#include <float1DReg.h>
#include <float3DReg.h>
#include <float5DReg.h>
#include <memory>

namespace SEP {
namespace loop {

/*!
  Simple class to contain windowing parameters
*/
class windP {
 public:
  /*!
     Create windowing object

   \param nw Number of samples

   \param fw Origin of window
  */
  windP(const std::vector<int> nw, const std::vector<int> fw,
        const std::vector<int> jw) {
    _nw = nw;
    _fw = fw;
    _jw = jw;
  }
  /*!
    Simple = operator
  */
  windP &operator=(windP other) {
    _nw = other._nw;
    _fw = other._fw;
    _jw = other._jw;
  }
  std::vector<int> _nw, _fw, _jw;  ///<  Number,origin, and sampling
};
/*!
  Basic looping class. Given some windowing parameters will produce a loop given
  maximum block size
*/
class basicLoop {
 public:
  /*!
    Deefault class
    */
  basicLoop() { ; }
  /*! Create Basic looping operator

  \param n Data size

  \param nw Number of samples

  \param fw First sample along each axis

  \param jw Skip parameter along each axis

  */
  basicLoop(const std::vector<int> n, const std::vector<int> nw,
            const std::vector<int> fw, const std::vector<int> jw) {
    storeParams(n, nw, fw, jw);
  }

  /*! Store basic parameters into the class

  \param n Data size

  \param nw Number of samples

  \param fw First sample along each axis

  \param jw Skip parameter along each axis

  */

  void storeParams(const std::vector<int> n, const std::vector<int> nw,
                   const std::vector<int> fw, const std::vector<int> jw) {
    _n = n;
    _nw = nw;
    _fw = fw;
    _jw = jw;
  }
  /*! Extend vectors to length 9

  \param x input vector

  \param def Default valiue

  @return Extended vector

  */

  std::vector<int> create9(const std::vector<int> x, const int def) const;

  /*! Create a loop given blocksize

  \param nblock Maximum block size

  @return Vector of windowing parameters to go through whole dataset
  */
  std::vector<windP> createLoop(const std::vector<int> nblock);
  /*!

  Check to make sure parameters make sense


    \param n  Length of axis

    \param nw Number of samples

    \param fw First sample

    \param jw Skip parameter

    \param b Blocksize

    */

  void checkLogic(const int n, const int nw, const int fw, const int jw,
                  const int b) const;

 protected:
  std::vector<int> _n, _fw, _nw, _jw;  ///< Size, window n,f,j
};

}  // namespace loop
}  // namespace SEP
#endif