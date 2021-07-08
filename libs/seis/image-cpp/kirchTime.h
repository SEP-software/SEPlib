#include <float1DReg.h>
#include <float3DReg.h>
#include <float5DReg.h>
#include <genericIO.h>
#include <ctime>
#include <memory>
#include "vel3D.h"

namespace SEP {
namespace KirchTime {

    /*!
      Basic subset class
    */
    class dataND {
 public:
  /*!
     Create data sub object
    */
  dataND() { ; }

  /*!
     Return hypercube coresponding to dataset
     */

  std::shared_ptr<hypercube> getHyper() { return _hyper; }
  virtual ~dataND() { ; }
  std::shared_ptr<genericReg> getFile() {
    if (!_file) throw SEPException("File has not been defined");
    return _file;
  }

 protected:
  std::shared_ptr<hypercube> _hyper;
  std::shared_ptr<genericReg> _file;
  float _aper;
};

/*!
    Class for a 5-D regulary sampled dataset

*/
class data3DReg : public dataND {
 public:
  /*!
     Create dataset from file


   \param file File object for dataset

 */

  data3DReg(std::shared_ptr<genericReg> file);

  /*!
      Set window we care about

      \param hyper - Hypercube describing domain we are modeling

      \param aper  -  Aperture for migration
    */

  void setWindow(std::shared_ptr<hypercube> hyper, const float aper);

  /*!
    Read a window of the dataset
*/

  std::shared_ptr<float3DReg> read();

  long long getSize() {
    return (long long)_nw[0] * (long long)_nw[1] * (long long)_nw[2];
  }
  ~data3DReg() { ; }

 private:
  std::vector<int> _nw, _fw;
};

class data5DReg : public dataND {
 public:
  /*!
       Create dataset from file


     \param file File object for dataset



   */

  data5DReg(std::shared_ptr<genericReg> file);
  /*!

     Create output dataset (based on parameters)


    \param input  Input dataset to take subset of

    \param aX   X axis for output

    \param aY   Y axis for output

  */

  data5DReg(std::shared_ptr<data5DReg> input, const axis aX, const axis aY);

  /*!

     Create output dataset (based on parameters)


    \param input  Input dataset to take subset of

    \param aOX   Offset X axis for output

    \param aOY   Offset Y axis for output

    \param aX   X axis for output

    \param aY   Y axis for output

  */

  data5DReg(std::shared_ptr<data3DReg> input, const axis aOX, const axis aOY,
            const axis aX, const axis aY);

  /*!
     Check whether velocity is at least as large as dataset

    \param vrms  Velocity file
  */
  void checkLogic(std::shared_ptr<SEP::velocity::vel3DFromFile> vrms);

  /*!
      Create a 5-D regularly sampled function a sub-sampled version of dataset

     \param   nwind  Number of samples along each axis

     \param  fwind   First sample along each axis

     \return 5-D float dataset

  */
  std::shared_ptr<float5DReg> createWindow(const std::vector<int> nwind,
                                           const std::vector<int> fwind);
  /*!
      Read a window of the dataset

    \param nwind Number of samples along each axis

    \param fwind First sample along each axis

    \param buf  Storage for dataset

  */
  void readWindow(const std::vector<int> nwind, const std::vector<int> fwind,
                  std::shared_ptr<float5DReg> buf);

  /*!
      Write a window the dataset

    \param nwind Number of samples along each axis

    \param fwind First sample along each axis

    \param buf  Storage for dataset
  */
  void writeWindow(const std::vector<int> nwind, const std::vector<int> fwind,
                   std::shared_ptr<float5DReg> buf);
  /*!
     Return hyperube describing dataset

    \return Hypercube description for dataset

  */
  std::shared_ptr<hypercube> getHyper() { return _hyper; }

  /*!
   Set the data file associated with file

  \param fle - File to read/write to

*/

  ~data5DReg() { ; }

