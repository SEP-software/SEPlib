#include "calcBlock.h"
#include "SEPException.h"
void SEP::blocking::blockSizeCalc::calcBlocks() {
  long long nbase = 0;

  for (auto d : _datas) nbase += d.second._nbase;

  if (nbase == 0) throw SEPException("No datasets available");
  auto first = _datas.begin()->second;
  int nfirst = first._nd.size() - first._ndimMin;

  nbase *= 2;

  if (nbase > _mem)
    throw SEPException(std::string("Not enough memory requested, minimum ") +
                       std::to_string(nbase / 1000 / 1000));
  for (auto i = _datas.begin(); i != _datas.end(); i++) {
    if (i == _datas.begin()) continue;
    int ndat = i->second._nd.size() - i->second._ndimMin;
    for (int idim = 0; idim < std::min(nfirst, ndat); idim++) {
      if (first._nd[idim + first._ndimMin] !=
          i->second._nd[idim + i->second._ndimMin])
        throw SEPException(
            std::string("Axis ") + std::to_string(idim + first._ndimMin) +
            std::string(" of ") + _datas.begin()->first +
            std::string(" length=") + std::to_string(idim + first._ndimMin) +
            std::string(" not equal to axis ") +
            std::to_string(idim + i->second._ndimMin) + std::string(" of ") +
            std::string(i->first) + std::string(" length=") +
            std::to_string(i->second._nd[idim + i->second._ndimMin]));
    }

    if (ndat > nfirst) {
      for (int idim = 0; idim < ndat - nfirst; idim++) {
        if (i->second._nd[i->second._ndimMin + idim + nfirst] != 1)
          throw SEPException(std::string("Dataset ") + _datas.begin()->first +
                             std::string(" and ") + i->first +
                             std::string(" do not have the same dimensions"));
      }
    }
    if (ndat > nfirst) {
      for (int idim = 0; idim < nfirst - ndat; idim++) {
        if (first._nd[first._ndimMin + idim + ndat] != 1)
          throw SEPException(std::string("Dataset ") + _datas.begin()->first +
                             std::string(" and ") + i->first +
                             std::string(" do not have the same dimensions"));
      }
    }
  }

  bool found = false;
  long long idim = nfirst;
  std::vector<int> nb(first._nd.size() - nfirst, 1);
  while (!found && idim < first._nd.size()) {
    if (nbase * first._nd[idim] < _mem) {
      nb[idim] = first._nd[idim];
      nbase *= first._nd[idim];
      idim++;
    } else {
      found = true;
      nb[idim] = first._nd[idim] / nbase;
    }
  }
  for (auto i = _datas.begin(); i != _datas.end(); i++) {
    for (int idim = 0; idim < nb.size(); idim++) {
      i->second._nbs[i->second._ndimMin] = nb[idim];
    }
  }
}