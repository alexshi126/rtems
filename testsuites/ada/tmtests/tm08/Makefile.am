include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am

include $(top_srcdir)/ada.am

noinst_PROGRAMS = ada_tm08
ada_tm08_SOURCES = tm08.adb config.h tmtest.adb tmtest.ads
ada_tm08_SOURCES += init.c

ada_tm08$(EXEEXT): tm08.adb init.$(OBJEXT)
	$(GNATCOMPILE) -margs -a $< -o $@

