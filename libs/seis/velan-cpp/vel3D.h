#ifndef VEL3D_H
#define VEL3D_H 1

#include <float3DReg.h>
#include <genericIO.h>
#include <ctime>
#include <memory>

namespace SEP {
namespace velocity {

/*!
Simple velocity class that is useful for trace based veloicity
*/

class vel3D {
 public:
  vel3D() { ; }

  /*!
     Return a trace containing velocity at a given location in 3-D space

     \param  n1  Number of samples in time

     \param  o1  First sample in time

     \param  d1  Sampling in time

     \param x  Location in X

     \param y  Location in y

      \return Vector containing the velocity

   */
  virtual std::vector<float> getVelocity(const int n1, const float o1,
                                         const float d1, const float x,
                                         const float y) = 0;

  /*!
     Return a trace containing velocity at a given location in 3-D space

     \param  n1  Number of samples in time

     \param  o1  First sample in time

     \param  d1  Sampling in time

     \param x  Location in X


      \return Vector containing the velocity

   */
  virtual std::vector<float> getVelocity(const int n1, const float o1,
                                         const float d1, const float x);

  /*!
    Get the maximum velocity

    @return maximum velocity
    */
  virtual float getMax() = 0;
  ~vel3D() { ; }

 protected:
  std::vector<axis> _axes;  ///< Axes for velocity
};
/*!
Constant velocity
*/

class vel3DConstant : public vel3D {
 public:
  /*! Initialixze  constant velocity object

     val Constant velocity to initialize with
     */
  vel3DConstant(const float val);
  /*!
     Return a trace containing velocity at a given location

     \param  n1  Number of samples in time

     \param  o1  First sample in time

     \param  d1  Sampling in time

     \param x  Location in X

     \param y  Location in y

      \return Vector containing the velocity

   */
  virtual std::vector<float> getVelocity(const int n1, const float o1,
                                         const float d1, const float x,
                                         const float y);
  /*!
    Return maximum velocity
    */
  virtual float getMax() { return _val; }

 private:
  float _val;
};

class vel3DCube : public vel3D {
 public:
  vel3DCube() { ; }

  /*!
     Return a trace containing velocity at a given location

     \param  n1  Number of samples in time

     \param  o1  First sample in time

     \param  d1  Sampling in time

     \param x  Location in X

     \param y  Location in y

      \return Vector containing the velocity

   */
  virtual std::vector<float> getVelocity(const int n1, const float o1,
                                         const float d1, const float x,
                                         const float y) override;

  /*!
     Return hypercube

  */
  ~vel3DCube() { ; }

  /*!
     Return maximum velocity
     */
  virtual float getMax() override { return _values->max(); }

 protected:
  std::shared_ptr<float3DReg> _values;  ///< Value for the velocity
};
class vel3DFromArray : public vel3DCube {
 public:
  /*!
    Create a velocity object from an existing array

    vals -3D Float array of velocity

    */
  vel3DFromArray(std::shared_ptr<float3DReg> vals);

  ~vel3DFromArray() { ; }
};

class vel3DFromFile : public vel3DCube {
 public:
  /*!
       Initalize the velocity object


    \param file FIle object for velocity
   */

  vel3DFromFile(std::shared_ptr<genericRegFile> file);

  /*!
 Initialize with constant

/*!
    Read  velocity (most likely a subset

  \param  output   Describing output space

  \param maxMem    Maximum amount of memory to use
*/

  long long readVelocity(std::shared_ptr<hypercube> output,
                         const long long maxMem);

  /*!
  Return hypercube associated with velocity file

  @hypercube
  */
  std::shared_ptr<hypercube> getHyper() { return _file->getHyper(); }
  ~vel3DFromFile() { ; }

 private:
  std::shared_ptr<genericRegFile> _file;  ///< File object
};
class vel3dFromArray : public vel3DCube {
 public:
};

}  // namespace velocity
}  // namespace SEP

#endif