
lib_LTLIBRARIES = libsep_JNI.la

libsep_JNI_la_SOURCES = \
auxpar_jni.c auxputch_jni.c datapath_jni.c doc_jni.c fetch_jni.c getch_jni.c \
getnumberaxes_jni.c getputaxis_jni.c hclose_jni.c hetch_jni.c initpar_jni.c \
noheader_jni.c putch_jni.c putlin_jni.c redin_jni.c redout_jni.c sreed_jni.c \
sreedwindow_jni.c srite_jni.c sritewindow_jni.c sseek_jni.c ssize_jni.c \
tetch_jni.c

libsep_JNI_la_LIBADD = ../../seplib_base/lib/corelibs/sep/libsep.la $(FCLIBS) -lm

edu_stanford_sep_seplib_corelibs_sep_%.h: ../main/java/edu/stanford/sep/seplib/%.java
	-$(TOUCH) $@ && cd ../main/java/edu/stanford/sep/seplib && $(MKDIR) -p classes && javac -cp classes -d classes $(patsubst %.h,%,$(subst edu_stanford_sep_seplib_corelibs_sep_,,$@)).java && cd classes && javah -jni edu.stanford.sep.seplib.corelibs.sep.$(patsubst %.h,%,$(subst edu_stanford_sep_seplib_corelibs_sep_,,$@)) && $(MV) -f $@ ../../../../../../../lib/$@
