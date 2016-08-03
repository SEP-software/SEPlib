
CLEANFILES = Headermath.c Create3d.c Synch3d.c Window_key.c

EXTRA_DIST = Headermath.csep Create3d.csep Synch3d.csep Window_key.csep

bin_PROGRAMS = Headermath Create3d Synch3d Window_key

LDADD = $(SEPLIB3D)

Headermath_LDADD = $(SEPMATH) $(SEPCONVERT) $(SEPVECTOR) $(SEPLIB3D) -lm

Window_key_LDADD = $(SUPERSET) -lm

Headermap.c: Headermath.csep
Create3d.c: Create3d.csep
Synch3d.c: Synch3d.csep
Window_key.c: Window_key.csep

include $(top_srcdir)/include/fortran.rules

