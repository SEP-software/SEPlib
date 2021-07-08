#ifndef BASIC_LOOP_H
#define BASIC_LOOP_H 1

#include "regVector.h"

#include <memory>
#include "genericFile.h"

#include "SEPException.h"

namespace SEP
{
  namespace loop
  {

    /*!
  Simple class to contain windowing parameters
*/
    class windP
    {
    public:
      /*!
     Create windowing object

   \param nw Number of samples

   \param fw Origin of window
  */
      windP(const std::vector<int> nw, const std::vector<int> fw,
            const std::vector<int> jw)
      {
        _nw = nw;
        _fw = fw;
        _jw = jw;
      }
      /*!
    Simple = operator
  */
      windP &operator=(windP other)
      {
        _nw = other._nw;
        _fw = other._fw;
        _jw = other._jw;
        return *this;
      }
      std::vector<int> _nw, _fw, _jw; ///<  Number,origin, and sampling
    };
    /*!
  Basic looping class. Given some windowing parameters will produce a loop given
  maximum block size
*/
    class basicLoop
    {
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
                const std::vector<int> fw, const std::vector<int> jw)
      {
        storeParams(n, nw, fw, jw);
      }

      /*! Store basic parameters into the class

  \param n Data size

  \param nw Number of samples

  \param fw First sample along each axis

  \param jw Skip parameter along each axis


  */

      void storeParams(const std::vector<int> n, const std::vector<int> nw,
                       const std::vector<int> fw, const std::vector<int> jw)
      {
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

      std::vector<int> _n, _fw, _nw, _jw; ///< Size, window n,f,j

      int _ndata;
    };

    /*!
  Virtual class to loop through dataset */
    class blockIO
    {
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
                       const std::vector<int> nbIn)
      {
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

      virtual void loopData(std::shared_ptr<SEP::genericReg> in,
                            std::shared_ptr<SEP::genericReg> out)
      {
        throw SEPException("Loop through data applying operator");
      }

      /*!
  Loop through data applying operator

  \param in Input file

  \param out Output file

  */

      virtual void loopDataInOut(std::shared_ptr<SEP::genericReg> in,
                                 std::shared_ptr<SEP::genericReg> out);

      /*!
  Loop through data applying operator

  \param in Input file


  */

      virtual void loopDataIn(std::shared_ptr<SEP::genericReg> in)
      {
        _inF = in;
        _hyperIn = in->getHyper();
        loopData(in, nullptr);
      }

      /*!
    Apply operator just on input

    \param in regSpace

  */
      virtual void applyIn(const std::shared_ptr<SEP::regSpace> in)
      {
        throw SEPException("Must override applyIn");
      }

      /*!
    Apply operator just on output

    \param out regSpace

  */
      virtual void applyOut(std::shared_ptr<SEP::regSpace> out)
      {
        throw SEPException("Must override applyOut");
      }
      /*!
    Apply operator on input and output

    \oaram in regSace

    \param out regSpace

  */
      virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                              std::shared_ptr<SEP::regSpace> out)
      {
        throw SEPException("Must override applyInOut");
      }
      /*!
  Loop through data applying operator



  \param out Output file

  */
      virtual void loopDataOut(std::shared_ptr<SEP::genericReg> out)
      {
        _outF = out;

        _hyperOut = out->getHyper();

        loopData(nullptr, out);
      }
      /*!  Create output hypercube from input hypercube

     \param hyperIn Input hypercube

  */
      virtual std::shared_ptr<hypercube> createHyperOut(
          const std::shared_ptr<hypercube> hyperIn)
      {
        throw SEPException("Must override createHyperOut");
      }

      /*!
    Minimum number of dimensions that need to be held in memory */
      virtual int getMinDims() { throw SEPException("Must override getMinDims"); }

      /*! Get data type for the input  */
      virtual SEP::dataType getDataTypeIn() { return SEP::DATA_FLOAT; }

      /*! Get data type for the output  */
      virtual SEP::dataType getDataTypeOut() { return SEP::DATA_FLOAT; }
      /*!
  Get any extra memory used by program
  */
      virtual long long getExtraMem() { return 0; }

      /*!
  Return the maximum input size needed given output size
  \param outP Output dimensions
  */
      virtual windP getInputSize(const windP &window)
      {
        throw SEPException("Must override getMaxInputSize");
      }
      /*!
    return Hypercube in*/
      std::shared_ptr<SEP::hypercube> getHyperIn() { return _hyperIn; }
      /*!
    return Hypercube out*/
      std::shared_ptr<SEP::hypercube> getHyperOut() { return _hyperOut; }

    protected:
      std::shared_ptr<SEP::genericReg> _inF, _outF;
      std::shared_ptr<SEP::hypercube> _hyperIn, _hyperOut;
      std::vector<SEP::loop::windP> _loopIn, _loopOut;
    };
    class blockIOReg : public blockIO
    {
    public:
      blockIOReg() { ; }

      /*!
Loop through data applying operator

\param in Input file

\param out Output file

*/

      virtual void loopData(std::shared_ptr<SEP::genericReg> in,
                            std::shared_ptr<SEP::genericReg> out);

      /*!
    Create hypercube given window parameters
    \param hyper Hypercube to base limits on
    \param nw,fw,jw Windowing parameters */
      virtual std::shared_ptr<SEP::hypercube> createSubset(
          std::shared_ptr<SEP::hypercube> hyper, const std::vector<int> nw,
          const std::vector<int> fw, const std::vector<int> jw);
    };
    /*!
Class to "pipe" several events in memory*/
    class blockIORegPipe : public blockIOReg
    {
    public:
      blockIORegPipe() { ; }
      /*!
   Initialize blockIO object
   \param inF Input file
   \param outF Output file
     \param ops Operations to run
     \param maxM Maximum memory in bytes */
      void setupPipe(std::shared_ptr<SEP::genericReg> inF,
                     std::shared_ptr<SEP::genericReg> outF,
                     std::vector<std::shared_ptr<blockIOReg>> &ops,
                     const long long maxM);
      /*!
    Apply operator on input and output

    \oaram in regSace

    \param out regSpace

  */
      virtual void applyInOut(const std::shared_ptr<SEP::regSpace> in,
                              std::shared_ptr<SEP::regSpace> out);

      /*!
    Number of copies of required blocks we can hold in memory

    \param Maximum memory to use
    \param outputSize Output buffer size
    */
      long long testHoldInMemory(const long long mem, std::vector<int> outputSize);

    private:
      std::vector<std::shared_ptr<blockIOReg>> _ops;
      std::vector<std::vector<SEP::loop::windP>> _loopMid;
    };

  } // namespace loop
} // namespace SEP
#endif
