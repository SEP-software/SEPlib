

lib_LTLIBRARIES =
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepocf90.la
endif

libsepocf90_la_SOURCES = oc_adjnull.f90 oc_file.f90 oc_llist.f90 oc_sd.f90 \
oc_cd.f90 oc_filter.f90 oc_lsqr.f90 oc_solver.f90 \
oc_cg.f90 oc_global.f90 oc_lsqrpre.f90 oc_solverpre.f90 \
oc_cgstep.f90 oc_gmres.f90 oc_lsqrreg.f90 oc_solverreg.f90 \
oc_combine.f90 oc_helicon.f90 oc_matmult.f90 oc_tags.f90 \
oc_dottest.f90 oc_helocut.f90 oc_polydiv.f90 oc_utils.f90 \
oc_epsilon.f90 oc_kolmogoroff.f90 oc_rescale.f90 oc_weight.f90 \
oc_filealgebra.f90 oc_laplacian.f90 oc_scale.f90 oc_wilson.f90

# Modules dependencies
oc_epsilon.o: oc_global.o oc_tags.o oc_utils.o oc_file.o \
oc_filealgebra.o oc_combine.o
oc_cd.o: oc_global.o oc_filealgebra.o oc_llist.o
oc_sd.o: oc_global.o oc_filealgebra.o oc_llist.o
oc_lsqrpre.o: oc_global.o oc_tags.o oc_file.o oc_filealgebra.o oc_combine.o
oc_scale.o: oc_global.o oc_file.o oc_adjnull.o
oc_rescale.o: oc_global.o oc_tags.o oc_utils.o oc_file.o oc_filealgebra.o
oc_solver.o: oc_global.o oc_tags.o oc_file.o oc_filealgebra.o
oc_laplacian.o: oc_global.o oc_file.o oc_filter.o oc_wilson.o
oc_helocut.o: oc_global.o oc_filter.o oc_laplacian.o oc_helicon.o \
oc_polydiv.o
oc_solverpre.o: oc_global.o oc_tags.o oc_utils.o oc_file.o \
oc_filealgebra.o oc_combine.o
oc_combine.o: oc_global.o oc_file.o oc_filealgebra.o oc_scale.o
oc_wilson.o: oc_global.o oc_filter.o oc_helicon.o oc_polydiv.o
oc_lsqr.o: oc_global.o oc_tags.o oc_file.o oc_filealgebra.o
oc_filealgebra.o: oc_global.o oc_file.o
oc_lsqrreg.o: oc_global.o oc_tags.o oc_file.o oc_filealgebra.o \
oc_combine.o
oc_weight.o: oc_file.o oc_adjnull.o
oc_kolmogoroff.o: oc_filter.o
oc_cg.o: oc_global.o oc_filealgebra.o
oc_dottest.o: oc_global.o oc_file.o oc_filealgebra.o
oc_solverreg.o: oc_global.o oc_tags.o oc_utils.o oc_file.o \
oc_filealgebra.o oc_combine.o
oc_file.o: oc_utils.o
oc_helicon.o: oc_global.o oc_filter.o oc_adjnull.o oc_scale.o
oc_adjnull.o: oc_file.o oc_filealgebra.o
oc_matmult.o: oc_global.o oc_file.o
oc_llist.o: oc_global.o oc_file.o oc_filealgebra.o
oc_gmres.o: oc_global.o oc_filealgebra.o oc_llist.o
oc_polydiv.o: oc_global.o oc_filter.o oc_adjnull.o
oc_cgstep.o: oc_global.o oc_filealgebra.o
oc_filter.o: oc_global.o oc_file.o

oc_epsilon.lo: oc_global.lo oc_tags.lo oc_utils.lo oc_file.lo \
oc_filealgebra.lo oc_combine.lo
oc_cd.lo: oc_global.lo oc_filealgebra.lo oc_llist.lo
oc_sd.lo: oc_global.lo oc_filealgebra.lo oc_llist.lo
oc_lsqrpre.lo: oc_global.lo oc_tags.lo oc_file.lo oc_filealgebra.lo \
oc_combine.lo
oc_scale.lo: oc_global.lo oc_file.lo oc_adjnull.lo
oc_rescale.lo: oc_global.lo oc_tags.lo oc_utils.lo oc_file.lo \
oc_filealgebra.lo
oc_solver.lo: oc_global.lo oc_tags.lo oc_file.lo oc_filealgebra.lo
oc_laplacian.lo: oc_global.lo oc_file.lo oc_filter.lo oc_wilson.lo
oc_helocut.lo: oc_global.lo oc_filter.lo oc_laplacian.lo oc_helicon.lo \
oc_polydiv.lo
oc_solverpre.lo: oc_global.lo oc_tags.lo oc_utils.lo oc_file.lo \
oc_filealgebra.lo oc_combine.lo
oc_combine.lo: oc_global.lo oc_file.lo oc_filealgebra.lo oc_scale.lo
oc_wilson.lo: oc_global.lo oc_filter.lo oc_helicon.lo oc_polydiv.lo
oc_lsqr.lo: oc_global.lo oc_tags.lo oc_file.lo oc_filealgebra.lo
oc_filealgebra.lo: oc_global.lo oc_file.lo
oc_lsqrreg.lo: oc_global.lo oc_tags.lo oc_file.lo oc_filealgebra.lo \
oc_combine.lo
oc_weight.lo: oc_file.lo oc_adjnull.lo
oc_kolmogoroff.lo: oc_filter.lo
oc_cg.lo: oc_global.lo oc_filealgebra.lo
oc_dottest.lo: oc_global.lo oc_file.lo oc_filealgebra.lo
oc_solverreg.lo: oc_global.lo oc_tags.lo oc_utils.lo oc_file.lo \
oc_filealgebra.lo oc_combine.lo
oc_file.lo: oc_utils.lo
oc_helicon.lo: oc_global.lo oc_filter.lo oc_adjnull.lo oc_scale.lo
oc_adjnull.lo: oc_file.lo oc_filealgebra.lo
oc_matmult.lo: oc_global.lo oc_file.lo
oc_llist.lo: oc_global.lo oc_file.lo oc_filealgebra.lo
oc_gmres.lo: oc_global.lo oc_filealgebra.lo oc_llist.lo
oc_polydiv.lo: oc_global.lo oc_filter.lo oc_adjnull.lo
oc_cgstep.lo: oc_global.lo oc_filealgebra.lo
oc_filter.lo: oc_global.lo oc_file.lo


include $(top_srcdir)/include/fortran.rules

