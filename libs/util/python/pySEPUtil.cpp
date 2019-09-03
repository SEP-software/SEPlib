
#include <pybind11/pybind11.h>

#include "basicLoop.h"
#include "doubleLoop.h"
#include "kirchTime.h"
#include "vel3D.h"
using namespace SEP::loop;

namespace py = pybind11;
namespace SEP {

PYBIND11_MODULE(pySEPUtil, clsUtil) {
  /*

   Looping
  */
  py::class_<windP>(clsUtil, "windP")

      .def(py::init<const std::vector<int>, const std::vector<int>,
                    const std::vector<int>>(),
           "Initialize by vectors of number of samples, first sample, skip ")

      .def_readwrite("nw", &windP::_nw)
      .def_readwrite("fw", &windP::_fw)
      .def_readwrite("jw", &windP::_jw)

      ;

  py::class_<basicLoop, std::shared_ptr<basicLoop>>(clsUtil, "basicLoop")

      .def(py::init<const std::vector<int>, const std::vector<int>,
                    const std::vector<int>, const std::vector<int>>(),
           "Initialize from data siz and window parameters (nw,fw,jw)")
      .def("createLoop",
           (std::vector<windP>(basicLoop::*)(const std::vector<int>)) &
               basicLoop::createLoop,
           "Create looping parameters");

  py::class_<doubleWindP>(clsUtil, "doubleWindP")  //
      .def(py::init<>(), "Initlialize an empty set")
      .def_readwrite("innerLoop", &doubleWindP::innerLoop)
      .def_readwrite("outerLoop", &doubleWindP::outerLoop);

  py::class_<loopCalc, std::shared_ptr<loopCalc>>(clsUtil, "loopCalc")

      .def(py::init<>(), "Dummy class for loop calc")
      .def("loopDependParams",
           (windP(loopCalc::*)(const std::vector<int>, const std::vector<int>,
                               const std::vector<int>)) &
               loopCalc::loopDependParams,
           "Create looping parameters");

  py::class_<doubleLoop, std::shared_ptr<doubleLoop>>(clsUtil, "doubleLoop")

      .def(py::init<const std::vector<int>, const std::vector<int>,
                    const std::vector<int>, const std::vector<int>,
                    std::shared_ptr<loopCalc>>(),
           "Initialize from data siz and window parameters (nw,fw,jw)")

      .def("createLoop",
           (std::shared_ptr<doubleWindP>(doubleLoop::*)(
               const std::vector<int>, const std::vector<int>)) &
               doubleLoop::createLoop,
           "Create looping parameters")

      ;

  /*
  Velocity
  */

  py::class_<SEP::velocity::vel3DFromFile,
             std::shared_ptr<SEP::velocity::vel3DFromFile>>(clsUtil,
                                                            "vel3DFromFile")
      .def(py::init<std::shared_ptr<genericRegFile>>(),
           "Initialize velocity with file object")
      .def("readVelocity",
           (long long (SEP::velocity::vel3DFromFile::*)(
               std::shared_ptr<hypercube>, const long long)) &
               SEP::velocity::vel3DFromFile::readVelocity,
           "Read the velocity from a file");

  /*

  Kirchhoff

  */

  py::class_<SEP::KirchTime::data3DReg,
             std::shared_ptr<SEP::KirchTime::data3DReg>>(clsUtil, "data3DReg")
      .def(py::init<std::shared_ptr<genericRegFile>>(),
           "Initialize a 3-D dataset object")
      .def("getHyper",
           (std::shared_ptr<hypercube>(SEP::KirchTime::data3DReg::*)()) &
               SEP::KirchTime::data3DReg::getHyper,
           "Get hypercube")
      .def("read",
           (long long (SEP::KirchTime::data3DReg::*)()) &
               SEP::KirchTime::data3DReg::read,
           "Read from a file");

  py::class_<SEP::KirchTime::data5DReg,
             std::shared_ptr<SEP::KirchTime::data5DReg>>(clsUtil, "data5DReg")

      .def(py::init<std::shared_ptr<SEP::KirchTime::data5DReg>, const axis,
                    const axis>(),
           "Initialize a 5-D dataset object replacing midpoint axes")
      .def(py::init<std::shared_ptr<SEP::KirchTime::data3DReg>, const axis,
                    const axis, const axis, const axis>(),
           "Initialize a 5-D dataset object replacing midpoint and offset axes")
      .def(py::init<std::shared_ptr<genericRegFile>>(),
           "Initialize a 5-D dataset object with a file")
      .def("getHyper",
           (std::shared_ptr<hypercube>(SEP::KirchTime::data5DReg::*)()) &
               SEP::KirchTime::data5DReg::getHyper,
           "Get hypercube")
      .def("getFile",
           (std::shared_ptr<genericRegFile>(SEP::KirchTime::data5DReg::*)()) &
               SEP::KirchTime::data5DReg::getFile,
           "Get file")
      .def("checkLogic",
           (void (SEP::KirchTime::data5DReg::*)(
               std::shared_ptr<SEP::velocity::vel3DFromFile>)) &
               SEP::KirchTime::data5DReg::checkLogic,
           "Make sure velocity contains domain")
      .def("setFile",
           (void (SEP::KirchTime::data5DReg::*)(
               std::shared_ptr<genericRegFile>)) &
               SEP::KirchTime::data5DReg::setFile,
           "Set file associated with data structure")
      .def("readWindow",
           (void (SEP::KirchTime::data5DReg::*)(const std::vector<int>,
                                                const std::vector<int>,
                                                std::shared_ptr<float5DReg>)) &
               SEP::KirchTime::data5DReg::readWindow,
           "Read a window of the file")
      .def("writeWindow",
           (void (SEP::KirchTime::data5DReg::*)(const std::vector<int>,
                                                const std::vector<int>,
                                                std::shared_ptr<float5DReg>)) &
               SEP::KirchTime::data5DReg::writeWindow,
           "Write a window to the file");

  py::class_<SEP::KirchTime::model, std::shared_ptr<SEP::KirchTime::model>>(
      clsUtil, "model")
      .def(
          py::init<std::shared_ptr<SEP::KirchTime::data5DReg>,
                   std::shared_ptr<SEP::velocity::vel3DFromFile>,
                   std::shared_ptr<float1DReg>, const float, const long long>(),
          "Initializing a modeling operator")

      .def("apply",
           (void (SEP::KirchTime::model::*)(std::shared_ptr<float3DReg>,
                                            std::shared_ptr<float5DReg>)) &
               SEP::KirchTime::model::apply,
           "Run the modeling operator");

  py::class_<SEP::KirchTime::migrate, std::shared_ptr<SEP::KirchTime::migrate>>(
      clsUtil, "migrate")
      .def(py::init<std::shared_ptr<SEP::KirchTime::data5DReg>,
                    std::shared_ptr<SEP::velocity::vel3DFromFile>, const float,
                    const long long>(),
           "Initializing a modeling operator")

      .def("apply",
           (void (SEP::KirchTime::migrate::*)(std::shared_ptr<float5DReg>,
                                              std::shared_ptr<float5DReg>)) &
               SEP::KirchTime::migrate::apply,
           "Run the modeling operator");

  py::class_<SEP::KirchTime::kirchhoffTime,
             std::shared_ptr<SEP::KirchTime::kirchhoffTime>>(clsUtil,
                                                             "kirchhoffTime")
      .def(py::init<std::shared_ptr<SEP::velocity::vel3DFromFile>,
                    std::shared_ptr<SEP::KirchTime::data5DReg>, const long long,
                    const float>(),
           "Initializing Kirchhoff looping operator")

      .def("modelData",
           (void (SEP::KirchTime::kirchhoffTime::*)(
               std::shared_ptr<SEP::KirchTime::data3DReg>,
               std::shared_ptr<float1DReg>)) &
               SEP::KirchTime::kirchhoffTime::modelData,
           "Run the modeling operator")
      .def("migrateData",
           (void (SEP::KirchTime::kirchhoffTime::*)(
               std::shared_ptr<SEP::KirchTime::data3DReg>)) &
               SEP::KirchTime::kirchhoffTime::migrateData,
           "Run the migration operator");
}
}  // namespace SEP
