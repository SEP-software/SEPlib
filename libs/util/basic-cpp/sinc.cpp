#include "sinc.h"
#include <iostream>
#include "math.h"
using namespace SEP;
sinc::sinc(const int lsinc, const float dsamp) {
  _dsamp = dsamp;
  int nsamp = 1. / _dsamp + .5;
  _lsinc = lsinc;
  for (int i = 0; i < nsamp; i++) {
    _table.push_back(mksinc(_lsinc, _dsamp * i));
  }
  _table.push_back(mksinc(_lsinc, 0.));
}
std::vector<float> sinc::mksinc(int lsinc, float d) {
  int j;
  float pi, pi2, snyq, snat, s0, ds, eta, s;

  /* compute constants */
  pi = 3.141592654;
  pi2 = pi * 2;
  snyq = 0.5;
  snat = snyq * (0.066 + 0.265 * log((double)lsinc));
  s0 = 0.0;
  ds = (snat - s0) / (lsinc * 2 - 1);
  eta = lsinc / 2 - 1.0 + d;

  /* segment work space */
  std::vector<float> b(lsinc), c(lsinc), work(lsinc);

  /* compute coefficients of Toeplitz linear system */
  for (j = 0; j < lsinc; j++) {
    for (s = s0, b[j] = c[j] = 0.0; s <= snat; s += ds) {
      b[j] += cos(pi2 * s * j);
      c[j] += cos(pi2 * s * (eta - j));
    }
  }

  /* solve the system for sinc coefficients */
  return toep(b, c, work);
}

std::vector<float> sinc::toep(std::vector<float> r, std::vector<float> g,
                              std::vector<float> a) {
  int i, j, jh;
  double c, e, v, w, bot;
  int m = r.size();
  std::vector<float> f(m);
  a[0] = 1.;
  v = r[0];
  f[0] = g[0] / r[0];

  for (j = 1; j < m; j++) {
    /* solve ra=v as in Claerbout, FGDP, p. 57 */
    e = a[j] = f[j] = 0.;
    for (i = 0; i < j; i++) e += a[i] * r[j - i];
    c = e / v;
    v -= e * c;
    jh = j / 2;
    for (i = 0; i <= jh; i++) {
      bot = a[j - i] - c * a[i];
      a[i] -= c * a[j - i];
      a[j - i] = bot;
    }

    /* use a and v above to get f[i], i = 0,1,2,...,j */
    w = 0;
    for (i = 0; i < j; i++) w += f[i] * r[j - i];
    c = (g[j] - w) / v;
    for (i = 0; i <= j; i++) f[i] += c * a[j - i];
  }

  return f;
}