  void setFile(std::shared_ptr<genericReg> fle);
  std::shared_ptr<hypercube> _hyper;  ///< Hypercube describing dataset
};

/*!
    Class to do Kirchhoff Time Migration

*/
/*!
    Class to do Kirchhoff

*/

class basicTime {
 public:
  basicTime() { ; }
  /*!
        Get input sampling (#of elements)  for window around current output
     volume
     */
  std::vector<int> getNin() { return _nin; }
  /*!
     Get input sampling (origin of window)  for window around current output
     volume
  */
  std::vector<int> getFin() { return _fin; }
  /*!
     Get input sampling (blocksize for output window)  for window around current
     output volume
  */
  std::vector<int> getBin() { return _bin; }
  /*!
       Calculate window parameters (range and block size) for input dataset
     given the described output volume

     \param nout  Number of samples along each axis for output

     \param fout  First sample along each axis

 */
  void calcInputWindow(const std::vector<int> nout,
                       const std::vector<int> fout);

 protected:
  long long _mem;
  std::shared_ptr<hypercube> _hyperData, _hyperImage;
  std::vector<int> _nin, _fin, _bin;
  std::shared_ptr<SEP::velocity::vel3DFromFile> _vel;
  float _aper;
};
/*!
    Class to do Kirchhoff Time Modeling
*/

class model : public basicTime {
 public:
  /*!
       Create migration object

     \param inp Input dataset

      \param vel Velocity object

      \param aoper Aperture for the migration

      \param mem  Amount of memory to use

  */
  model(std::shared_ptr<data5DReg> inp,
        std::shared_ptr<SEP::velocity::vel3DFromFile> vel,
        std::shared_ptr<float1DReg> wave, const float aper,
        const long long mem);

  /*!
       Perform time migration

     \param  input Input volume

     \param output Output volume

  */
  void apply(std::shared_ptr<float3DReg> image,
             std::shared_ptr<float5DReg> data);

 private:
  std::shared_ptr<float1DReg> _wave;
};
/*!
    Class to do Kirchhoff Time Migration

*/

class migrate : public basicTime {
 public:
  /*!
       Create migration object

     \param inp Input dataset

      \param vel Velocity object

      \param aoper Aperture for the migration

      \param mem  Amount of memory to use

  */
  migrate(std::shared_ptr<data5DReg> inp,
          std::shared_ptr<SEP::velocity::vel3DFromFile> vel, const float aper,
          const long long mem);

  /*!
       Perform time migration

     \param  input Input volume

     \param output Output volume

  */
  void apply(std::shared_ptr<float5DReg> input,
             std::shared_ptr<float5DReg> output);
};

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
  windP(std::vector<int> nw, std::vector<int> fw) {
    _nw = nw;
    _fw = fw;
  }
  /*!
    Simple = operator
  */
  windP &operator=(windP other) {
    _nw = other._nw;
    _fw = other._fw;
     return *this;
  }
  std::vector<int> _nw, _fw;  ///<  Number and origin of samples
};

class kirchhoffTime {
 public:
  kirchhoffTime(std::shared_ptr<SEP::velocity::vel3DFromFile> v,
                std::shared_ptr<data5DReg> d, const long long mx,
                const float a) {
    vel = v;
    data = d;
    maxs = mx;
    aper = a;
  }
  void modelData(std::shared_ptr<data3DReg> image,
                 std::shared_ptr<float1DReg> wave);
  void migrateData(std::shared_ptr<data5DReg> data);

 private:
  std::shared_ptr<SEP::velocity::vel3DFromFile> vel;
  std::shared_ptr<data5DReg> data;
  float aper;
  long long maxs;
};

inline float sqrt7(float x) {
  unsigned int i = *(unsigned int *)&x;
  // adjust bias
  i += 127 << 23;
  // approximation of square root
  i >>= 1;
  return *(float *)&i;
}
}  // namespace KirchTime
}  // namespace SEP
