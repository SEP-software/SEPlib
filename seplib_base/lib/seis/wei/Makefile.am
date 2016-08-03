
lib_LTLIBRARIES =
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepweif90.la
endif

libsepweif90_la_LIBADD = $(FFTW_FCLD) \
    ../../corelibs/sep3d/libsep3d.la \
    ../../corelibs/sep/libsep.la \
    $(FCLIBS) -lm


EXTRA_DIST=\
wei_basics.f90s    wei_flags.f90s     wei_path.f90s  wei_timers.f90s\
wei_cam.f90s       wei_image.f90s     wei_pspi.f90s  wei_verb.f90s\
weicig.f90s        wei_imaging.f90s   wei_run.f90s   wei_wavespace.f90s\
wei_data.f90s      wei_kmap.f90s      wei_sll.f90s   wei_wem.f90s\
wei_external.f90s  wei_mem.f90s       wei_slow.f90s  wei_xmap.f90s\
wei_fft.f90s       wei_mig_base.f90s  wei_ssf.f90s  lloyd.f90s\
wei_fk_share.f90s  wei_par.f90s       weitds.f90s weiattr.f90s wei_quantile.f90s

libsepweif90_la_SOURCES=\
wei_basics.f90    wei_flags.f90     wei_path.f90  wei_timers.f90\
wei_cam.f90       wei_image.f90     wei_pspi.f90  wei_verb.f90\
weicig.f90        wei_imaging.f90   wei_run.f90   wei_wavespace.f90\
wei_data.f90      wei_kmap.f90      wei_sll.f90   wei_wem.f90\
wei_external.f90  wei_mem.f90       wei_slow.f90  wei_xmap.f90\
wei_fft.f90       wei_mig_base.f90  wei_ssf.f90  lloyd.f90\
wei_fk_share.f90  wei_par.f90       weitds.f90 weiattr.f90 wei_quantile.f90


                                                                                    
                                                                                    




wei_data.lo: wei_wavespace.lo
wei_basics.lo: wei_timers.lo wei_mem.lo wei_verb.lo wei_external.lo wei_par.lo
wei_mig_base.lo: wei_basics.lo wei_slow.lo wei_imaging.lo wei_data.lo  wei_image.lo wei_wavespace.lo wei_fft.lo wei_pspi.lo wei_kmap.lo wei_xmap.lo wei_path.lo
wei_image.lo: wei_wavespace.lo
wei_ssf.lo: wei_slow.lo
wei_run.lo: wei_external.lo
wei_imaging.lo: wei_wavespace.lo 
weicig.lo: weiattr.lo weitds.lo wei_wavespace.lo wei_flags.lo wei_image.lo
wei_sll.lo: lloyd.lo wei_wavespace.lo wei_slow.lo wei_path.lo
wei_fft.lo: wei_flags.lo wei_wavespace.lo
wei_cam.lo: wei_fk_share.lo
wei_wem.lo: wei_fk_share.lo
wei_verb.lo:  wei_external.lo
wei_pspi.lo: wei_basics.lo wei_slow.lo wei_fft.lo
wei_cam.lo: wei_basics.lo
wei_path.lo: wei_basics.lo wei_slow.lo wei_image.lo wei_data.lo
wei_slow.lo: wei_wavespace.lo
wei_wavespace.lo: wei_basics.lo
lloyd.lo: wei_quantile.lo
wei_mem.lo:  wei_verb.lo  wei_par.lo wei_run.lo
wei_timers.lo:
wei_kmap.lo: wei_basics.lo
wei_fk_share.lo: wei_kmap.lo wei_slow.lo
wei_xmap.lo: wei_basics.lo
wei_wavespace.lo: wei_basics.lo
weitds.lo: wei_par.lo
wei_mem.lo: wei_verb.lo wei_par.lo wei_run.lo
wei_image.lo: wei_slow.lo
wei_path.lo: wei_data.lo





wei_data.o: wei_wavespace.o
wei_basics.o: wei_timers.o wei_mem.o wei_verb.o wei_external.o wei_par.o
wei_mig_base.o: wei_basics.o wei_slow.o wei_imaging.o wei_data.o  wei_image.o wei_wavespace.o wei_fft.o wei_pspi.o wei_kmap.o wei_xmap.o wei_path.o
wei_image.o: wei_wavespace.o
wei_ssf.o: wei_slow.o
wei_run.o: wei_external.o
wei_imaging.o: wei_wavespace.o
wei_sll.o: lloyd.o wei_wavespace.o wei_slow.o wei_path.o
wei_path.o: wei_data.o
wei_fft.o: wei_flags.o wei_wavespace.o
weicig.o: weiattr.o weitds.o wei_wavespace.o wei_image.o wei_flags.o
wei_tds.o: wei_par.o
wei_cam.o: wei_fk_share.o
wei_wavespace.o: wei_basics.o
wei_wem.o: wei_fk_share.o
wei_verb.o:  wei_external.o
wei_pspi.o: wei_basics.o wei_slow.o wei_fft.o
wei_cam.o: wei_basics.o
wei_path.o: wei_basics.o wei_slow.o wei_image.o wei_data.o
wei_slow.o: wei_wavespace.o
wei_wavespace.o: wei_basics.o
lloyd.o: wei_quantile.o
wei_mem.o:  wei_verb.o  wei_par.o wei_run.o
wei_timers.o:
wei_kmap.o: wei_basics.o
wei_fk_share.o: wei_kmap.o wei_slow.o
wei_xmap.o: wei_basics.o
weitds.o: wei_par.o
wei_mem.o: wei_verb.o wei_par.o wei_run.o
wei_image.o: wei_slow.o






include $(top_srcdir)/include/fortran.rules
