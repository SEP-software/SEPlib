#ifndef BASIC_LOOP_H
#define BASIC_LOOP_H 1

#include "regVector.h"

#include <memory>
#include "genericFile.h"

#include "SEPException.h"

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


    */

  void checkLogic(const int n, const int nw, const int fw, const int jw,
                  const int b) const;

  std::vector<int> _n, _fw, _nw, _jw;  ///< Size, window n,f,j

  int _ndata;
};

/*!
  Virtual class to loop through dataset */
class blockIO {
 public:
  blockIO() { ; }

  /*!
  Store basic parameters into the class

    \param n Data size

    \param nw Number of samples

    \param fw First sample along each axis

    \param jw Skip parameter along each axis

    \param nb Blocksize for IO


  */
  void storeParams(const std::vector<int> n, const std::vector<int> nw,
                   const std::vector<int> fw, const std::vector<int> jw,
                   const std::vector<int> nbIn) {
    std::shared_ptr<SEP::loop::basicLoop> basic(
        new SEP::loop::basicLoop(n, nw, fw, jw));
    _loopIn = basic->createLoop(nbIn);
    _loopOut = basic->createLoop(nbIn);
  }

  /*!
  Store basic parameters into the class

    \param nIn Input Data size

    \param nOut Output Data size

    \param nw Number of samples

    \param fw First sample along each axis

    \param jw Skip parameter along each axis

    \param nb Blocksize for IO input

    \param nb Blocksize for IO output

  */
  void storeParams(const std::vector<int> nIn, const std::vector<int> nOut,
                   const std::vector<int> nw, const std::vector<int> fw,
                   const std::vector<int> jw, const std::vector<int> nbIn,
                   const std::vector<int> nbOut);
  /*!
  Loop through data applying operator

  \param in Input file

  \param out Output file

  */

  virtual void loopData(std::shared_ptr<SEP::genericRegFile> in,
                        std::shared_ptr<SEP::genericRegFile> out) {
    throw SEPException("Loop through data applying operator");
  }

  /*!
  Loop through data applying operator

  \param in Input file

  \param out Output file

  */

  virtual void loopDataInOut(std::shared_ptr<SEP::genericRegFile> in,
                             std::shared_ptr<SEP::genericRegFile> out);

  /*!
  Loop through data applying operator

  \param in Input file


  */

  virtual void loopDataIn(std::shared_ptr<SEP::genericRegFile> in) {
    _inF = in;
    _hyper = in->getHyper();
    loopData(in, nullptr);
  }

  /*!
    Apply operator just on input

    \param in regSpace

  */
  virtual void applyIn(const std::shared_ptr<SEP::regSpace> in) {
    throw SEPException("Must override applyIn");
  }

  /*!
    Apply operator just on output

    \param out regSpace

  */
  virtual void applyOut(std::shared_ptr<SEP::regSpace> out) {
    throw SEPException("Must override applyOut");
  }
  /*!
    Apply operator on input and output

    \oaram in regSace

    \param out regSpace

  */
  virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                          std::shared_ptr<SEP::regSpace> out) {
    throw SEPException("Must override applyInOut");
  }
  /*!
  Loop through data applying operator



  \param out Output file

  */
  virtual void loopDataOut(std::shared_ptr<SEP::genericRegFile> out) {
    _outF = out;
    _hyper = out->getHyper();
    loopData(nullptr, out);
  }

 protected:
  std::shared_ptr<SEP::genericRegFile> _inF, _outF;
  std::shared_ptr<SEP::hypercube> _hyper;
  std::vector<SEP::loop::windP> _loopIn, _loopOut;
};
class blockIOReg : public blockIO {
 public:
  blockIOReg() { ; }

  /*!
Loop through data applying operator

\param in Input file

\param out Output file

*/

  virtual void loopData(std::shared_ptr<SEP::genericRegFile> in,
                        std::shared_ptr<SEP::genericRegFile> out);

  /*!
    Create hypercube given window parameters

    \param nw,fw,jw Windowing parameters */
  virtual std::shared_ptr<SEP::hypercube> createSubset(
      const std::vector<int> nw, const std::vector<int> fw,
      const std::vector<int> jw);
};
}  // namespace loop
}  // namespace SEP
#endif