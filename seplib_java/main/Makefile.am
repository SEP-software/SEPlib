
JSOURCEDIR1 = java/edu/stanford/sep/seplib/

JSOURCES1 = Auxpar.java Auxputch.java Datapath.java Doc.java Fetch.java \
Getch.java GetNumberAxes.java GetPutAxis.java Hclose.java HelixCart.java \
Hetch.java Initpar.java Noheader.java Putch.java Putlin.java Redin.java \
Redout.java Sreed.java SreedWindow.java Srite.java SriteWindow.java \
Sseek.java Ssize.java Tetch.java

JCLASSDIR1 = $(JSOURCEDIR1)/classes/edu/stanford/sep/seplib/corelibs/sep/

all-local: sepcore.jar

sepcore.jar: $(addprefix $(JCLASSDIR1),$(subst java,class,$(JSOURCES1)))
	jar cfm sepcore.jar sepcore_manifest -C java/edu/stanford/sep/seplib/classes edu

$(JCLASSDIR1)%.class: $(JSOURCEDIR1)$(basename %).java
	@cd $(JSOURCEDIR1) && test -d classes || $(MKDIR) classes
	cd $(JSOURCEDIR1) && javac -cp ./classes -d ./classes $(notdir $<)

install-data-local: sepcore.jar
	$(INSTALL_DATA) $? $(libdir)

clean-local:
	-rm -rf java/edu/stanford/sep/seplib/classes/edu
