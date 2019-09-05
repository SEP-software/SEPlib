#ifndef MAPS_H
#define MAPS_H 1
#include <vector>
#include "axis.h"
namespace SEP {

namespace maps {
/*!
 Invert a mapping x(y) -> y(x)

 \param aX Input axis sampling
 \param aY Output axis sampling
 \param y Input array
 \param xylo Value to put for low values outside array
 \param xyhi Value to put for high values outside array
 */

std::vector<float> invert1DMap(const axis aX, const axis aY,
                               const std::vector<float> &y, const float xylo,
                               const float xyhi);
}  // namespace maps
}  // namespace SEP
#endif