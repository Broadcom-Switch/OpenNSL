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
# $Id: Makefile,v 1.4 Broadcom SDK $
# $Copyright: (c) 2005 Broadcom Corp.
# All Rights Reserved.$
#

SDK :=$(shell if [ -n "$$SDK" ] ; then\
	echo $$SDK;\
	else\
	cd $(dir $(lastword $(MAKEFILE_LIST))); while /usr/bin/test ! -e RELEASE ; do \
	dir=`cd ../;pwd`;			\
	if [ "$$dir" = "/" ] ; then		\
	   echo Cannot find SDK in $(lastword $(MAKEFILE_LIST)) 1>&2;		\
	   exit 1;				\
	fi ;					\
	cd $$dir;				\
	done ;					\
	pwd;					\
	fi)

ifeq ($(SDK),)					
$(error Please run this in a tree)		
endif 				

export SDK

override-target=linux-$(platform)

ifeq ($(LINUX_MAKE_SHARED_LIB),1)
libext = so.$(SHAREDLIBVER)
else
libext = a
endif

ifeq (,$(platform))
$(error Internal error: platform variable is not set)
endif

include $(SDK)/make/Make.config
LOCALDIR=systems/linux/user/common
include $(SDK)/make/Make.depend
kernel-override=linux-$(platform)
ifdef BLDCONFIG
KERN_BLDROOT=${SDK}/${SDKBUILD}/${BLDCONFIG}/$(kernel-override)$(bldroot_suffix)
else
KERN_BLDROOT=${SDK}/${SDKBUILD}/$(kernel-override)$(bldroot_suffix)
endif

ifeq (,$(kernel_version))
kernel_version=2_4
endif

ifeq ($(kernel_version),2_6)
KOBJ=ko
else
KOBJ=o
endif

ifneq (,$(TOOLS_DIR))
override PATH := $(TOOLS_DIR):$(PATH)
endif

ifeq ($(DEST_DIR),)
DEST_DIR=${BLDDIR}
endif

KERNEL_BDE_LOCAL :=linux-kernel-bde.$(KOBJ)
KERNEL_BDE :=$(DEST_DIR)/$(KERNEL_BDE_LOCAL)

USER_BDE_LOCAL :=linux-user-bde.$(KOBJ)
USER_BDE=$(DEST_DIR)/$(USER_BDE_LOCAL)

BCM_KNET_LOCAL :=linux-bcm-knet.$(KOBJ)
BCM_KNET=$(DEST_DIR)/$(BCM_KNET_LOCAL)

ifeq (,$(findstring DELIVER,$(MAKECMDGOALS)))
.DEFAULT_GOAL := all
all_targets := kernel_modules $(KERNEL_BDE) $(USER_BDE)

LOCAL_TARGETS :=

ifeq ($(NO_LOCAL_TARGETS),)
LOCAL_TARGETS +=$(patsubst %,$(realpath ..)/$(platform)/%,$(KERNEL_BDE_LOCAL) $(USER_BDE_LOCAL))

all_targets +=$(LOCAL_TARGETS)
endif

# Build all by default
ifndef BUILD_KNET
BUILD_KNET = 1
endif

ifeq ($(BUILD_KNET),1)
# Kernel network support
all_targets += $(BCM_KNET)

ifeq ($(NO_LOCAL_TARGETS),)
LOCAL_TARGETS +=$(patsubst %,../$(platform)/%,$(BCM_KNET_LOCAL))
all_targets +=$(LOCAL_TARGETS)
endif

ADD_TO_CFLAGS += -I$(SDK)/systems/linux/kernel/modules/include
COND_KNET_LIBS = libuser.$(libext)
endif

#OPENNSL_FIXUP
.NOTPARALLEL:

all: $(BLDDIR)/.tree $(all_targets)

ifeq ($(NO_LOCAL_TARGETS),)
define LOCAL_TARGET_DEF
$(1) : $(DEST_DIR)/$(notdir $(1))
	cp $$? $$@
endef
endif

# User BDE libraries
ADD_TO_CFLAGS += -I$(SDK)/systems/bde/linux/include

# Use raw IOCTL for KNET
ADD_TO_CFLAGS += -DPROXY_SUPPORT=0

CFLAGS += $(ADD_TO_CFLAGS)

kernel_modules:
	$(MAKE) -C $(SDK)/systems/bde/linux/kernel kernel_version=$(kernel_version)
	$(MAKE) -C $(SDK)/systems/bde/linux/user/kernel kernel_version=$(kernel_version)
ifeq ($(BUILD_KNET),1)
	$(MAKE) -j1 -C $(SDK)/systems/linux/kernel/modules kernel_version=$(kernel_version) \
		subdirs="shared bcm-knet" override-target=linux-$(platform) CFLAGS="$(CFLAGS)"
endif

$(KERNEL_BDE): $(KERN_BLDROOT)/linux-kernel-bde.$(KOBJ)
	mkdir -p $(@D)
	$(OBJCOPY) --strip-debug $< $@

$(USER_BDE): $(KERN_BLDROOT)/linux-user-bde.$(KOBJ)
	$(OBJCOPY) --strip-debug $< $@

$(BCM_KNET): $(KERN_BLDROOT)/linux-bcm-knet.$(KOBJ)
	$(OBJCOPY) --strip-debug $< $@

ifeq ($(NO_LOCAL_TARGETS),)
$(foreach targ,$(LOCAL_TARGETS),$(eval $(call LOCAL_TARGET_DEF,$(targ))))
endif

clean::
	$(MAKE) -C $(SDK)/systems/bde/linux/kernel $@
	$(MAKE) -C $(SDK)/systems/bde/linux/user/kernel $@
	$(MAKE) -C $(SDK)/systems/linux/kernel/modules \
		subdirs="shared bcm-knet" \
		override-target=linux-$(platform) $@
	$(RM) $(KERNEL_BDE) $(USER_BDE)
	$(RM) $(BCM_KNET)
	$(RM) $(KERN_BLDROOT)/linux-kernel-bde.$(KOBJ)
	$(RM) $(KERN_BLDROOT)/linux-user-bde.$(KOBJ)
	$(RM) $(KERN_BLDROOT)/linux-bcm-knet.$(KOBJ)
	$(RM) $(LOCAL_TARGETS)

distclean:: clean

.PHONY: variable

#
# Echo variable values used for configuration
# usage: make VAR=CC variable
#
variable::
	@echo $($(VAR))

else
ifndef DELIVERY
$(error DELIVERY required)
endif

DELIVERABLES := $(KERNEL_BDE) $(USER_BDE)
# 1= source
define DELIVERY_RULE
_DEL_TARG += $(DELIVERY)/$(notdir $(1))
$(DELIVERY)/$(notdir $(1)) : $(1)
	@mkdir -p $(DELIVERY)
ifeq ($(filter $(notdir $(BCM)) $(notdir $(BCM).dbg),$(notdir $1)),)
	$(OBJCOPY) --strip-debug $$< $$@
else
	$(CP) -p $$< $$@
endif
endef

$(foreach f,$(DELIVERABLES),$(eval $(call DELIVERY_RULE,$(f))))

DELIVER: $(_DEL_TARG)
endif

# Make.config defines remaining phony targets
.PHONY: build kernel_modules DELIVER

