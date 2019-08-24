cmake_minimum_required(VERSION 2.8)

set(INCLUDES    
cluster.h	sepaux.h	sepfftf.h	sepmathf.h	sulib.h
hwt.h		sepconvert.h	sepfilter.h	septravel.h
sep_par.h	sepfft.h	sepmath.h	sepvector.h
)


install(FILES ${INCLUDES} DESTINATION include)
