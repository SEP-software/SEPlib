EXTRA_DIST=cgstep.py \
   vec_base.py vec_super.py vec_sep.py vec_sfloat.py vec_scmplx.py  vec_oc.py\
   solv_base.py solv_smp.py solv_reg.py solv_prec.py \
   op_base.py  op_combo.py  op_oc_par.py  op_oc.py  \
   op_scale.py op_oc_serial.py op_oc_par_split.py  pv_func.py\
   pv_always_split.py  pv_copy_nfs.py  pv_copy.py  pv_split.py solv_shape.py


   


install-data-local: 
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
