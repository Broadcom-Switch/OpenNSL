#
#  Unless you and Broadcom execute a separate written software license
#  agreement governing use of this software, this software is licensed to
#  you under the terms of the GNU General Public License version 2 (the
#  "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
#  with the following added to such license:
#  
#  As a special exception, the copyright holders of this software give
#  you permission to link this software with independent modules, and to
#  copy and distribute the resulting executable under terms of your
#  choice, provided that you also meet, for each linked independent
#  module, the terms and conditions of the license of that module.  An
#  independent module is a module which is not derived from this
#  software.  The special exception does not apply to any modifications
#  of the software.
#
# -*- Makefile -*-
# $Id: Makefile,v 1.3 Broadcom SDK $
# $Copyright: (c) 2005 Broadcom Corp.
# All Rights Reserved.$
#
LOCALDIR = systems/linux/kernel/modules/bcm-knet

include ${SDK}/make/Make.config

LIBS = $(LIBDIR)/libkern.a

ifeq ($(kernel_version),2_4)
MODULE = $(LIBDIR)/linux-bcm-knet.o
else
KERNEL_MODULE_DIR = kernel_module

THIS_MOD_NAME := linux-bcm-knet
MODULE = $(LIBDIR)/$(THIS_MOD_NAME).o
KMODULE = $(LIBDIR)/$(THIS_MOD_NAME).ko

build: $(MODULE) $(KMODULE)
endif

KBUILD_EXTRA_SYMBOLS := ${BLDDIR}/../../../../bde/linux/kernel/kernel_module/Module.symvers
ifeq (,$(findstring -DPROXY_SUPPORT=0,$(CFLAGS)))
KBUILD_EXTRA_SYMBOLS += ${BLDDIR}/../uk-proxy/kernel_module/Module.symvers
endif

# BCM Network Device

$(MODULE): $(BLDDIR)/.tree $(BOBJS) $(LIBS)
	$(LD) $(MODULE_LDFLAGS) -r -d $(BOBJS) $(LIBS) -o $@
ifneq ($(kernel_version),2_4)
$(KMODULE): $(MODULE)
	rm -fr $(BLDDIR)/$(KERNEL_MODULE_DIR)
	mkdir $(BLDDIR)/$(KERNEL_MODULE_DIR)
	cp ${SDK}/make/Makefile.linux-kmodule $(BLDDIR)/$(KERNEL_MODULE_DIR)/Makefile
	cat ${KBUILD_EXTRA_SYMBOLS} > $(BLDDIR)/$(KERNEL_MODULE_DIR)/Module.symvers
	MOD_NAME=$(THIS_MOD_NAME) $(MAKE) -C $(BLDDIR)/$(KERNEL_MODULE_DIR) $(THIS_MOD_NAME).ko
endif

# Make.depend is before clean:: so that Make.depend's clean:: runs first.

include ${SDK}/make/Make.depend

clean::
	$(RM) $(BLDDIR)/version.c $(BLDDIR)/version.o
	$(RM) $(BOBJS) $(MODULE)

ifneq ($(kernel_version),2_4)
.PHONY: build
endif
