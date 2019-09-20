#ifndef CALC_BLOCK_H
#define CALC_BLOCK_H 1
#include <map>
#include <string>
#include <vector>
namespace SEP {

namespace blocking {

/* Internal class to store dataset*/

class dataS {
 public:
  dataS() { ; }
  dataS(const std::vector<int> &nd, const int ndimMin, const int esize) {
    _nd = nd;
    _ndimMin = ndimMin;
    _esize = esize;
    _nbase = _esize;
    _nbs.resize(nd.size());
    for (auto i = 0; i < _ndimMin; i++) {
      _nbs[i] = _nd[i];
      _nbase *= _nd[i];
    }
  }
  std::vector<int> _nd;
  int _ndimMin;
  int _esize;
  long long _nbase;
  std::vector<int> _nbs;
};

/*!
   Class to figure out maximum blocksize*/
class blockSizeCalc {
 public:
  /*!
  Initalize with amount of memory available

   \param mem - Memory in bytes
   */
  blockSizeCalc(long long mem) { _mem = mem; }
  /*!
    Add a dataset that needs to looped through
    \param Name of dataset
    \param nd Data dimensons
    \param ndimMin Minimum of number of dimensions that need to be held for the
    dataset \param esize Element size
    */

  void addData(const std::string &name, const std::vector<int> &nd,
               const int ndimMin, const int esize) {
    _datas[name] = dataS(nd, ndimMin, esize);
  }
  /*!
  Calc block
  */
  void calcBlocks();
  /*!
   Return block size
   \param name Name of dataset
   */
  std::vector<int> getBlockSize(const std::string &name) {
    return _datas[name]._nbs;
  }

 private:
  long long _mem;
  std::map<std::string, dataS> _datas;
};
}  // namespace blocking
}  // namespace SEP

#endif