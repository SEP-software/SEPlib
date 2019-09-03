#ifndef SINC_H
#define SINC_H 1
#include <vector>
class sinc {
 public:
  sinc() { ; }
  sinc(const int lsinc, const float dsamp);

  std::vector<float> mksinc(int lsinc, float d);

  std::vector<float> toep(std::vector<float> r, std::vector<float> g,
                          std::vector<float> a);

  std::vector<std::vector<float>> _table;
  float _dsamp;
  int _lsinc;
};
#endif