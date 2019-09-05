#include "maps.h"
/* From yxtoxy in cwp*/

std::vector<float> SEP::maps::invert1DMap(const axis aX, const axis aY,
                                          const std::vector<float> &y,
                                          const float xylo, const float xyhi) {
  std::vector<float> x(aY.n);

  int nxi, nyo, jxi1, jxi2, jyo;
  float dxi, fxi, dyo, fyo, fyi, yo, xi1, yi1, yi2;

  nxi = aX.n;
  dxi = aX.d;
  fxi = aX.o;
  nyo = aY.n;
  dyo = aY.d;
  fyo = aY.o;
  fyi = y[0];

  /* loop over output y less than smallest input y */
  for (jyo = 0, yo = fyo; jyo < nyo; jyo++, yo += dyo) {
    if (yo >= fyi) break;
    x[jyo] = xylo;
  }

  /* loop over output y between smallest and largest input y */
  if (jyo == nyo - 1 && yo == fyi) {
    x[jyo++] = fxi;
    yo += dyo;
  }
  jxi1 = 0;
  jxi2 = 1;
  xi1 = fxi;
  while (jxi2 < nxi && jyo < nyo) {
    yi1 = y[jxi1];
    yi2 = y[jxi2];
    if (yi1 <= yo && yo <= yi2) {
      x[jyo++] = xi1 + dxi * (yo - yi1) / (yi2 - yi1);
      yo += dyo;
    } else {
      jxi1++;
      jxi2++;
      xi1 += dxi;
    }
  }

  /* loop over output y greater than largest input y */
  while (jyo < nyo) x[jyo++] = xyhi;
  return x;
}