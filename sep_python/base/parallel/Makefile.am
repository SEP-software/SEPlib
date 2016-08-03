EXTRA_DIST= \
   mach.py mach_base.py mach_list.py mach_file.py\
   sep_socket.py par_msgs.py \
   pf_base.py      pf_copy.py        pf_irreg.py  pf_resplit.py \
   pf_copy_nfs.py  pf_patch.py  pf_split.py \
   pj_base.py pj_split.py pj_nfs.py pj_func.py pj_simple.py\
   distribute_prog.py \
   pc.py pc_base.py pc_mpich.py 




install-data-local: 
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
