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
# $Id: Makefile,v 1.1 Broadcom SDK $
# $Copyright: (c) 2005 Broadcom Corp.
# All Rights Reserved.$
#
LOCALDIR = systems/bde/linux/user/kernel

# Make sure we build for the kernel if this is a user-mode build
ifneq ($(platform), )
override-target=linux-$(platform)
endif

include $(SDK)/make/Make.config

LIBS = $(LIBDIR)/libkern.a

ifneq ($(kernel_version),2_4)
KERNEL_MODULE_DIR = kernel_module

THIS_MOD_NAME := linux-user-bde
MODULE = $(LIBDIR)/$(THIS_MOD_NAME).o
KMODULE = $(LIBDIR)/$(THIS_MOD_NAME).ko

build: kernel_libs $(MODULE) $(KMODULE)
else
MODULE = $(LIBDIR)/linux-user-bde.o

build: kernel_libs $(MODULE)
endif

KBUILD_EXTRA_SYMBOLS := ${BLDDIR}/../../kernel/kernel_module/Module.symvers

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

kernel_libs:
	$(MAKE) -C $(SDK)/systems/linux/kernel/modules/shared

include $(SDK)/make/Make.depend

# Make.depend is before clean:: so that Make.depend's clean:: runs first.

clean::
	$(MAKE) -C $(SDK)/systems/linux/kernel/modules/shared $@
	$(RM) $(BOBJS) $(MODULE)

.PHONY: build kernel_libs
