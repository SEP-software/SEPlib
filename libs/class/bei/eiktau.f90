complex function eiktau( dt, w, vkx, qi )
real                     dt, w, vkx, qi
eiktau = cexp( - dt * csqrt( cmplx( qi, -w) ** 2   +   vkx * vkx /4. )&
  & )
return
end  
