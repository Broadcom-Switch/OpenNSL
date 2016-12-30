#*********************************************************************
#
# (C) Copyright Broadcom Corporation 2013-2016
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#*********************************************************************

#path and prefix of toolchain
#
# CROSS_COMPILE setting for GTO boards (Broadcom SVKs)
CROSS_COMPILE_GTO = /projects/nwsoft-toolchains/brl_2.0/gto/bin/powerpc-broadcom-linux-gnu-
# CROSS_COMPILE setting for IM-x86 and Celestica x86 boards
CROSS_COMPILE_x86 = /usr/bin/

# Default to GTO cross compile
export CROSS_COMPILE = $(CROSS_COMPILE_GTO)

#directory where the shared library resides
platform := gto-trident-brl20

export AR      = $(CROSS_COMPILE)ar
export AS      = $(CROSS_COMPILE)as
export CC      = $(CROSS_COMPILE)gcc
export LD      = $(CROSS_COMPILE)ld
export NM      = $(CROSS_COMPILE)nm
export OBJCOPY = $(CROSS_COMPILE)objcopy
export OBJDUMP = $(CROSS_COMPILE)objdump
export RANLIB  = $(CROSS_COMPILE)ranlib
export STRIP   = $(CROSS_COMPILE)strip

export SED     = sed
export RM      = rm

export OPENNSL_ROOT = ./..

export CFLAGS += -DCDP_PACKAGE=1
export CFLAGS += -I$(OPENNSL_ROOT)/include
export CFLAGS += -I$(OPENNSL_ROOT)/vendor/cjson

#Uncomment the following line for DNX family of devices
#export CFLAGS += -DOPENNSL_PRODUCT_DNX

FEATURE_LIST = L3
CFLAGS  += $(foreach feature,$(FEATURE_LIST), -DINCLUDE_$(feature))

OPENNSL_CFGFLAGS = -DOPENNSL_WARM_BOOT_SUPPORT
CFLAGS += ${OPENNSL_CFGFLAGS}

EXAMPLE_UTIL_SRCS = $(abspath $(OPENNSL_ROOT)/examples/util.c)
EXAMPLE_UTIL_OBJS = $(abspath $(OPENNSL_ROOT)/examples/util.o)

targets := $(basename $(notdir $(wildcard example*.c)))
targets := $(filter-out example_rpc_client.c,$(targets))

.PHONY: exutils all clean dump_vars

all: exutils $(targets)

exutils:
	$(CC) ${CFLAGS} -c $(EXAMPLE_UTIL_SRCS)

clean:
	$(RM) -rf *.d
	$(RM) -rf *.o

#
# Build the target executables
# The .o files are built by an implicit rule.
#
$(targets): % : %.o
	$(CC) -o $@ -L$(OPENNSL_ROOT)/bin/$(platform) -Wl,-Bstatic $^ $(EXAMPLE_UTIL_OBJS) -Wl,-Bdynamic -lc -lopennsl

.SECONDEXPANSION:

#
# This rule builds the dependency files
#
%.d: %.c
	set -e; $(RM) -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) -f $@.$$$$

-include $(patsubst %.c,%.d,$(notdir $(wildcard *.c)))

dump_vars:
	@echo OPENNSL_ROOT        = $(OPENNSL_ROOT)
	@echo targets             = $(targets)
	@echo CFLAGS              = $(CFLAGS)
	@echo CROSS_COMPILE       = $(CROSS_COMPILE)
